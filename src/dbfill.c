//  dbfill.c
//  reads in a database dictionary and creates relations based on a db fill script
//  Matthew A. Terry (terrym@uwindsor.ca)
//  ===========================================================================
//  include statements
#include "dbfill.h"

//  dbfill menu
int run_dbfill()
{
  return 0;
}

crel_table_p build_table(char *path)
{
  FILE *loc;
  crel_table_p new_table;
  char buf[256][256];
  int i, j;

  if((loc = fopen(path, "r")) == NULL)
  {
    return NULL;
  }

  i = 0;
  while(!feof(loc))
  {
    fgets(buf[i], 256, loc);
    ++i;
  }

  if((new_table = (crel_table_p) malloc(sizeof(crel_table_t)) == NULL || \
    (new_table->name = (char *) calloc(256, sizeof(char))) == NULL|| \
    (new_table->loc = (char *) calloc(256, sizeof(char))) == NULL
  {
    return NULL;
  }

  strcpy(new_table->name, buf[0]);
  strcpy(new_table->loc, buf[1]);
  for (j=2; j<i; j++)
  {
    crel_attr_p attribute;

    attribute = new_attribute(buf[j]);
    insert_attr(new_table, attribute);
  }

  fclose(loc);

  return new_table;
}

int build_relations(crel_table_p target, char *path)
{
  FILE *loc;
  char buf[256][256];
  int i;

  if ((loc = fopen(path, "r")) == NULL)
  {
    return ERROR_BADALLOC;
  }

  
  return 0;
}
