
.PHONY: all clean test

CFLAGS += -Wall -Werror

all: jumptable

clean:
	-rm jumptable

test: jumptable
	./jumptable 0 0
	./jumptable 1 0
	./jumptable 2 0
	./jumptable 3 0
	./jumptable 3 1
	./jumptable 3 2
	./jumptable 3 3

jumptable: jumptable.c
