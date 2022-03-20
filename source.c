#include "source.h"

#include <assert.h>
#include <stdlib.h>

#include "../window/alloc.h"
#include "../log/log.h"

/*
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
*/

convert_source * convert_source_new (size_t arg_size)
{
    return calloc (1, sizeof(convert_source));
}

status convert_fill_alloc (convert_source * source)
{
    assert (source->contents);
    
    if (range_is_empty (source->contents->region))
    {
	window_rewrite (*source->contents);
    }

    status status = STATUS_UPDATE;

    while ( source->contents->region.end < source->contents->alloc.end && (status = convert_read(source)) == STATUS_UPDATE )
    {}

    return status;
}

/*status convert_fill_minimum (convert_source * source, size_t limit)
{
    window_alloc (*source->contents, limit);

    status status = STATUS_INCOMPLETE;

    while ( (size_t)range_count (source->contents->region) < limit && (status = convert_read(source)) == STATUS_INCOMPLETE )
    {}

    if (range_is_empty (source->contents->region))
    {
	return STATUS_ERROR;
    }

    if ((size_t)range_count (source->contents->region) < limit)
    {
	log_debug ("Failed to fill minimum %zu / %zu", range_count(source->contents->region), limit);
	return STATUS_ERROR;
    }

    assert ((size_t)range_count (source->contents->region) >= limit);
    
    return (size_t)range_count (source->contents->region) >= limit;
    }*/

status convert_load_all (convert_source * source)
{
    size_t new_size;

    status status = STATUS_UPDATE;

    while ( (status = convert_fill_alloc (source)) != STATUS_END )
    {
	new_size = 2 * range_count (source->contents->region) + 1024;
	window_alloc (*source->contents, new_size);
    }

    *window_push (*source->contents) = '\0';
    source->contents->region.end--;

    return status;
}

void convert_source_free(convert_source * source)
{
    source->clear(source);
    free (source);
}

status convert_skip_bytes(convert_source * source, size_t count)
{
    size_t have_bytes;

    status status = STATUS_UPDATE;
    
    while (count > 0 && status == STATUS_UPDATE)
    {
	if ( (have_bytes = range_count(source->contents->region)) )
	{
	    source->contents->region.begin += have_bytes;
	    count -= have_bytes;
	}
	else if ((status = convert_fill_alloc (source)) == STATUS_ERROR)
	{
	    log_debug ("Failed to fill");
	    break;
	}
    }

    return count == 0 ? status : STATUS_ERROR;
}

/*status convert_pull_max (range_const_unsigned_char * result, convert_source * source, size_t limit)
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

    convert_fill_alloc (error, source);

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
    }*/

status convert_grow (convert_source * source, size_t count)
{
    size_t new_size = range_count (source->contents->region) + count;
    window_alloc (*source->contents, new_size);
    return convert_read (source);
}
