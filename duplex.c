#ifndef FLAT_INCLUDES
#include <stddef.h>
#include <stdbool.h>
#include <assert.h>
#define FLAT_INCLUDES
#include "../range/def.h"
#include "../window/def.h"
#include "../window/alloc.h"
#include "sink.h"
#include "source.h"
#include "duplex.h"
#endif

bool convert_join (convert_sink * sink, convert_source * source)
{
    sink->contents = &source->contents->region.const_cast;

    window_alloc (*source->contents, 65535);

    bool error = false;

    while (convert_fill_alloc (&error, source))
    {
	if (!convert_drain (&error, sink))
	{
	    return false;
	}

	assert (range_is_empty (*sink->contents));
    }

    assert (range_is_empty (*sink->contents) || error);

    return !error;
}
