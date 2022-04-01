test/convert-cat: src/convert/test/cat.test.o
test/convert-cat: src/convert/fd/source.o
test/convert-cat: src/convert/fd/sink.o
test/convert-cat: src/convert/source.o
test/convert-cat: src/convert/sink.o
test/convert-cat: src/range/strstr.o
test/convert-cat: src/window/alloc.o
test/convert-cat: src/log/log.o

test/convert-cat-load-all: src/convert/test/cat-load-all.test.o
test/convert-cat-load-all: src/window/alloc.o
test/convert-cat-load-all: src/log/log.o
test/convert-cat-load-all: src/convert/fd/source.o
test/convert-cat-load-all: src/convert/fd/sink.o
test/convert-cat-load-all: src/convert/source.o
test/convert-cat-load-all: src/convert/sink.o

test/convert-getline: src/convert/test/getline.test.o
test/convert-getline: src/window/alloc.o
test/convert-getline: src/convert/getline.o
test/convert-getline: src/log/log.o
test/convert-getline: src/range/strstr.o
test/convert-getline: src/convert/fd/source.o
test/convert-getline: src/convert/fd/sink.o
test/convert-getline: src/convert/source.o
test/convert-getline: src/convert/sink.o

test/run-convert-cat: src/convert/test/run-cat.sh
test/run-convert-getline: src/convert/test/run-convert-getline.sh
test/run-convert-cat-load-all: src/convert/test/run-cat-load-all.sh

C_PROGRAMS += test/convert-cat
C_PROGRAMS += test/convert-cat-load-all
C_PROGRAMS += test/convert-getline
SH_PROGRAMS += test/run-convert-cat
SH_PROGRAMS += test/run-convert-getline
SH_PROGRAMS += test/run-convert-cat-load-all

run-tests: run-convert-tests
run-convert-tests:
	DEPENDS=convert-tests sh run-tests.sh test/run-convert-cat test/run-convert-cat-load-all test/run-convert-getline

depend: convert-depend
convert-depend:
	sh makedepend.sh src/convert/convert.makefile

convert-tests: test/convert-cat
convert-tests: test/convert-cat-load-all
convert-tests: test/run-convert-cat
convert-tests: test/run-convert-cat-load-all
convert-tests: test/convert-getline
convert-tests: test/run-convert-getline

tests: convert-tests
# DO NOT DELETE

src/convert/join.o: src/convert/join.h src/convert/sink.h src/range/def.h
src/convert/join.o: src/window/def.h src/convert/status.h
src/convert/join.o: src/convert/source.h src/window/alloc.h
src/convert/source.o: src/convert/source.h src/window/alloc.h src/log/log.h
src/convert/fd/sink.o: src/convert/sink.h src/range/def.h src/window/def.h
src/convert/fd/sink.o: src/convert/status.h
src/convert/fd/source.o: src/convert/source.h src/window/alloc.h
src/convert/fd/source.o: src/range/def.h src/window/def.h
src/convert/sink.o: src/convert/sink.h src/range/def.h src/window/def.h
src/convert/sink.o: src/convert/status.h
src/convert/getline.o: src/convert/getline.h src/convert/source.h
src/convert/getline.o: src/range/string.h src/range/def.h
src/convert/test/getline.test.o: src/convert/getline.h src/convert/source.h
src/convert/test/getline.test.o: src/convert/fd/source.h src/convert/source.h
src/convert/test/getline.test.o: src/range/def.h src/window/def.h
src/convert/test/getline.test.o: src/convert/status.h src/window/alloc.h
src/convert/test/getline.test.o: src/log/log.h
src/convert/test/cat-load-all.test.o: src/convert/fd/source.h
src/convert/test/cat-load-all.test.o: src/convert/source.h src/range/def.h
src/convert/test/cat-load-all.test.o: src/window/def.h src/convert/status.h
src/convert/test/cat-load-all.test.o: src/convert/sink.h
src/convert/test/cat-load-all.test.o: src/convert/fd/sink.h
src/convert/test/cat-load-all.test.o: src/window/alloc.h
src/convert/test/cat.test.o: src/convert/fd/source.h src/convert/source.h
src/convert/test/cat.test.o: src/range/def.h src/window/def.h
src/convert/test/cat.test.o: src/convert/status.h src/window/alloc.h
src/convert/test/cat.test.o: src/convert/sink.h src/convert/fd/sink.h
src/convert/test/cat.test.o: src/log/log.h
