#ifndef _C_REL_
#define _C_REL_
//  crel.h
//  Relational data structure and functions for manipulating relations in C
//  Matthew A. Terry (terrym@uwindsor.ca)
//  ===========================================================================
//  include statements
#include <string.h>
#include <stdlib.h>

//  Implementation notes:
//    Relations are organized into tables, which have a number of elements:
//      - table name (string)
//      - data storage location (string)
//      - attribute definitions
//        - attribute name (string)
//        - attribute length (int)
//        - attribute constraints
//          - primary key

//  attribute constraints structure definition:
struct crel_attr_constraints
{
  unsigned int primary_key  : 1;
};
typedef struct crel_attr_constraints crel_attr_constraints_t;

//  attribute list structure definition:
struct crel_attr
{
  char *name;
  int length;
  crel_attr_constraints_t* constraints;
};
typedef struct crel_attr crel_attr_t;

//  relation table structure definition
struct crel
{
  char *name;
  char *file_loc;
  crel_attr_t *attr_list;
};
typedef struct crel crel_t;

//  function declarations
//  creating a new relational table
crel_t new_reltable();



#endif
