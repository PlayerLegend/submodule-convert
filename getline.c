#include "getline.h"
#include <stdbool.h>
#include "../range/string.h"
#include <assert.h>

status convert_getline (range_const_char * line, convert_source * source, const range_const_char * end_sequence)
{
    size_t region_size;

    size_t end_point;

    status status;

    while (!(region_size = range_count(source->contents->region)) || region_size == (end_point = range_strstr (&source->contents->signed_cast.region.alias_const, end_sequence)))
    {
	//log_debug ("No newline in region " RANGE_FORMSPEC, RANGE_FORMSPEC_ARG(source->contents->region));
	status = convert_grow (source, 20);

	if (status != STATUS_UPDATE)
	{
	    return region_size == 0 ? STATUS_END : STATUS_ERROR;
	}
    }

    assert (region_size > end_point);

    line->begin = source->contents->signed_cast.region.alias_const.begin;
    line->end = line->begin + end_point;
    source->contents->region.begin += range_count(*line) + range_count (*end_sequence);
    
    return STATUS_UPDATE;
}
