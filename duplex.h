#ifndef FLAT_INCLUDES
#include <stddef.h>
#include <stdbool.h>
#define FLAT_INCLUDES
#include "../range/def.h"
#include "../window/def.h"
#include "sink.h"
#include "source.h"
#endif


typedef struct convert_duplex convert_duplex;
typedef void (*convert_duplex_clear_callback)(convert_duplex * target);
struct convert_duplex {
    convert_source source;
    convert_sink sink;
    convert_duplex_clear_callback clear;
};
    
