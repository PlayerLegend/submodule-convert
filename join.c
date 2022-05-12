#include "join.h"
#include <assert.h>
#include "../window/alloc.h"

bool convert_join (convert_sink * sink, convert_source * source)
{
    sink->contents = &source->contents->region.alias_const;

    window_alloc (*source->contents, 65535);

    status status = STATUS_UPDATE;

    while ((status = convert_fill_alloc (source)) != STATUS_ERROR && !range_is_empty(source->contents->region))
    {
	if (STATUS_UPDATE != convert_drain (sink))
	{
	    return false;
	}

	assert (range_is_empty (*sink->contents));
    }

    assert (range_is_empty (*sink->contents));

    return status != STATUS_ERROR;
}
