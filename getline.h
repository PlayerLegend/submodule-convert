#ifndef FLAT_INCLUDES
#include "source.h"
#endif

/**
   @file convert/getline.h
   Provides the convert_getline function
   @todo update documentation
*/

status convert_getline (range_const_char * line, convert_source * source, const range_const_char * end_sequence);
/**<
   @brief Reads a line from 'source' and places its contents in 'line', consuming the line's bytes from source's contents. Resulting lines will not contain their line end sequences.
   @param error Will be set to true if an error occurs
   @param line The range that will be set to contain the next input line
   @param source The source to read from
   @param end_sequence A range string describing a line end sequence
 */
