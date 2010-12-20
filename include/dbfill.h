#ifndef _DB_FILL_
#define _DB_FILL_
//  dbfill.h
//  Header file for module that reads in a database dictionary and creates relations based on a db fill script
//  Matthew A. Terry (terrym@uwindsor.ca)
//  ===========================================================================
#include <curses.h>
#include <form.h>
#include "error.h"
#include "crel.h"

//  dbcompile menu
int run_dbfill();

//  read in the file at the given .dic file and reconstruct the table based off the
//    content given there
crel_table_p build_table(char *);
//  read in the .lst file given and build new relations and insert them into the
//    database
int build_relations(crel_table_p, char *);
#endif
