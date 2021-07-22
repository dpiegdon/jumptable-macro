#pragma once

/*
 * macro-hell to generate jumptables that can be stacked
 */

/* macro to escape parameters, so that commas ',' can be passed */
#define _ESCAPE(...) __VA_ARGS__

/*
 * macro to create a generic jumptable
 *
 * RETTYPE: value returned by functions in jumptable.
 *
 * NAME: name of function to be defined that will evaluate jumptable.
 *
 * ARGS: full type/arguments list of that function.
 *             e.g. _ESCAPE(int foo, unsigned bar)
 *
 * CALLEEARGS: full arguments to be passed along to selected jumptable entry.
 *             likely the same as above, but without types.
 *             e.g. _ESCAPE(foo, bar)
 *
 * BADVALUE: value to be returned if selected jumptable entry was NULL.
 *
 * ARRAY: full list of jumptargets that defines jumptable.
 *        e.g. (target0, target1, target2, target3)
 *
 * INDEXTYPE: type to be used for index-variable
 *            e.g unsigned
 *
 * INDEXNAME: name to be used for index-variable
 *
 * INDEXVALUE: expression to be assigned to index-variable; this actually selects jumptable entry.
 *             e.g. _ESCAPE((foo >> 4) & 0x3)
 *
 * INDEXBITS: number of bits the index-selector has. ARRAY needs to have 2^INDEXBITS entries.
 */
#define JUMPTABLE(RETTYPE, NAME, ARGS, CALLEEARGS, BADVALUE, ARRAY, INDEXTYPE, INDEXNAME, INDEXVALUE, INDEXBITS)	\
	RETTYPE NAME(ARGS) {												\
		static const RETTYPE (*const jTable[1 << INDEXBITS]) (ARGS) = {ARRAY};					\
		INDEXTYPE INDEXNAME = (INDEXVALUE) & ((1 << INDEXBITS)-1);						\
		RETTYPE (*fun) (ARGS) = jTable[INDEXNAME];								\
		if (NULL == fun)											\
			return BADVALUE;										\
		else													\
			return fun(CALLEEARGS);										\
	}
