//============================================================================
// Name        : DesignByContract.h
// Author      : Serge Demeyer
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Serge Demeyer - University of Antwerp
// Description : Declarations for design by contract in C++
//============================================================================

/*

THIS SHIT DOESNT WORK FOR WHATEVER REASON (Windows) SO I'M DISABLING IT.
JUST REPLACE IT WITH THIS CODE WHENEVER YOURE ON CANCER LINUX AND IT WILL WORK LIKE A CHARM
FUCK

#include <assert.h>

#define REQUIRE(assertion, what) \
	if (!(assertion)) __assert (what, __FILE__, __LINE__)

#define ENSURE(assertion, what) \
	if (!(assertion)) __assert (what, __FILE__, __LINE__)
*/

#define REQUIRE(assertion, what)
#define ENSURE(assertion, what)