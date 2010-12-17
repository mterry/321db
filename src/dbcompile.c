//  dbcompile.c
//  Reads in a database script which generates the final database dictionary
//  Matthew A. Terry (terrym@uwindsor.ca)
//  ===========================================================================
//  include statements
#include <curses.h>
#include <form.h>
#include <stdio.h>

//  dbcompile menu
int run_dbcompile()
{
  //  fields for the dbcompile form:
  //    - full location for the database build script
  //    - full location for the database dictionary storage directory
  FIELD *field[3];
  FORM *dbcompile_form;

  int row, col;
  char ch;

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
    switch((unsigned int) ch)
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

  // unpost the form and free memory
  unpost_form(dbcompile_form);
  free_form(dbcompile_form);  
  free_field(field[0]);
  free_field(field[1]);

  return 0;
}

//  save the compiled database definition to a file
//  read in the database file
//  parse the database file
//  construct the database table
