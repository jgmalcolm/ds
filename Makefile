MAKE=make --no-print-directory
DFLAGS = $(shell test -f .DEBUG && echo -gstabs+ -DDEBUG || echo -O -DNDEBUG)
CFLAGS = -std=c99 -Wall $(DFLAGS)

SRC = ll readline queue bitfield hash cache coll bt twul

all: .depend libds.so test
	./test
test: libds.so

libds.so: $(patsubst %, %.o, $(SRC))

%.so:
	$(CC) $(CFLAGS) -dynamiclib -o $@ $^ $(LDFLAGS)

clean:
	rm -f libds.so $(patsubst %, %.o, $(SRC))
debug:
	@test -f .DEBUG && (rm .DEBUG; echo off) || (touch .DEBUG; echo on)

.depend: Makefile $(patsubst %, %.c, $(SRC)) *.h
	$(CC) -MM $(CFLAGS) $(filter %.c, $^) >$@

include .depend
