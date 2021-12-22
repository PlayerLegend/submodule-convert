#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#define FLAT_INCLUDES
#include "../range/def.h"
#include "../window/def.h"
#include "../window/alloc.h"
#include "../keyargs/keyargs.h"
#include "def.h"
#include "fd.h"

#include "../log/log.h"

bool convert_read_fd (bool * error, convert_interface * interface)
{
    fd_interface * io = (fd_interface*) interface;

    size_t max = interface->read_buffer->alloc.end - interface->read_buffer->region.begin;

    assert (interface->read_buffer->region.end <= interface->read_buffer->alloc.end);
    assert (interface->read_buffer->region.end >= interface->read_buffer->region.begin);

    size_t remaining = max - range_count (interface->read_buffer->region);
    
    if (!remaining)
    {
	return true;
    }

    ssize_t got = read (io->fd, interface->read_buffer->region.end, remaining);

    if (got <= 0)
    {
	if (got < 0)
	{
	    perror ("read");
	    *error = true;
	}

	return false;
    }

    interface->read_buffer->region.end += got;

    return true;
}

bool convert_write_fd (bool * error, convert_interface * interface)
{
    fd_interface * io = (fd_interface*) interface;

    size_t remaining = range_count (*interface->write_range);

    if (!remaining)
    {
	return true;
    }

    ssize_t wrote = write (io->fd, interface->write_range->begin, remaining);

    if (wrote < 0)
    {
	perror ("write");
	*error = true;
	return false;
    }

    assert ((size_t) wrote <= remaining);

    interface->write_range->begin += wrote;

    return true;
}

void convert_clear_fd (convert_interface * interface)
{
    fd_interface * io = (fd_interface*) interface;
    close (io->fd);
}

keyargs_define(fd_interface_init)
{
    return (fd_interface)
	{
	    .interface.read = convert_read_fd,
	    .interface.write = convert_write_fd,
	    .interface.clear = convert_clear_fd,
	    .fd = args.fd,
	    .interface.read_buffer = args.read_buffer,
	    .interface.write_range = args.write_range,
	};
}

