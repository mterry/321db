#ifndef _DB_COMPILE_
#define _DB_COMPILE_
//  dbcompile.h
//  Header file for module that reads in a database script which generates the final database dictionary
//  Matthew A. Terry (terrym@uwindsor.ca)
//  ===========================================================================
#include <curses.h>
#include <form.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "error.h"

enum TRIM
{
  TRIM_LEFT,
  TRIM_RIGHT,
  TRIM_BOTH
};

// dbcompile menu
int run_dbcompile();

//  uses the is***** functions from ctypes.h to trim a string of unwanted characters
//    returns the truncated string
char * trim(char *, int (*istrimmable)(int), enum TRIM);
//  read field buffer and remove leading and trailing spaces;
//    returns the truncated string
//    DEPRECATED == use trim() instead
char * get_field_buffer(FIELD *);
int read_db_definition(char *);
#endif
