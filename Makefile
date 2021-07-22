
.PHONY: all clean test

CFLAGS += -Og -ggdb3 -Wall -Werror

all: jumptable jumptable.asm jumptable.disasm

clean:
	-rm jumptable *.asm *.disasm

test: jumptable
	./jumptable 0 0
	./jumptable 1 0
	./jumptable 2 0
	./jumptable 3 0
	./jumptable 3 1
	./jumptable 3 2
	./jumptable 3 3

%.disasm: %
	objdump -dgCxwsSh --show-raw-insn $< > $@

%.asm: %.c
	gcc -S $(CFLAGS) $^ -o $@

jumptable: jumptable.c jumptable.h
	gcc -o $@ $<
