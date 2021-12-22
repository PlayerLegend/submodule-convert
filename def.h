#ifndef FLAT_INCLUDES
#include <stddef.h>
#include <stdbool.h>
#define FLAT_INCLUDES
#include "../range/def.h"
#include "../window/def.h"
#endif

typedef struct convert_interface convert_interface;
typedef bool (*convert_update_func)(bool * error, convert_interface * interface);
typedef void (*convert_clear_func)(convert_interface * interface);
struct convert_interface {
    convert_update_func read;
    convert_update_func write;
    convert_clear_func clear;
    window_unsigned_char * read_buffer;
    range_const_unsigned_char * write_range;
};

convert_interface * convert_interface_new (size_t arg_size);

// return true if more can be read or written from arg, not necessarily into buffer

inline static bool convert_read (bool * error, convert_interface * interface)
{
    return interface->read(error, interface);
}

inline static bool convert_write (bool * error, convert_interface * interface)
{
    return interface->write(error, interface);
}

inline static void convert_clear (convert_interface * interface)
{
    interface->clear(interface);
}

void convert_free(convert_interface * interface);
bool convert_fill (bool * error, convert_interface * interface);
bool convert_fill_minimum (bool * error, convert_interface * interface, size_t limit);
bool convert_drain (bool * error, convert_interface * interface);
bool convert_load_all (bool * error, convert_interface * interface);
bool convert_pull_max (bool * error, range_const_unsigned_char * result, convert_interface * interface, size_t limit);
bool convert_grow (bool * error, convert_interface * interface, size_t count);

bool convert_skip_bytes(bool * error, convert_interface * interface, size_t count);
