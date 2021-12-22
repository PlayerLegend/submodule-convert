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
#include "../getline.h"

#include "../../log/log.h"

int main()
{
    window_unsigned_char window = {0};
    
    fd_interface read = fd_interface_init(.fd = STDIN_FILENO, .read_buffer = &window);

    window_alloc (window, 1e6);

    range_const_char line;

    range_const_char end = { .begin = "\n", .end = end.begin + 1 };

    assert (end.end == end.begin + 1);

    bool error = false;

    while (convert_getline (&error, &line, &read.interface, &end))
    {
	log_normal ("line: %.*s", range_count(line), line.begin);
    }

    assert (!error);

    window_clear (window);

    return 0;
}
