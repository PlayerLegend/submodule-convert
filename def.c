#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#define FLAT_INCLUDES
#include "../range/def.h"
#include "../window/def.h"
#include "../window/alloc.h"
#include "def.h"

#include "../log/log.h"

convert_interface * convert_interface_new (size_t arg_size)
{
    return calloc (1, sizeof(convert_interface));
}

bool convert_fill (bool * error, convert_interface * interface)
{
    assert (interface->read_buffer);
    
    if (range_is_empty (interface->read_buffer->region))
    {
	window_rewrite (*interface->read_buffer);
    }

    size_t start_size = range_count (interface->read_buffer->region);
    
    while ( interface->read_buffer->region.end < interface->read_buffer->alloc.end && convert_read(error, interface) )
    {}

    size_t end_size = range_count (interface->read_buffer->region);
    
    assert (!*error);
    assert (start_size <= end_size);
    
    return !*error && end_size != start_size;
}

bool convert_fill_minimum (bool * error, convert_interface * interface, size_t limit)
{
    window_alloc (*interface->read_buffer, limit);
    
    while ( (size_t)range_count (interface->read_buffer->region) < limit && convert_read(error, interface) )
    {}

    if (range_is_empty (interface->read_buffer->region))
    {
	return false;
    }

    if ((size_t)range_count (interface->read_buffer->region) < limit)
    {
	*error = true;
	log_debug ("Failed to fill minimum");
	return false;
    }

    assert ((size_t)range_count (interface->read_buffer->region) >= limit);
    
    return !*error && (size_t)range_count (interface->read_buffer->region) >= limit;
}

bool convert_drain (bool * error, convert_interface * interface)
{
    assert (interface->write_range);
    
    size_t start_size = range_count (*interface->write_range);

    while ( range_count(*interface->write_range) > 0 && convert_write(error, interface) )
    {}
    
    size_t end_size = range_count (*interface->write_range);

    assert (end_size <= start_size);
    
    return !*error && (end_size != start_size || range_is_empty (*interface->write_range));
}

bool convert_load_all (bool * error, convert_interface * interface)
{
    size_t new_size;
    
    while (convert_fill (error, interface))
    {
	new_size = 2 * range_count (interface->read_buffer->region) + 1024;
	window_alloc (*interface->read_buffer, new_size);
    }

    *window_push (*interface->read_buffer) = '\0';
    interface->read_buffer->region.end--;

    return !*error;
}

void convert_free(convert_interface * interface)
{
    interface->clear(interface);
    free (interface);
}

bool convert_skip_bytes(bool * error, convert_interface * interface, size_t count)
{
    size_t have_bytes;
    
    while (count > 0)
    {
	have_bytes = range_count(interface->read_buffer->region);

	if (!have_bytes)
	{
	    if (!convert_fill (error, interface))
	    {
		log_debug ("failed to fill");
		return false;
	    }
	}

	if (have_bytes > count)
	{
	    have_bytes = count;
	}

	interface->read_buffer->region.begin += have_bytes;

	count -= have_bytes;
    }

    return true;
}

bool convert_pull_max (bool * error, range_const_unsigned_char * result, convert_interface * interface, size_t limit)
{
    if (!limit)
    {
	result->begin = result->end = interface->read_buffer->region.begin;
	return false;
    }
    
    size_t have_bytes = range_count(interface->read_buffer->region);

    if (have_bytes > 0)
    {
	if (have_bytes > limit)
	{
	    have_bytes = limit;
	}
	
	result->begin = interface->read_buffer->region.begin;
	result->end = result->begin + limit;

	goto finish;
    }

    window_alloc (*interface->read_buffer, 1024);

    convert_fill (error, interface);

    if (*error)
    {
	return false;
    }

    have_bytes = range_count(interface->read_buffer->region);

    if (have_bytes > limit)
    {
	have_bytes = limit;
    }

    result->begin = interface->read_buffer->region.begin;
    result->end = result->begin + have_bytes;

    if (!have_bytes)
    {
	return false;
    }

finish:
    interface->read_buffer->region.begin = (unsigned char*) result->end;
    return true;
}

bool convert_grow (bool * error, convert_interface * interface, size_t count)
{
    size_t new_size = range_count (interface->read_buffer->region) + count;
    window_alloc (*interface->read_buffer, new_size);
    return convert_fill (error, interface);
}
