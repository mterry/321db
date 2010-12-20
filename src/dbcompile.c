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
    store_path = "home/mat/prog/cs321/321db/etc/db_store/";
  }

  mvprintw(row-1, 0, "script_path=\"%s\" and store_path=\"%s\" Press any key to continue.", script_path, store_path);

  refresh();
  getch();
  clear();

  // create the new database from the given script path
  // vars declaration
  crel_table_p *database;

  if((database = read_db_definition(script_path, store_path)) == NULL)
  {
    unpost_form(dbcompile_form);
    free_form(dbcompile_form);
    free_field(field[0]);
    free_field(field[1]);
    free_field(field[2]);

    return ERROR_BADALLOC;
  }

  getch();
  clear();
 
  free(database);

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

/// -- TODO --
//  reads in and parses the database definition file; returns an array of relational
//    tables; returns NULL on failure
crel_table_p * read_db_definition(const char *path, const char *store_path)
{
  //  variable declarations
  FILE *loc;
  crel_table_p *database;
  int table_count, line_length, step;
  enum TRIM t;
  char *full_store_path;

  //  variable initialization
  table_count = 1;
  line_length = 10;
  step = 0;
  if((database = (crel_table_p *) calloc(table_count, sizeof(crel_table_p))) == NULL)
  {
    fclose(loc);
    return NULL;
  }

  t = TRIM_RIGHT;

  if((loc = fopen(path, "r")) == NULL)
  {
    free(database);
    return NULL;
  }

  while(!feof(loc))
  {
    //  variable declarations for block
    char **token_list, buf[255], *str;
    int i, j;

    //  variable init
    i = 0;
    str = trim(fgets(buf, 255, loc), isgraph, t);
    if((token_list = (char **) calloc(line_length, sizeof(char *))) == NULL)
    {
      free(database);
      fclose(loc);
      return NULL;
    }
    
    token_list[i] = strtok(str, " ,;");
    for(; (token_list[i]) != NULL; ++i)
    {
      if((i+1) == line_length)
      {
        line_length += 10;
        token_list = (char **) realloc(token_list, line_length*sizeof(char *));
      }
      token_list[i+1] = strtok(NULL, " ,;");
    }

    // parse token list
    if(((strcmp(token_list[0], "TABLE")) == 0) && (step == 0))
    {
      full_store_path = (char *) calloc(256, sizeof(char));

      strcpy(full_store_path, store_path);
      strcat(full_store_path, "db_data");
      strcat(full_store_path, token_list[1]);
      strcat(full_store_path, ".dat");

      database[table_count-1] = new_table(token_list[1], full_store_path);

      if((strcmp(token_list[2], "(")) == 0)
      {
        ++step;
      }
    }
    else if(((strcmp(token_list[0], "ATTR")) == 0) && (step != 0))
    {
      char *name, *type, *len, *pch, *attr_defn;

      name = (char *) calloc(240, sizeof(char));
      type = (char *) calloc(8, sizeof(char));
      len = (char *) calloc(8, sizeof(char));
      attr_defn = (char *) calloc(256, sizeof(char));

      strcpy(name, token_list[1]);
      pch = strtok(token_list[2], "()");
      if ((strcmp(pch, "VARCHAR2")) == 0)
      {
        strcpy(type, "CHAR");
        pch = strtok(NULL, "()");
        strcpy(len, pch);
        strcat(attr_defn, name);
        strcat(attr_defn, " ");
        strcat(attr_defn, type);
        strcat(attr_defn, " ");
        strcat(attr_defn, len);
      }
      else if((strcmp(pch, "NUMBER")) == 0)
      {
        strcpy(type, "INT");
        strcat(attr_defn, name);
        strcat(attr_defn, " ");
        strcat(attr_defn, type);
      }
      else if((strcmp(pch, "DECIMAL")) == 0)
      {
        strcpy(type, "FLOAT");
        strcat(attr_defn, name);
        strcat(attr_defn, " ");
        strcat(attr_defn, type);
      }
      else
      {
        fclose(loc);
        return NULL;
      }
      crel_attr_p attribute = new_attribute(attr_defn);

      insert_attr(database[table_count-1], attribute);
    }
    else if(((strcmp(token_list[0], "(")) == 0) && step == 0)
    {
      ++step;
    }
    else if(((strcmp(token_list[0], ")")) == 0) && step != 0)
    {
      ++table_count;
      --step;
    }
    else
    {
      fclose(loc);
      return NULL;
    }
  }

  fclose(loc);
  return database;
}
/// -- END TODO --
