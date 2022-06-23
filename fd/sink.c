#include "sink.h"
#include <unistd.h>
#include <stdio.h>
#include <assert.h>

static status convert_write_fd (convert_sink * sink)
{
    fd_sink * io = (fd_sink*) sink;

    size_t remaining = range_count (*sink->contents);

    if (!remaining)
    {
	return STATUS_UPDATE;
    }

    ssize_t wrote = write (io->fd, sink->contents->begin, remaining);

    if (wrote < 0)
    {
	perror ("write");
	return STATUS_ERROR;
    }

    if (wrote == 0)
    {
	return STATUS_END;
    }

    assert ((size_t) wrote <= remaining);

    sink->contents->begin += wrote;

    return STATUS_UPDATE;
}

static void convert_clear_fd_sink (convert_sink * sink)
{
    fd_sink * io = (fd_sink*) sink;
    close (io->fd);
}

fd_sink fd_sink_init(int fd, range_const_unsigned_char * contents)
{
    return (fd_sink)
	{
	    .sink.update = convert_write_fd,
	    .sink.clear = convert_clear_fd_sink,
	    .fd = fd,
	    .sink.contents = contents,
	};
}
