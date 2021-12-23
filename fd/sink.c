#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#define FLAT_INCLUDES
#include "../../range/def.h"
#include "../../window/def.h"
#include "../../window/alloc.h"
#include "../../keyargs/keyargs.h"
#include "../source.h"
#include "../sink.h"
#include "sink.h"

#include "../../log/log.h"

static bool convert_write_fd (bool * error, convert_sink * sink)
{
    fd_sink * io = (fd_sink*) sink;

    size_t remaining = range_count (*sink->contents);

    if (!remaining)
    {
	return true;
    }

    ssize_t wrote = write (io->fd, sink->contents->begin, remaining);

    if (wrote < 0)
    {
	perror ("write");
	*error = true;
	return false;
    }

    assert ((size_t) wrote <= remaining);

    sink->contents->begin += wrote;

    return true;
}

static void convert_clear_fd_sink (convert_sink * sink)
{
    fd_sink * io = (fd_sink*) sink;
    close (io->fd);
}

keyargs_define(fd_sink_init)
{
    return (fd_sink)
	{
	    .sink.update = convert_write_fd,
	    .sink.clear = convert_clear_fd_sink,
	    .fd = args.fd,
	    .sink.contents = args.contents,
	};
}
