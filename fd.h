#ifndef FLAT_INCLUDES
#include <stddef.h>
#include <stdbool.h>
#define FLAT_INCLUDES
#include "../range/def.h"
#include "../window/def.h"
#include "def.h"
#include "../keyargs/keyargs.h"
#endif

#ifndef STDIN_FILENO
#define STDIN_FILENO 0
#endif

#ifndef STDOUT_FILENO
#define STDOUT_FILENO 1
#endif

#ifndef STDERR_FILENO
#define STDERR_FILENO 2
#endif

typedef struct {
    convert_interface interface;
    int fd;
}
    fd_interface;

bool convert_read_fd (bool * error, convert_interface * interface);
bool convert_write_fd (bool * error, convert_interface * interface);
void convert_clear_fd (convert_interface * interface);

#define fd_interface_init(...) keyargs_call(fd_interface_init, __VA_ARGS__)
keyargs_declare(fd_interface,
		fd_interface_init,
		window_unsigned_char * read_buffer;
		range_const_unsigned_char * write_range;
		int fd;);
