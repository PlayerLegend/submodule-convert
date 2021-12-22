#!/bin/sh

set -e

contents="$(mktemp)"

dd if=/dev/random bs=1M count=1 2>/dev/null > "$contents"

cat "$contents" |  $DEBUG_PROGRAM test/convert-cat | cmp "$contents"

rm "$contents"

echo "Verified cat"
