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
   @file convert/fd/source.h
   Provides a source for reading from file descriptors
*/

typedef struct fd_source /// A structure used for reading from a file descriptor using the interface described in convert/source.h
{
    convert_source source; ///< The source to read from
    int fd; ///< The file descriptor to be used when reading
}
    fd_source;

fd_source fd_source_init (int fd, window_unsigned_char * contents); ///< Initializes an fd_source
convert_source * fd_source_new (int fd); ///< Allocates and initializes an fd_source
