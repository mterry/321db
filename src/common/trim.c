//  trim.c
//  Generic function for trimming unwanted text from a string (using functions from ctype.h)
//  Paul Preney (paul@preney.ca)
//  ===========================================================================
#include "trim.h"

char *trim(char *str, int(*istrimmable)(int), enum TRIM t)
{
  char *beg;

  if (t == TRIM_LEFT || t == TRIM_BOTH)
  {
    char *p;

    // find the first non-trimmable character
    for (beg = str; *beg != '\0' && !istrimmable(*beg); ++beg)
      ;

    // shift the string contents...
    if (beg != str)
    {
      for (p = str; *beg != '\0'; ++p, ++beg)
      {
        *p = *beg;
      }
      *p = *beg;
    }
  }

  if (t == TRIM_RIGHT || t == TRIM_BOTH)
  {
    char *end = str+strlen(str);

    // find the last non-trimmable character
    if (end != str)
    {
      --end;
    }

    for (; end != str && !istrimmable(*end); --end)
      ;

    //Truncate the string...
    if (end == str && istrimmable(*end))
    {
      *end = '\0';
    }
    else
    {
      end[1] = '\0';
    }
  }

  return str;
}
