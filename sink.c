#include "sink.h"

#include <assert.h>
#include <stdlib.h>

status convert_drain (convert_sink * sink)
{
    assert (sink->contents);
    
    status status = STATUS_UPDATE;

    while ( range_count(*sink->contents) > 0 && (status = convert_write(sink)) == STATUS_UPDATE )
    {}
    
    if (!range_is_empty(*sink->contents))
    {
	return STATUS_ERROR;
    }

    return status;
}

void convert_sink_free(convert_sink * sink)
{
    sink->clear(sink);
    free (sink);
}
