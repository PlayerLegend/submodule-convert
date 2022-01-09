#ifndef FLAT_INCLUDES
#include <stddef.h>
#include <stdbool.h>
#define FLAT_INCLUDES
#include "../range/def.h"
#include "../window/def.h"
#endif

typedef struct convert_sink convert_sink;
typedef bool (*convert_sink_update_callback)(bool * error, convert_sink * target);
typedef void (*convert_sink_clear_callback)(convert_sink * target);

struct convert_sink {
    convert_sink_update_callback update;
    convert_sink_clear_callback clear;
    range_const_unsigned_char * contents;
};

inline static bool convert_write (bool * error, convert_sink * sink)
{
    return sink->update(error, sink);
}

bool convert_drain (bool * error, convert_sink * sink);

inline static void convert_sink_clear (convert_sink * sink)
{
    bool error = false;
    convert_drain(&error, sink);
    sink->clear(sink);
}

void convert_sink_free(convert_sink * sink);
