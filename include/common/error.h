#ifndef _321_ERROR_
#define _321_ERROR_
//  error.h
//  Error codes and printing/logging functions for such

enum error_code
{
  ERROR_UNKNOWN = -1,
  ERROR_OK = 0,
  ERROR_BADTYPE,
  ERROR_NOENTRY,
  ERROR_OPEN
};

#endif
