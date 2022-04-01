#include "../fd/source.h"

#include <assert.h>
#include <unistd.h>

#include "../../window/alloc.h"
#include "../sink.h"
#include "../fd/sink.h"
#include "../../log/log.h"

int main()
{
    window_unsigned_char read_buffer = {0};

    window_alloc (read_buffer, 1e6);

    fd_source fd_read = fd_source_init(STDIN_FILENO, &read_buffer);
    fd_sink fd_write = fd_sink_init(STDOUT_FILENO, &read_buffer.region.const_cast);

    status status = STATUS_UPDATE;

    while ( (status = convert_fill_alloc (&fd_read.source)) != STATUS_ERROR && !range_is_empty (read_buffer.region) )
    {
	assert (convert_drain (&fd_write.sink) == STATUS_UPDATE);
	assert (range_is_empty (read_buffer.region));
    }

    assert (status != STATUS_ERROR);
    
    window_clear (read_buffer);

    return 0;
}
