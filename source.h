#ifndef FLAT_INCLUDES
#include <stddef.h>
#include <stdbool.h>
#define FLAT_INCLUDES
#include "../range/def.h"
#include "../window/def.h"
#endif

typedef struct convert_source convert_source;
typedef bool (*convert_source_update_callback)(bool * error, convert_source * target);
typedef void (*convert_source_clear_callback)(convert_source * target);

struct convert_source {
    convert_source_update_callback update;
    convert_source_clear_callback clear;
    window_unsigned_char * contents;
};

inline static bool convert_read (bool * error, convert_source * interface)
{
    return interface->update(error, interface);
}

inline static void convert_source_clear (convert_source * source)
{
    source->clear(source);
}

void convert_source_free(convert_source * source);
bool convert_fill_alloc (bool * error, convert_source * source);
bool convert_fill_minimum (bool * error, convert_source * source, size_t limit);
bool convert_load_all (bool * error, convert_source * source);
bool convert_pull_max (bool * error, range_const_unsigned_char * result, convert_source * source, size_t limit);
bool convert_grow (bool * error, convert_source * source, size_t count);
bool convert_skip_bytes(bool * error, convert_source * source, size_t count);
