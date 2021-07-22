#include <stdio.h>
#include <stdlib.h>

#include "jumptable.h"

/*
 * macro to define specific jumptable for this example.
 * this will return -1 on non-existing entry, the return-value of the jumptable entry otherwise.
 * gets two parameters (int foo, int bar) and passes them along.
 */
#define MYJUMPTABLE(NAME, INDEXTYPE, INDEXNAME, INDEXVALUE, INDEXBITS, ARRAY)	\
	JUMPTABLE(int,								\
		_ESCAPE(NAME),							\
		_ESCAPE(int foo, int bar),					\
		_ESCAPE(foo, bar),						\
		-1,								\
		_ESCAPE(ARRAY),							\
		_ESCAPE(INDEXTYPE),						\
		_ESCAPE(INDEXNAME),						\
		_ESCAPE(INDEXVALUE),						\
		_ESCAPE(INDEXBITS))

int d0(int foo, int bar)
{
	printf("A %d %d\n", foo, bar);
	return 1;
}

int d1(int foo, int bar)
{
	printf("B %d %d\n", foo, bar);
	return 1;
}

int d2(int foo, int bar)
{
	printf("C %d %d\n", foo, bar);
	return 1;
}

int d3(int foo, int bar)
{
	printf("D %d %d\n", foo, bar);
	return 1;
}

int _y0(int foo, int bar)
{
	printf("W %d %d\n", foo, bar);
	return 1;
}

int _y1(int foo, int bar)
{
	printf("X %d %d\n", foo, bar);
	return 1;
}

int _y2(int foo, int bar)
{
	printf("Y %d %d\n", foo, bar);
	return 1;
}

int _y3(int foo, int bar)
{
	printf("Z %d %d\n", foo, bar);
	return 1;
}

// actually define some jumptables that even stack
MYJUMPTABLE(decode2, unsigned, p0, bar, 2, _ESCAPE(_y0, _y1, _y2, NULL));
MYJUMPTABLE(decode1, unsigned, p0, foo, 2, _ESCAPE(d0, d1, d2, decode2));

int main(int argc, char**argv)
{
	if(argc == 3) {
		int a = atoi(argv[1]);
		int b = atoi(argv[2]);
		int r = decode1(a, b);
		if(r < 0)
			printf("ret %d for %d %d\n\n", r, a, b);
	} else {
		printf("2 args plz.\n");
	}
}
