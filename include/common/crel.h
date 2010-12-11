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
typedef struct crel_attr_constraints * crel_attr_constraints_t;

//  attribute list structure definition:
struct crel_attr
{
  int index;
  char *name;
  int length;
  crel_attr_constraints_t constraints;
};
typedef struct crel_attr * crel_attr_t;

//  relation table structure definition
struct crel
{
  char *name;
  char *file_loc;
  int next_order_available;
  crel_attr_t attr_list;
};
typedef struct crel * crel_t;

//  function declarations
//  creating a new relational table; returns the new table
crel_t new_reltable();
//  delete a relational table; returns the deleted table with all other
//  references removed
crel_t del_reltable();

//  add attribute to a table; returns 0 for successful
int add_attribute(crel_t, crel_attr_t);
//  remove attribute from a table; returns a pointer to the removed attribute
crel_attr_t rem_attribute(crel_t, crel_attr_t);
//  change attribute name; returns a pointer to the changed attribute
crel_attr_t ch_attribute(crel_attr_t, char *);
//  find an attribute by name in a table
crel_attr_t find_attribute(crel_t, char *);

//  set an attribute to be a primary key; returns
int
#endif
