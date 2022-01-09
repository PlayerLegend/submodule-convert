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
    convert_source source;
    int fd;
}
    fd_source;

fd_source fd_source_init (int fd, window_unsigned_char * contents);
