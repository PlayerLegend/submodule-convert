#include "../fd/source.h"
#include "../sink.h"
#include "../fd/sink.h"
#include <unistd.h>
#include <assert.h>
#include "../../window/alloc.h"

int main()
{
    window_unsigned_char buffer = {0};
    
    fd_source fd_read = fd_source_init(STDIN_FILENO, &buffer);
    fd_sink fd_write = fd_sink_init(STDOUT_FILENO, &buffer.region.alias_const);

    assert (convert_load_all (&fd_read.source) == STATUS_END);

    assert (convert_drain (&fd_write.sink) == STATUS_END);

    window_clear(buffer);

    return 0;
}
