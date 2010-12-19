//  crel.c
//  General relation class
//  Matthew A. Terry (terrym@uwindsor.ca)
//  A general relational data structure and functions for accessing and modifying
//  the relation.
//  ----------------------------------------------------------------------------
#include "crel.h"

//  function definitions
//  creating a new relational table; returns the new table, or NULL for failure
crel_t new_reltable(char *name, char *loc)
{
  // declare vars
  crel_t new_table;

  // init vars
  if((new_table = (crel_t) calloc(1, sizeof(struct crel))) == NULL)
  {
    return NULL;
  }

  // create the attribute list array
  new_table->attr_list = (crel_attr_t *) calloc(1, sizeof(crel_attr_t));
  // populate other fields in the structure
  new_table->name = name;
  new_table->loc = loc;
  new_table->attr_list_len = 0;

  return new_table;
}
//  delete a relational table; returns the deleted table with all other
//  references removed;
crel_t rem_reltable(crel_t table_to_remove)
{
  int i;

  for(i=table_to_remove->attr_list_len; i!=0; --i)
  {
    free(rem_attribute(table_to_remove, table_to_remove->attr_list[i-1]));
  }

  free(table_to_remove->name);
  free(table_to_remove->loc);

  return table_to_remove;
}

//  add attribute to a table; returns a reference to the added attribute for successful;
//    NULL for failure
crel_attr_t add_attribute(crel_t table, char *name, char *type, int len)
{
  crel_attr_t new_attr;

  new_attr = (crel_attr_t) calloc(1, sizeof(struct crel_attr));
  new_attr->constraints = (crel_attr_constraints_t) calloc(1, sizeof(struct crel_attr_constraints));
  new_attr->name = name;
  new_attr->type = type;
  new_attr->len = len;

  table->attr_list[(table->attr_list_len)++] = new_attr;

  return new_attr;
}
//  remove attribute from a table; returns a pointer to the removed attribute
//  returns NULL if no matching attribute is found in the table
crel_attr_t rem_attribute(crel_t table, crel_attr_t attribute)
{
  int i, j;

  for(i=0; i<table->attr_list_len; ++i)
  {
    if((memcmp(attribute, table->attr_list[i], sizeof(crel_attr_t))) == 0)
    {
      break;
    }
  }

  if (i == table->attr_list_len)
  {
    return NULL;
  }

  free(attribute->name);
  free(attribute->type);

  for (j=i+1; j<table->attr_list_len; ++j, ++i)
  {
    table->attr_list[i] = table->attr_list[j];
  }

  table->attr_list[(table->attr_list_len)-1] == NULL;

  table->attr_list_len--;

  return attribute;
}
//  change attribute name; returns 0 if successful, error_code for failure
int ch_attr_name(crel_attr_t attribute, char *name)
{
  return 0;
}
//  change attribute type; returns 0 if successful, error_code for failure
int ch_attr_type(crel_attr_t attribute, char *type)
{
  return 0;
}

/// TODO:
int set_primary_key(crel_attr_t target)
{
  return 0;
}
//  remove the primary key status for an attribute; returns 0 for successful
int rem_primary_key(crel_attr_t target)
{
  return 0;
}
int set_foreign_key(crel_attr_t target, crel_t foreign_target)
{
  return 0;
}
int rem_foreign_key(crel_attr_t target)
{
  return 0;
}
/// END TODO;
