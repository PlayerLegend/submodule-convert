#ifndef FLAT_INCLUDES
#include <stddef.h>
#include <stdbool.h>
#include <unistd.h>
#define FLAT_INCLUDES
#include "../../range/def.h"
#include "../../window/def.h"
#include "../source.h"
#include "../sink.h"
#include "../../keyargs/keyargs.h"
#endif

typedef struct {
    convert_source source;
    int fd;
}
    fd_source;

#define fd_source_init(...) keyargs_call(fd_source_init, __VA_ARGS__)
keyargs_declare(fd_source,
		fd_source_init,
		window_unsigned_char * contents;
		int fd;);
