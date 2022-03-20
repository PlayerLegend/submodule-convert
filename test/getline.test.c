#include "../getline.h"
#include "../fd/source.h"
#include <unistd.h>
#include <assert.h>
#include "../../window/alloc.h"

int main()
{
    window_unsigned_char window = {0};
    
    fd_source read = fd_source_init(STDIN_FILENO, &window);

    window_alloc (window, 1e6);

    range_const_char line;

    range_const_char end = { .begin = "\n", .end = end.begin + 1 };

    assert (end.end == end.begin + 1);

    status status;

    while ( (status = convert_getline (&line, &read.source, &end)) == STATUS_UPDATE )
    {
	log_normal ("line: %.*s", range_count(line), line.begin);
    }
    
    assert (status == STATUS_END);

    window_clear (window);

    return 0;
}
