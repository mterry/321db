#ifndef _DB_COMPILE_
#define _DB_COMPILE_
//  dbcompile.h
//  Header file for module that reads in a database script which generates the final database dictionary
//  Matthew A. Terry (terrym@uwindsor.ca)
//  ===========================================================================
#include <curses.h>
#include <form.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error.h"
#include "crel.h"
#include "trim.h"

// dbcompile menu
int run_dbcompile();

//  read field buffer and remove leading and trailing spaces;
//    returns the truncated string
//  -- DEPRECATED == use trim() instead
char * get_field_buffer(FIELD *);
//  -- END DEPRECATED

//  parse the database definition file; returns an array of relational tables;
//    returns NULL on failure
crel_table_p * read_db_definition(char *, char *);
//  saves a constructed table dictionary to file; returns 0 if successful;
//    returns error_code on failure
int save_table(crel_table_p);
#endif
