//  dbcompile.c
//  Reads in a database script which generates the final database dictionary
//  Matthew A. Terry (terrym@uwindsor.ca)
//  ===========================================================================
//  include statements
#include "dbcompile.h"

//  dbcompile menu
int run_dbcompile()
{
  //  fields for the dbcompile form:
  //    - full location for the database build script
  //    - full location for the database dictionary storage directory
  FIELD *field[3];
  FORM *dbcompile_form;

  int row, col;
  int ch;

  char *store_path;
  char *script_path;

  clear();

  getmaxyx(stdscr, row, col);

  //  init fields
  field[0] = new_field(1, col, 2, 0, 0, 0);
  field[1] = new_field(1, col, 5, 0, 0, 0);
  field[2] = NULL;

  //  set field options
  set_field_back(field[0], A_UNDERLINE);
  set_field_back(field[0], O_AUTOSKIP);
  set_field_back(field[1], A_UNDERLINE);
  set_field_back(field[1], O_AUTOSKIP);

  // create the form
  dbcompile_form = new_form(field);
  post_form(dbcompile_form);
  refresh();

  mvprintw(1, 0, "Enter the full path of the definition script.");
  mvprintw(4, 0, "Enter the full path to the database dictionary directory.");
  mvprintw(6, 0, "Press ENTER to submit, the down and up arrows to move between fields.");
  refresh();

  // loop through to get user input
  while((ch = getch()) != KEY_ENTER)
  {
    switch(ch)
    {
      case KEY_DOWN:
        // go to next field
        form_driver(dbcompile_form, REQ_NEXT_FIELD);
        // go to the end of the present buffer; leaves nicely at the last character
        form_driver(dbcompile_form, REQ_END_LINE);
        break;
      case KEY_UP:
        // go to previous field
        form_driver(dbcompile_form, REQ_PREV_FIELD);
        form_driver(dbcompile_form, REQ_END_LINE);
        break;
      default:
        // if this is a normal character, it gets printed
        form_driver(dbcompile_form, ch);
    }
  }

  if((script_path = get_field_buffer(field[0], col)) == NULL)
  {
    return -1;
  }
  if((store_path = get_field_buffer(field[1], col)) == NULL)
  {
    return -1;
  }

  // unpost the form and free memory
  unpost_form(dbcompile_form);
  free_form(dbcompile_form);  
  free_field(field[0]);
  free_field(field[1]);

  return 0;
}

//  read field buffer and remove leading and trailing spaces; returns the truncated string
char * get_field_buffer(FIELD *field, int buf_length)
{
  char *field_contents, *tmp;
  int i;

  field_contents = (char *)malloc(sizeof(char));

  if ((tmp = field_buffer(field, buf_length)) == NULL)
  {
    return NULL;
  }

  for (i=0; i<buf_length; i++)
  {
    int c;
    c = *(tmp+i);
    if (!isspace(c))
    {
      strncat(field_contents, (tmp+i), 1);
    }
  }
  free(tmp);
  return field_contents;
}
//  save the compiled database definition to a file
//  read in the database file
//  parse the database file
//  construct the database table
