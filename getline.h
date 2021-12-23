#ifndef FLAT_INCLUDES
#include <stddef.h>
#include <stdbool.h>
#define FLAT_INCLUDES
#include "../range/def.h"
#include "../window/def.h"
#include "source.h"
#endif

bool convert_getline (bool * error, range_const_char * line, convert_source * source, const range_const_char * end_sequence);
