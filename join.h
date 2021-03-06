#ifndef FLAT_INCLUDES
#include <stdbool.h>
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
