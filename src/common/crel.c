//  crel.h
//  General relation class
//  Matthew A. Terry (terrym@uwindsor.ca)
//  A general relational data structure and functions for accessing and modifying
//  the relation.
//  ----------------------------------------------------------------------------
#include <string.h>
#include <stdlib.h>
#include "common/crel.h"

//  function definitions
//  creating a new relational table; returns the new table
crel_t new_reltable()
{
  crel_t new_table = (crel_t) malloc(sizeof(crel_t);
  new_table.next_index = 0;
  new_table->attr_list = NULL;
  return new_table;
}
//  delete a relational table; returns the deleted table with all other
//  references removed
crel_t rem_reltable(crel_t table_to_remove)
{
  int i;

  for (i=0; i<table_to_remove.next_index; i++)
  {
    crel_attr_t temp_attribute = rem_attribute_by_pointer(table_to_remove, \
      table_to_remove->attr_list);
    free(temp_attribute);
  }

  
}

//  add attribute to a table; returns 0 for successful
int add_attribute(crel_t table, char *attr_name)
{
  return 0;
}
//  remove attribute from a table by pointer; returns a pointer to the removed attribute
crel_attr_t rem_attribute_by_pointer(crel_t table, crel_attr_t target)
{
}
//  remove attribute from a table by name; returns a pointer to the removed attribute
crel_attr_t rem_attribute_by_name(crel_t table, char *attr_name)
{
}
//  change attribute name; returns a pointer to the changed attribute
crel_attr_t ch_attribute(crel_t table, char *target, char *new_name)
{
}
//  find an attribute by name in a table
crel_attr_t find_attribute_by_name(crel_t table, char *attr_name)
{
}
//  find an attribute by index number in a table
crel_attr_t find_attribute_by_index(crel_t table, int attr_index)
{
}

//  set an attribute to be a primary key; returns 0 for successful
int set_primary_key(crel_attr_t target)
{
  return 0;
}
//  remove the primary key status for an attribute; returns 0 for successful
int rem_primary_key(crel_attr_t target)
{
  return 0;
}
