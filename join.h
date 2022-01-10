#ifndef FLAT_INCLUDES
#include <stddef.h>
#include <stdbool.h>
#define FLAT_INCLUDES
#include "../range/def.h"
#include "../window/def.h"
#include "sink.h"
#include "source.h"
#endif

/**
   @file convert/join.h
   This file provides the convert_join function
*/

bool convert_join (convert_sink * sink, convert_source * source);
/**<
   @brief Returns true if all bytes from source could be written to sink without error, or false otherwise
*/
