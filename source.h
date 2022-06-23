#ifndef FLAT_INCLUDES
#include "type.h"
#endif

/**
   @file convert/source.h
   Provides an interface for reading bytes from an abstracted stream into a window.
   @todo update documentation
*/

inline static status convert_read (convert_source * interface)
{
    return interface->update(interface);
}
/**<
   @brief Reads once from the given interface
   @param error Will be set to true if an error occurs
   @param interface The source to read from
*/

inline static void convert_source_clear (convert_source * source)
{
    source->clear(source);
}
/**<
   @brief Clears a source in preparation to free it
*/

void convert_source_free(convert_source * source);
/**<
   @brief Clears and then frees the given source
 */

status convert_fill_alloc (convert_source * source);
/**<
   @brief Reads into the remaining unused bytes of the given source's contents
 */

status convert_fill_minimum (convert_source * source, size_t limit);
/**<
   @brief Reads at least 'limit' number of bytes into the given source's contents. If 0 bytes are read, then false is returned and error is not set. If a nonzero number of bytes are read, but this number is still less than limit, then error is set to true and false is returned. Otherwise, this function returns true.
 */

status convert_load_all (convert_source * source);
/**<
   @brief Loads bytes into the source's contents until the source is exhausted. Returns true if no error occured, and false otherwise.
*/

//status convert_pull_max (range_const_unsigned_char * result, convert_source * source, size_t limit);
/**<
   @brief Attempts to read 'limit' bytes from the source, and then assigns result to point to at most 'limit' bytes at the beginning of the source. The bytes returned in 'result' will be consumed from the source's contents.
 */

status convert_grow (convert_source * source, size_t count);
/**<
   @brief Attempts to read 'count' more bytes onto the end of the given source's contents.
*/

status convert_skip_bytes(convert_source * source, size_t count);
/**<
   @brief Skips ahead in the source stream by 'count' bytes, discarding the skipped bytes.
*/
