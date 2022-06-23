#ifndef FLAT_INCLUDES
#include "../window/def.h"
#endif

// status

typedef enum {
    STATUS_UPDATE, //< Signifies that the function arguments were updated
    STATUS_END, //< Signifies that the stream has ended
    STATUS_ERROR, //< Signifies that there was an error when running the function
}
    status; //< A return value for stream-like functions

// source

typedef struct convert_source convert_source;
typedef status (*convert_source_update_callback)(convert_source * target);
/**<
   @brief This callback is called when more bytes should be read into the given source. 
   @param error Should be set to true if an error occurs
   @param target The target source
   @return True if further bytes may be read, false if the stream ended with this call or an error occurred.
*/

typedef void (*convert_source_clear_callback)(convert_source * target);
/**<
   @brief This callback is run in order to free any allocations to the given source before it is freed
*/

struct convert_source /// A generic source type
{
    convert_source_update_callback update; ///< The update callback
    convert_source_clear_callback clear; ///< The clear callback
    window_unsigned_char * contents; ///< The contents into which the update callback will write bytes
};

// sink

typedef struct convert_sink convert_sink;
typedef status (*convert_sink_update_callback)(convert_sink * target);
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
