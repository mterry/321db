//  dbcompile.c
//  reads in a database script which generates the final database dictionary
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
  FIELD *field[4];
  FORM *dbcompile_form;

  int row, col;
  int ch;

  char *store_path;
  char *script_path;
  char *file_contents;

  clear();

  getmaxyx(stdscr, row, col);

  //  init fields
  field[0] = new_field(1, col/4, 2, 0, 0, 0);
  field[1] = new_field(1, col/4, 5, 0, 0, 0);
  field[2] = new_field(1, 8, row-1, 0, 0, 0);
  field[3] = NULL;

  //  set field options
  set_field_back(field[0], A_UNDERLINE);
  set_field_back(field[1], A_UNDERLINE);
  set_field_back(field[2], A_REVERSE);
  set_field_fore(field[2], A_REVERSE);

  field_opts_off(field[0], O_NULLOK);
  field_opts_off(field[0], O_AUTOSKIP);
  field_opts_off(field[0], O_STATIC);
  field_opts_off(field[1], O_AUTOSKIP);
  field_opts_off(field[1], O_STATIC);
  field_opts_off(field[2], O_AUTOSKIP);
  field_opts_off(field[2], O_EDIT);

  set_field_buffer(field[2], 0, " SUBMIT ");

  // create the form
  dbcompile_form = new_form(field);
  post_form(dbcompile_form);
  refresh();

  mvprintw(1, 0, "Enter the full path of the definition script.");
  mvprintw(4, 0, "OPTIONAL: Enter the full path to the database dictionary directory.");
  mvprintw(6, 0, "Use, the down and up arrows to move between fields, keypad Enter to select.");
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
  clear();

  crel_t *table_list;

  if((table_list = parse_db_definition(script_path, store_path)) == NULL)
  {
    // unpost the form and free memory
    unpost_form(dbcompile_form);
    free_form(dbcompile_form);  
    free_field(field[0]);
    free_field(field[1]);
    free_field(field[2]);
 
    return ERROR_BADTYPE;
  }

  refresh();
  getch();
  clear();

  // unpost the form and free memory
  unpost_form(dbcompile_form);
  free_form(dbcompile_form);  
  free_field(field[0]);
  free_field(field[1]);
  free_field(field[2]);
 
  return 0;
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
//  -- END DEPRECATED

//  reads in and parses the database definition file; returns an array of relational
//    tables; returns NULL on failure
crel_t * parse_db_definition(char *path, char *store_path)
{
  FILE *loc;
  crel_t *table_list;
  int line_number, step, table_count;

  enum TRIM t = TRIM_BOTH;
  line_number = 0;
  step = 0;
  table_count = 0;
  table_list = (crel_t *) calloc(10, sizeof(crel_t));

  if ((loc = fopen(path, "r")) == NULL)
  {
    return NULL;
  }

  while (!feof(loc))
  {
    char *current_line, buf[255], **token_list, **ptl;

    token_list = (char **) malloc(sizeof(char*));
    ptl = token_list;

    fgets(buf, 255, loc);
    
    // trim out all spaces, non-printing characters found before and after text
    current_line = trim(buf, isgraph, t);

    // split the current line into tokens delimited by ", ;"
    ptl[0] = strtok(current_line, " ,;");
    int i;

    i = 0;
    while(ptl[++i] != NULL)
    {
      ptl[i] = strtok(NULL, " ,;");
    }

    // if token == "TABLE", then expect the next token = "name" and the next = '(';
    //   increase step
    if(((strcmp(token_list[0], "TABLE")) == 0) && (step == 0))
    {
      table_list[table_count] = new_reltable(token_list[1], store_path);
      ++step;
    }
    // else if token == "ATTR" && step != 0, then create a new attribute with
    //   attr_name=token_list+1...
    else if(((strcmp(token_list[0], "ATTR")) == 0) && (step != 0))
    {
      char *type, *name;
      int len;

      name = token_list[1];
      type = strtok(token_list[2], "()");
      len = (int) atol(strtok(NULL, "()"));

      crel_attr_t new_attr = add_attribute(table_list[table_count], name, type, len);

      /// TODO:
      if (token_list[3] != NULL)
      {
        if ((strcmp(token_list[3], "PRIMARY")) == 0)
        {
        }
      }
      /// END TODO;
    }
    // else if token == ')', then decrease step
    else if((strcmp(token_list[0], ")")) == 0)
    {
      table_count++;
      table_list++;
      --step;
    }
    else if((strcmp(token_list[0], "(")) == 0)
    {
      ++step;
    }
    // else return NULL
    else
    {
      free(token_list);
      free(table_list);
      return NULL;
    }
    free(token_list);
  }

  fclose(loc);
  return table_list;
}
