#!/bin/sh

$DEBUG_PROGRAM test/convert-getline <<EOF
this is a line
this is another line
a
b
c
d
1
2
3
4
more lines
all done
EOF
