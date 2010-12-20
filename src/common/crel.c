//  crel.c
//  Source for a basic relational data structure in C
//  Matthew A. Terry (terrym@uwindsor.ca)
//  ===========================================================================
#include "crel.h"

//  new relation; returns the created relation with a stored 1D array of crel_data_t;
//    parses the character string given to it, tokenizes it, and puts each token
//    into the corresponding crel_data; then checks for data consistency against 
//    the given attribute list before it returns; if there is an issue in creating the
//    relation, or with the consistency check, the function returns NULL
crel_relation_p new_relation(crel_attr_p *attribute_list, char *relation_content)
{
  //  variable declarations
  char *pch;
  crel_relation_t new_relation;
  int i, base_count;

  //  variable init
  pch = strtok(relation_content, " ");
  i = 0;
  base_count = 10;
  new_relation.fields = (crel_data_p) calloc(base_count, sizeof(crel_data_t));

  // tokenize and insert loop
  while(pch != NULL)
  {
    if((strcmp(attribute_list[i]->type, "CHAR")) == 0)
    {
      if(strlen(pch) > attribute_list[i]->length)
      {
        return NULL;
      }
      strcpy(new_relation.fields[i].c_content, pch);
    }
    else if((strcmp(attribute_list[i]->type, "INT")) == 0)
    {
      int pch_convert;
      if(((pch_convert = atol(pch)) > INT_MAX) || (pch_convert < INT_MIN))
      {
        return NULL;
      }
      new_relation.fields[i].i_content = pch_convert;
    }
    else if((strcmp(attribute_list[i]->type, "FLOAT")) == 0)
    {
      double pch_convert;
      if(((pch_convert = atof(pch)) > DBL_MAX) || (pch_convert < DBL_MIN))
      {
        return NULL;
      }
      new_relation.fields[i].f_content = pch_convert;
    }
    else
    {
      return NULL;
    }
    pch = strtok(NULL, " ");
    ++i;
    if (i == base_count)
    {
      base_count += 10;
      new_relation.fields = (crel_data_p) realloc(new_relation.fields, \
        base_count*(sizeof(crel_data_t)));
    }
  }
  crel_relation_p new_relation_p = &new_relation;

  return new_relation_p;
}
//  new table; returns the created table
crel_table_p new_table(char *name, char *loc)
{
  //  variable declarations
  crel_table_t new_table;
  
  //  variable init
  new_table.name = (char *) calloc(strlen(name), sizeof(char));
  new_table.loc = (char *) calloc(strlen(loc), sizeof(char));
  strcpy(new_table.name, name);
  strcpy(new_table.loc, loc);
  new_table.relation_count = 1;
  new_table.attribute_count = 1;

  crel_table_p new_table_p = &new_table;

  return new_table_p;
}
//  new attribute; returns the created attribute; it parses the character string given
//    to it, tokenizes it, and then creates a new attribute based on the character
//    string given to it; if there are any errors in creating the new attribute, then
//    the function returns NULL
crel_attr_p new_attribute(char *attribute_content)
{
  //  variable declarations
  char *pch;
  crel_attr_t new_attribute;

  //  variable init
  pch = strtok(attribute_content, " ");
  new_attribute.name = (char *) calloc(strlen(pch), sizeof(char));
  strcpy(new_attribute.name, pch);

  pch = strtok(NULL, " ");
  if((strcmp(pch, "CHAR")) == 0)
  {
    new_attribute.type = (char *) calloc(strlen(pch), sizeof(char));
    strcpy(new_attribute.type, pch);
    pch = strtok(NULL, " ");
    new_attribute.length = (int) atol(pch);
  }
  else if((strcmp(pch, "INT")) == 0)
  {
    new_attribute.type = (char *) calloc(strlen(pch), sizeof(char));
    strcpy(new_attribute.type, pch);
    new_attribute.length = 0;
  }
  else if((strcmp(pch, "FLOAT")) == 0)
  {
    new_attribute.type = (char *) calloc(strlen(pch), sizeof(char));
    strcpy(new_attribute.type, pch);
    new_attribute.length = 0;
  }
  else
  {
    return NULL;
  }

  crel_attr_p new_attribute_p = &new_attribute;

  return new_attribute_p;
}

//  insert attribute to table; returns 0 if successful, error_code if failed
int insert_attr(crel_table_p target, crel_attr_p attribute)
{
  //  increase attribute count
  target->attribute_count++;
  
  //  reallocate memory in the array
  if((target->attribute_list = (crel_attr_p *) realloc(target->attribute_list, \
    target->attribute_count*(sizeof(crel_attr_p)))) == NULL)
  {
    return ERROR_BADALLOC;
  }

  //  insert the new attribute pointer into the list at the end
  target->attribute_list[target->attribute_count-1] = attribute;

  return 0;
}
//  remove attribute from table; returns 0 if successful, enum ERROR_CODE if failed
int rem_attr(crel_table_p target, int attribute_no)
{
  int i;
  
  free(target->attribute_list[attribute_no]->name);
  free(target->attribute_list[attribute_no]->type);
  target->attribute_list[attribute_no]->length = 0;

  free(target->attribute_list[attribute_no]);

  for (i=attribute_no; i < target->attribute_count; ++i)
  {
    target->attribute_list[i] = target->attribute_list[i+1];
  }

  target->attribute_count--;

  if((target->attribute_list = (crel_attr_p *) realloc(target->attribute_list, \
    (target->attribute_count)*(sizeof(crel_attr_p)))) == NULL)
  {
    return ERROR_BADALLOC;
  }

  return 0;
}
//  insert relation to table; returns 0 if successful, enum ERROR_CODE if failed
int insert_rel(crel_table_p target, crel_relation_p relation)
{
  //  increase relation count
  target->relation_count++;

  //  reallocate memory in the array
  if((target->relations = (crel_relation_p *) realloc(target->relations, \
    (target->relation_count)*(sizeof(crel_relation_p)))) == NULL)
  {
    return ERROR_BADALLOC;
  }

  //  insert the new relation pointer into the list at the end
  target->relations[target->relation_count-1] = relation;

  return 0;
}
//  remove relation from table; returns 0 if successful, enum ERROR_CODE if failed
int rem_rel(crel_table_p target, int relation_no)
{
  int i;

  free(target->relations[relation_no]->fields);
  
  free(target->relations[relation_no]);

  for (i=relation_no; i < target->relation_count; ++i)
  {
    target->relations[i] = target->relations[i+1];
  }

  target->relation_count--;

  if((target->relations = (crel_relation_p *) realloc(target->relations, \
    target->relation_count*(sizeof(crel_attr_p)))) == NULL)
  {
    return ERROR_BADALLOC;
  }
  
  return 0;
}

//  to string functions
//  table to string
char * crel_table_to_string(crel_table_p table)
{
  char *to_string;
  strcat(to_string, table->name);
  strcat(to_string, "\n");
  strcat(to_string, table->loc);
  strcat(to_string, "\n");

  return to_string;
}
//  attribute to string
char * crel_attr_to_string(crel_attr_p attribute)
{
  char *to_string, *int_to_string;

  to_string = (char *) calloc(256, sizeof(char));

  strcat(to_string, attribute->name);
  strcat(to_string, " ");
  strcat(to_string, attribute->type);
  strcat(to_string, " ");
  sprintf(int_to_string, "%d", attribute->length);
  strcat(to_string, int_to_string);

  return to_string;
}
