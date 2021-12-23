#ifndef FLAT_INCLUDES
#include <stddef.h>
#include <stdbool.h>
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

    window_alloc (*source->contents, 1024);

    bool error = false;

    while (convert_fill (&error, source))
    {
	if (!convert_drain (&error, sink))
	{
	    return false;
	}
    }

    return !error;
}