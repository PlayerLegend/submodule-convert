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

/**
   @file convert/fd/sink.h
   Provides a sink for writing to file descriptors
*/

typedef struct fd_sink /// A structure used for writing to a file descriptor using the interface described in convert/sink.h
{
    convert_sink sink; ///< The sink to write to
    int fd; ///< The file descriptor to use when writing
}
    fd_sink;

fd_sink fd_sink_init(int fd, range_const_unsigned_char * contents); ///< Initializes an fd_sink
