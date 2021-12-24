#include <stddef.h>
#include <stdbool.h>
#include <assert.h>
#include <unistd.h>
#define FLAT_INCLUDES
#include "../../range/def.h"
#include "../../window/def.h"
#include "../../window/alloc.h"
#include "../../keyargs/keyargs.h"
#include "../source.h"
#include "../fd/source.h"
#include "../sink.h"
#include "../fd/sink.h"

#include "../../log/log.h"

int main()
{
    window_unsigned_char read_buffer = {0};

    window_alloc (read_buffer, 1e6);

    fd_source fd_read = fd_source_init(.fd = STDIN_FILENO, .contents = &read_buffer);
    fd_sink fd_write = fd_sink_init(.fd = STDOUT_FILENO, .contents = &read_buffer.region.const_cast);

    bool error = false;
    
    while (convert_fill_alloc (&error, &fd_read.source) && convert_drain (&error, &fd_write.sink))
    {
	assert (!error);
    }

    assert (!error);
    assert (range_is_empty (read_buffer.region));

    window_clear (read_buffer);

    return 0;
}
