#ifndef _CREL_H_
#define _CREL_H_
//  crel.h
//  Header file for a basic relational data structure in C
//  Matthew A. Terry (terrym@uwindsor.ca)
//  ===========================================================================
#include "error.h"
#include <string.h>
#include <limits.h>
#include <float.h>
#include <stdlib.h>
#include <stdio.h>

//  data types for attributes
struct crel_attr
{
  char *name;
  char *type;
  int length;
};
typedef struct crel_attr crel_attr_t;
typedef crel_attr_t * crel_attr_p;

//  data types for relations
union crel_data
{
  char c_content[255];
  int i_content;
  double f_content;
};
typedef union crel_data crel_data_t;
typedef crel_data_t * crel_data_p;

struct crel_relation
{
  crel_data_p fields;
};
typedef struct crel_relation crel_relation_t;
typedef crel_relation_t * crel_relation_p;

//  data type for the table itself
struct crel_table
{
  char *name;
  char *loc;
  int relation_count;
  int attribute_count;
  crel_attr_p *attribute_list;
  crel_relation_p *relations;
};
typedef struct crel_table crel_table_t;
typedef crel_table_t * crel_table_p;

//  new relation; returns a pointer to the created relation with a stored 1D array
//    of crel_data_t;
crel_relation_p new_relation(crel_attr_p *, char *);
//  new table; returns a pointer to the created table with a variable number of 
//    relations stored
crel_table_p new_table(char *, char *);
//  new attribute; returns a pointer to the created attribute
crel_attr_p new_attribute(char *);

//  insert attribute to table
int insert_attr(crel_table_p, crel_attr_p);
//  remove attribute from table
int rem_attr(crel_table_p, int);
//  insert relation to table
int insert_rel(crel_table_p, crel_relation_p);
//  remove relation from table
int rem_rel(crel_table_p, int);

//  to string functions
//  table to string
char * crel_table_to_string(crel_table_p);
//  attribute to string
char * crel_attr_to_string(crel_attr_p);
#endif
