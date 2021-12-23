#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#define FLAT_INCLUDES
#include "../range/def.h"
#include "../window/def.h"
#include "../window/alloc.h"
#include "source.h"

#include "../log/log.h"

convert_source * convert_source_new (size_t arg_size)
{
    return calloc (1, sizeof(convert_source));
}

bool convert_fill (bool * error, convert_source * source)
{
    assert (source->contents);
    
    if (range_is_empty (source->contents->region))
    {
	window_rewrite (*source->contents);
    }

    size_t start_size = range_count (source->contents->region);
    
    while ( source->contents->region.end < source->contents->alloc.end && convert_read(error, source) )
    {}

    size_t end_size = range_count (source->contents->region);
    
    assert (!*error);
    assert (start_size <= end_size);
    
    return !*error && end_size != start_size;
}

bool convert_fill_minimum (bool * error, convert_source * source, size_t limit)
{
    window_alloc (*source->contents, limit);
    
    while ( (size_t)range_count (source->contents->region) < limit && convert_read(error, source) )
    {}

    if (range_is_empty (source->contents->region))
    {
	return false;
    }

    if ((size_t)range_count (source->contents->region) < limit)
    {
	*error = true;
	log_debug ("Failed to fill minimum");
	return false;
    }

    assert ((size_t)range_count (source->contents->region) >= limit);
    
    return !*error && (size_t)range_count (source->contents->region) >= limit;
}

bool convert_load_all (bool * error, convert_source * source)
{
    size_t new_size;
    
    while (convert_fill (error, source))
    {
	new_size = 2 * range_count (source->contents->region) + 1024;
	window_alloc (*source->contents, new_size);
    }

    *window_push (*source->contents) = '\0';
    source->contents->region.end--;

    return !*error;
}

void convert_free(convert_source * source)
{
    source->clear(source);
    free (source);
}

bool convert_skip_bytes(bool * error, convert_source * source, size_t count)
{
    size_t have_bytes;
    
    while (count > 0)
    {
	have_bytes = range_count(source->contents->region);

	if (!have_bytes)
	{
	    if (!convert_fill (error, source))
	    {
		log_debug ("failed to fill");
		return false;
	    }
	}

	if (have_bytes > count)
	{
	    have_bytes = count;
	}

	source->contents->region.begin += have_bytes;

	count -= have_bytes;
    }

    return true;
}

bool convert_pull_max (bool * error, range_const_unsigned_char * result, convert_source * source, size_t limit)
{
    if (!limit)
    {
	result->begin = result->end = source->contents->region.begin;
	return false;
    }
    
    size_t have_bytes = range_count(source->contents->region);

    if (have_bytes > 0)
    {
	if (have_bytes > limit)
	{
	    have_bytes = limit;
	}
	
	result->begin = source->contents->region.begin;
	result->end = result->begin + limit;

	goto finish;
    }

    window_alloc (*source->contents, 1024);

    convert_fill (error, source);

    if (*error)
    {
	return false;
    }

    have_bytes = range_count(source->contents->region);

    if (have_bytes > limit)
    {
	have_bytes = limit;
    }

    result->begin = source->contents->region.begin;
    result->end = result->begin + have_bytes;

    if (!have_bytes)
    {
	return false;
    }

finish:
    source->contents->region.begin = (unsigned char*) result->end;
    return true;
}

bool convert_grow (bool * error, convert_source * source, size_t count)
{
    size_t new_size = range_count (source->contents->region) + count;
    window_alloc (*source->contents, new_size);
    return convert_fill (error, source);
}
