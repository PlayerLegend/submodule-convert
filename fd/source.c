#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#define FLAT_INCLUDES
#include "../../range/def.h"
#include "../../window/def.h"
#include "../../window/alloc.h"
#include "../source.h"
#include "../sink.h"
#include "source.h"
#include "sink.h"

#include "../../log/log.h"

static bool convert_read_fd (bool * error, convert_source * source)
{
    fd_source * io = (fd_source*) source;

    size_t max = source->contents->alloc.end - source->contents->region.begin;

    assert (source->contents->region.end <= source->contents->alloc.end);
    assert (source->contents->region.end >= source->contents->region.begin);

    size_t remaining = max - range_count (source->contents->region);
    
    if (!remaining)
    {
	return true;
    }

    ssize_t got = read (io->fd, source->contents->region.end, remaining);

    if (got <= 0)
    {
	if (got < 0)
	{
	    perror ("read");
	    *error = true;
	}

	return false;
    }

    source->contents->region.end += got;

    return true;
}


static void convert_clear_fd_source (convert_source * source)
{
    fd_source * io = (fd_source*) source;
    close (io->fd);
}

fd_source fd_source_init (int fd, window_unsigned_char * contents)
{
    return (fd_source)
	{
	    .source.update = convert_read_fd,
	    .source.clear = convert_clear_fd_source,
	    .fd = fd,
	    .source.contents = contents,
	};
}

static void convert_clear_fd_source_and_free_buffer (convert_source * source)
{
    convert_clear_fd_source (source);

    window_clear (*source->contents);
    free (source->contents);
}

convert_source * fd_source_new (int fd)
{
    fd_source * retval = calloc(1, sizeof(*retval));

    retval->source.update = convert_read_fd;
    retval->source.clear = convert_clear_fd_source_and_free_buffer;

    retval->fd = fd;
    retval->source.contents = calloc (1, sizeof(*retval->source.contents));

    return &retval->source;
}
