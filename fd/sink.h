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
    convert_sink sink;
    int fd;
}
    fd_sink;

#define fd_sink_init(...) keyargs_call(fd_sink_init, __VA_ARGS__)
keyargs_declare(fd_sink,
		fd_sink_init,
		range_const_unsigned_char * contents;
		int fd;);
