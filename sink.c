#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#define FLAT_INCLUDES
#include "../range/def.h"
#include "../window/def.h"
#include "../window/alloc.h"
#include "sink.h"

#include "../log/log.h"

bool convert_drain (bool * error, convert_sink * sink)
{
    assert (sink->contents);
    
    //size_t start_size = range_count (*sink->contents);

    while ( range_count(*sink->contents) > 0 && convert_write(error, sink) )
    {}
    
    //size_t end_size = range_count (*sink->contents);

    //assert (end_size <= start_size);
    
//    return !*error && (end_size != start_size || range_is_empty (*sink->contents));
    return !*error && range_is_empty (*sink->contents);
}

void convert_sink_free(convert_sink * sink)
{
    sink->clear(sink);
    free (sink);
}
