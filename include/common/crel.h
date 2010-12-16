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
  char *type;
  int length;
  crel_attr_constraints_t constraint_list;
  struct crel_attr *next_attribute;
};
typedef struct crel_attr * crel_attr_t;

//  relation table structure definition
struct crel
{
  char *name;
  char *file_loc;
  int next_index;
  crel_attr_t attr_list;
};
typedef struct crel * crel_t;

//  function declarations
//  creating a new relational table; returns the new table
crel_t new_reltable();
//  delete a relational table; returns the deleted table with all other
//  references removed
crel_t rem_reltable();

//  add attribute to a table; returns 0 for successful
int add_attribute(crel_t, char *, char *);
//  remove attribute from a table by pointer; returns a pointer to the removed attribute
crel_attr_t rem_attribute_by_pointer(crel_t, crel_attr_t);
//  remove attribute from a table by name; returns a pointer to the removed attribute
crel_attr_t rem_attribute_by_name(crel_t, char *);
//  change attribute name; returns a pointer to the changed attribute
crel_attr_t ch_attribute(crel_t, char *, char *);
//  find an attribute by name in a table
crel_attr_t find_attribute_by_name(crel_t, char *);
//  find an attribute by index number in a table
crel_attr_t find_attribute_by_index(crel_t, int);

//  set an attribute to be a primary key; returns 0 for successful
int set_primary_key(crel_attr_t);
//  remove the primary key status for an attribute; returns 0 for successful
int rem_primary_key(crel_attr_t);
#endif
