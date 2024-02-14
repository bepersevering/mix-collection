# Makefile for the C code in async-socket-server.
#
# Eli Bendersky [http://eli.thegreenplace.net]
# This code is in the public domain.
CC = gcc
CCFLAGS = -std=gnu99 -Wall -O3 -g -DNDEBUG -pthread
LDFLAGS = -lpthread -pthread

# It's possible to compile uv-server after installing libuv. The full
# instructions for installation I used (including `make install`) are from:
# https://github.com/libuv/libuv/blob/master/README.md.
# libuv compiles into a shared library which is placed alongside the .a in the
# installation directory.
LDLIBUV = -luv -Wl,-rpath=/usr/local/lib

EXECUTABLES = \
	select-server \

all: $(EXECUTABLES)

select-server: utils.c select-server.c
	$(CC) $(CCFLAGS) $^ -o $@ $(LDFLAGS)

.PHONY: clean format

clean:
	rm -f $(EXECUTABLES) *.o

format:
	clang-format -style=file -i *.c *.h