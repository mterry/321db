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
  field[0] = new_field(1, col/4, 2, 0, 0, 0);
  field[1] = new_field(1, col/4, 5, 0, 0, 0);
  field[2] = NULL;

  //  set field options
  set_field_back(field[0], A_UNDERLINE);
  set_field_back(field[1], A_UNDERLINE);

  field_opts_off(field[0], O_NULLOK);
  field_opts_off(field[0], O_AUTOSKIP);
  field_opts_off(field[1], O_NULLOK);
  field_opts_off(field[1], O_AUTOSKIP);

  // create the form
  dbcompile_form = new_form(field);
  post_form(dbcompile_form);
  refresh();

  mvprintw(1, 0, "Enter the full path of the definition script.");
  mvprintw(4, 0, "OPTIONAL: Enter the full path to the database dictionary directory.");
  mvprintw(6, 0, "Press Enter on the keypad to submit, the down and up arrows to move between fields.");
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
      case KEY_LEFT:
        // go to previous character
        form_driver(dbcompile_form, REQ_PREV_CHAR);
        break;
      case KEY_RIGHT:
        // go to next character
        form_driver(dbcompile_form, REQ_NEXT_CHAR);
        break;
      case KEY_BACKSPACE:
        // delete previous character
        form_driver(dbcompile_form, REQ_DEL_PREV);
        break;
      case KEY_DC:
        // delete current character
        form_driver(dbcompile_form, REQ_DEL_CHAR);
        break;
      case KEY_HOME:
        form_driver(dbcompile_form, REQ_BEG_FIELD);
        break;
      case KEY_END:
        form_driver(dbcompile_form, REQ_END_FIELD);
        break;
      default:
        // if this is a normal character, it gets printed
        form_driver(dbcompile_form, ch);
    }
  }

  mvprintw(row-2, 0, "script_path before=%s and store_path before=%s", field_buffer(field[0], 0), field_buffer(field[1], 0));
  refresh();

  enum TRIM t = TRIM_BOTH;

  if (((script_path = trim(field_buffer(field[0], 0), isgraph, t)) == NULL) \
    || ((store_path = trim(field_buffer(field[1], 0), isgraph, t)) == NULL))
  {
    return ERROR_BADTYPE;
  }

  if ((field_status(field[1])) == FALSE)
  {
    store_path = "../etc/db_store/";
  }

  mvprintw(row-1, 0, "script_path=\"%s\" and store_path=\"%s\" Press any key to continue.", script_path, store_path);

  refresh();
  getch();

  // unpost the form and free memory
  unpost_form(dbcompile_form);
  free_form(dbcompile_form);  
  free_field(field[0]);
  free_field(field[1]);
  
  clear();

  return 0;
}

//  uses the is***** functions from ctypes.h to trim a string of unwanted characters
//    returns the truncated string
char * trim(char *str, int (*istrimmable)(int), enum TRIM t)
{
  char *beg;

  if (t == TRIM_LEFT || t == TRIM_BOTH)
  {
    char *p;

    // find the first non-trimmable character
    for (beg = str; *beg != '\0' && !istrimmable(*beg); ++beg)
      ;

    // shift the string contents...
    if (beg != str)
    {
      for (p = str; *beg != '\0'; ++p, ++beg)
      {
        *p = *beg;
      }
      *p = *beg;
    }
  }

  if (t == TRIM_RIGHT || t == TRIM_BOTH)
  {
    char *end = str+strlen(str);

    // find the last non-trimmable character
    if (end != str)
    {
      --end;
    }

    for (; end != str && !istrimmable(*end); --end)
      ;

    //Truncate the string...
    if (end == str && istrimmable(*end))
    {
      *end = '\0';
    }
    else
    {
      end[1] = '\0';
    }
  }

  return str;
}

//  read field buffer and remove leading and trailing spaces;
//    returns the truncated string
//    DEPRECATED -- use trim() instead
char * get_field_buffer(FIELD *field)
{
  char *field_contents, *tmp;
  int i;

  field_contents = (char *)malloc(sizeof(char));

  if ((tmp = field_buffer(field, 0)) == NULL)
  {
    return NULL;
  }

  for (i=0; i<strlen(tmp); i++)
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
int read_db_definition(char *path)
{
  FILE *loc;
}
//  parse the database file
//  construct the database table
