#ifndef FLAT_INCLUDES
#define FLAT_INCLUDES
#endif

typedef enum {
    STATUS_UPDATE, //< Signifies that the function arguments were updated
    STATUS_END, //< Signifies that the stream has ended
    STATUS_ERROR, //< Signifies that there was an error when running the function
}
    status; //< A return value for stream-like functions
