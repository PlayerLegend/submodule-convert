#include "source.h"
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <stdlib.h>
#include "../../window/alloc.h"

static status convert_read_fd (convert_source * source)
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
	    return STATUS_ERROR;
	}
	else
	{
	    return STATUS_END;
	}
    }

    source->contents->region.end += got;

    return STATUS_UPDATE;
}


static void convert_clear_fd_source (convert_source * source)
{
    fd_source * io = (fd_source*) source;
    if (io->fd >= 0)
    {
	close (io->fd);
    }
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
