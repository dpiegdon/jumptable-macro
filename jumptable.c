
#include <stdio.h>

#define _ESCAPE(...) __VA_ARGS__

#define JUMPTABLE(RETTYPE, NAME, ARGS, BADVALUE, ARRAY, INDEXTYPE, INDEXNAME, INDEXVALUE, INDEXBITS, ...)	\
	RETTYPE NAME(ARGS){											\
		const RETTYPE (*jTable[1 << INDEXBITS])(ARGS) = {ARRAY};					\
		INDEXTYPE INDEXNAME = (INDEXVALUE) & ((1 << INDEXBITS)-1);					\
		RETTYPE (*fun)(ARGS) = jTable[INDEXNAME];							\
		if (NULL == fun)										\
			return BADVALUE;									\
		else												\
			return fun(__VA_ARGS__);								\
	}

#define MYJUMPTABLE(NAME, ARRAY, INDEXTYPE, INDEXNAME, INDEXVALUE, INDEXBITS)			\
	JUMPTABLE(int, NAME, _ESCAPE(unsigned value, int foo), -1, _ESCAPE(ARRAY), INDEXTYPE, INDEXNAME, INDEXVALUE, INDEXBITS, value, foo)


int d0(unsigned value, int foo)
{
	printf("A %u %d\n", value, foo);
	return 1;
}

int d1(unsigned value, int foo)
{
	printf("B %u %d\n", value, foo);
	return 1;
}

int d2(unsigned value, int foo)
{
	printf("C %u %d\n", value, foo);
	return 1;
}

int d3(unsigned value, int foo)
{
	printf("D %u %d\n", value, foo);
	return 1;
}

MYJUMPTABLE(decode, _ESCAPE(d0, d1, d2, d3), unsigned, p0, value & 0x3, 3);

int main(int argc, char**argv)
{
	printf("ret %d\n", decode(argc, argc & 3));
}
