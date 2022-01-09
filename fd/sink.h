#ifndef FLAT_INCLUDES
#include <stddef.h>
#include <stdbool.h>
#include <unistd.h>
#define FLAT_INCLUDES
#include "../../range/def.h"
#include "../../window/def.h"
#include "../source.h"
#include "../sink.h"
#endif

typedef struct {
    convert_sink sink;
    int fd;
}
    fd_sink;

fd_sink fd_sink_init(int fd, range_const_unsigned_char * contents);
