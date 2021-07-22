#include <stdio.h>
#include <stdlib.h>

#define _ESCAPE(...) __VA_ARGS__

#define JUMPTABLE(RETTYPE, NAME, ARGS, BADVALUE, ARRAY, INDEXTYPE, INDEXNAME, INDEXVALUE, INDEXBITS, ...)	\
	RETTYPE NAME(ARGS) {											\
		const RETTYPE (*jTable[1 << INDEXBITS]) (ARGS) = {ARRAY};					\
		INDEXTYPE INDEXNAME = (INDEXVALUE) & ((1 << INDEXBITS)-1);					\
		RETTYPE (*fun) (ARGS) = jTable[INDEXNAME];							\
		if (NULL == fun)										\
			return BADVALUE;									\
		else												\
			return fun(__VA_ARGS__);								\
	}

#define MYJUMPTABLE(NAME, INDEXTYPE, INDEXNAME, INDEXVALUE, INDEXBITS, ARRAY)					\
	JUMPTABLE(int,												\
		_ESCAPE(NAME),											\
		_ESCAPE(int foo, int bar),									\
		-1,												\
		_ESCAPE(ARRAY),											\
		_ESCAPE(INDEXTYPE),										\
		_ESCAPE(INDEXNAME),										\
		_ESCAPE(INDEXVALUE),										\
		_ESCAPE(INDEXBITS),										\
		foo,												\
		bar)

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
