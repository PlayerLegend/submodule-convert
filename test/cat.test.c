#include <stddef.h>
#include <stdbool.h>
#include <assert.h>
#define FLAT_INCLUDES
#include "../../range/def.h"
#include "../../window/def.h"
#include "../../window/alloc.h"
#include "../../keyargs/keyargs.h"
#include "../def.h"
#include "../fd.h"
#include "../../debug/debug.h"

#include "../../log/log.h"

int main()
{
    window_unsigned_char read_buffer = {0};

    window_alloc (read_buffer, 1e6);

    fd_interface read = fd_interface_init(.fd = STDIN_FILENO, .read_buffer = &read_buffer);
    fd_interface write = fd_interface_init(.fd = STDOUT_FILENO, .write_range = &read_buffer.region.const_cast);

    bool error = false;
    
    while (convert_fill (&error, &read.interface) && convert_drain (&error, &write.interface))
    {
	assert (!error);
    }

    assert (!error);
    assert (range_is_empty (read_buffer.region));

    window_clear (read_buffer);

    return 0;
}
