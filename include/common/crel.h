#ifndef _C_REL_
#define _C_REL_
//  crel.h
//  Relational data structure and functions for manipulating relations in C
//  Matthew A. Terry (terrym@uwindsor.ca)
//  ===========================================================================
//  include statements
#include <string.h>
#include <stdlib.h>
#include "error.h"

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
  unsigned char primary_key : 1;
  unsigned char foreign_key : 1;
  struct crel * foreign_key_p;
};
typedef struct crel_attr_constraints * crel_attr_constraints_t;

//  attribute structure definition:
struct crel_attr
{
  char *name;
  char *type;
  int len;
  crel_attr_constraints_t constraints;
};
typedef struct crel_attr * crel_attr_t;

//  relation table structure definition
struct crel
{
  char *name;
  char *loc;
  int attr_list_len;
  crel_attr_t *attr_list;
};
typedef struct crel * crel_t;

//  function declarations
//  creating a new relational table; returns the new table
crel_t new_reltable();
//  delete a relational table; returns the delected table with all other
//  references removed;
crel_t rem_reltable();

//  add attribute to a table; returns 0 for successful
int add_attribute(crel_t, char *, char *, int);
//  remove attribute from a table; returns the removed attribute if successful,
//  NULL if failed
crel_attr_t rem_attribute(crel_t, crel_attr_t);
//  change attribute name; returns 0 for successful, error_code for failure
int ch_attr_name(crel_attr_t, char *);
//  change attribute type; returns 0 for successful, error_code for failure
int ch_attr_type(crel_attr_t, char *);

//  set an attribute to be a primary key; returns 0 for successful
int set_primary_key(crel_attr_t);
//  remove the primary key status for an attribute; returns 0 for successful
int rem_primary_key(crel_attr_t);
//  set an attribute to be a foreign key; returns 0 for successful
int set_foreign_key(crel_attr_t, crel_t);
//  remove the foreign key status for an attribute; returns 0 for successful
int rem_foreign_key(crel_attr_t);
#endif
