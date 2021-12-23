#include <stddef.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#define FLAT_INCLUDES
#include "../range/def.h"
#include "../range/string.h"
#include "../window/def.h"
#include "../window/alloc.h"
#include "../keyargs/keyargs.h"
#include "source.h"
#include "getline.h"

#include "../log/log.h"

bool convert_getline (bool * error, range_const_char * line, convert_source * source, const range_const_char * end_sequence)
{
    size_t region_size;

    size_t end_point;

    while (!(region_size = range_count(source->contents->region)) || region_size == (end_point = range_strstr (&source->contents->signed_cast.region.const_cast, end_sequence)))
    {
	if (!convert_grow (error, source, 20))
	{
	    return false;
	}
	
	/*window_alloc (*source->contents, range_count(source->contents->region) + 20);
	if (!convert_read (error, source))
	{
	    return false;
	    }*/
    }

    assert (region_size > end_point);

    line->begin = source->contents->signed_cast.region.const_cast.begin;
    line->end = line->begin + end_point;
    window_release (*source->contents, range_count(*line) + range_count (*end_sequence));
    
    return !*error;
}
