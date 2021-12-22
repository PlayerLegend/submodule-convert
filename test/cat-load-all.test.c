#include <stddef.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
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
    window_unsigned_char buffer = {0};
    
    fd_interface read = fd_interface_init(.fd = STDIN_FILENO, .read_buffer = &buffer);
    fd_interface write = fd_interface_init(.fd = STDOUT_FILENO, .write_range = &buffer.region.const_cast);

    bool error = false;

    assert (convert_load_all (&error, &read.interface));
    assert (!error);

    while (convert_drain (&error, &write.interface))
    {
	assert (!error);
    }

    assert (!error);
    assert (range_is_empty (buffer.region));

    window_clear(buffer);

    return 0;
}
