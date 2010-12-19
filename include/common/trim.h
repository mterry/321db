//  trim.h
//  Generic function for trimming unwanted text from a string (using functions from ctype.h)
//  Paul Preney (paul@preney.ca)
//  ===========================================================================
#include <ctype.h>
#include <string.h>

enum TRIM
{
  TRIM_LEFT,
  TRIM_RIGHT,
  TRIM_BOTH
};

//  uses the is***** functions from ctypes.h to trim a string of unwanted characters
//    returns the truncated string
char *trim(char *, int (*istrimmable)(int), enum TRIM);
