#ifndef FLAT_INCLUDES
#include <stddef.h>
#include <stdbool.h>
#define FLAT_INCLUDES
#include "../range/def.h"
#include "../window/def.h"
#endif

/**
   @file convert/sink.h
   Provides an interface for writing bytes from a range into an abstracted stream.
*/

typedef struct convert_sink convert_sink;
typedef bool (*convert_sink_update_callback)(bool * error, convert_sink * target);
/**<
   This callback is called when bytes should be drained from the target's contents.
   @param error Should be set to true if an error occurs
   @param target The target sink
   @return Returns true if more bytes may be written after this call. Returns false if an error occured or the output stream closed.
*/

typedef void (*convert_sink_clear_callback)(convert_sink * target);
/**<
   @brief This callback is run in order to free any allocations to the given sink before it is freed
*/

struct convert_sink /// A generic sink structure
{
    convert_sink_update_callback update; ///< The update callback
    convert_sink_clear_callback clear; ///< The clear callback
    range_const_unsigned_char * contents; ///< The contents range to drain
};

inline static bool convert_write (bool * error, convert_sink * sink)
{
    return sink->update(error, sink);
}
/**<
   @brief Writes bytes from the sink's contents once
   @param error Will be set to true if an error occurs
   @param interface The sink to write from
*/

bool convert_drain (bool * error, convert_sink * sink);
/**<
   @brief Writes all of the contents of the given sink
   @param error Will be set to true if an error occurs
   @return false if an error occurred or the stream closed before all contents were written
 */

inline static void convert_sink_clear (convert_sink * sink)
{
    bool error = false;
    convert_drain(&error, sink);
    sink->clear(sink);
}
/**<
   @brief Clears a sink in preparation to free it
 */

void convert_sink_free(convert_sink * sink);
/**<
   @brief Clears and then frees a sink
*/
