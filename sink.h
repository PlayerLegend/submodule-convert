#ifndef FLAT_INCLUDES
#include "type.h"
#endif

/**
   @file convert/sink.h
   Provides an interface for writing bytes from a range into an abstracted stream.
   @todo update documentation
*/

inline static status convert_write (convert_sink * sink)
{
    return sink->update(sink);
}
/**<
   @brief Writes bytes from the sink's contents once
   @param error Will be set to true if an error occurs
   @param interface The sink to write from
*/

status convert_drain (convert_sink * sink);
/**<
   @brief Writes all of the contents of the given sink
   @param error Will be set to true if an error occurs
   @return false if an error occurred or the stream closed before all contents were written
 */

inline static void convert_sink_clear (convert_sink * sink)
{
    convert_drain(sink);
    sink->clear(sink);
}
/**<
   @brief Clears a sink in preparation to free it
 */

void convert_sink_free(convert_sink * sink);
/**<
   @brief Clears and then frees a sink
*/
