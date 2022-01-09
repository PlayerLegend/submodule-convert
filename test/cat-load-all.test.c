#include <stddef.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#define FLAT_INCLUDES
#include "../../range/def.h"
#include "../../window/def.h"
#include "../../window/alloc.h"
#include "../source.h"
#include "../fd/source.h"
#include "../sink.h"
#include "../fd/sink.h"

#include "../../log/log.h"

int main()
{
    window_unsigned_char buffer = {0};
    
    fd_source fd_read = fd_source_init(STDIN_FILENO, &buffer);
    fd_sink fd_write = fd_sink_init(STDOUT_FILENO, &buffer.region.const_cast);

    bool error = false;

    assert (convert_load_all (&error, &fd_read.source));
    assert (!error);

    while (convert_drain (&error, &fd_write.sink))
    {
	assert (!error);
    }

    assert (!error);
    assert (range_is_empty (buffer.region));

    window_clear(buffer);

    return 0;
}
