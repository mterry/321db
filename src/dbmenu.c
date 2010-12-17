//  dbmenu.c
//  Menu for DB321 and main program loop
//  Matthew A. Terry (terrym@uwindsor.ca)
//  ---------------------------------------------------------------------------
#include <curses.h>
#include "error.h"

int run_menu(char);

int main(int argc, char **argv)
{
  //  open the curses terminal and set primary behaviour
  initscr();
  cbreak();
  noecho();
  nonl();
  intrflush(stdscr, FALSE);
  keypad(stdscr, TRUE);

  // the number of rows and columns in the terminal
  int row, col;

  char cinput;

  getmaxyx(stdscr, row, col);

  //  initial screen output 
  mvprintw(row/2, 0, "Welcome to 321db. This is a database management system created for the course 60-321 at the University of Windsor. It is the culminating project for the course, and attempts to congeal all the topics we covered in class together into a cohesive whole.\n");
  printw("This code is provided as is and no warranty is provided. Use at your own risk.\n");
  printw("Press any key to continue.\n");
  refresh();

  // wait for input from any key
  getch();

  // clear the screen and reposition the cursor to (0, 0)
  clear();
  move(0, 0);
  printw("Please select your choice.\n");
  printw("0: compile a database from an existing dictionary file.\n");
  printw("1: input records into the existing database.\n");
  printw("2: change or delete recordst in the existing database.\n");
  printw("3: query the existing database for information.\n");
  printw("q: quit 321db.\n");

  while(1)
  {
    move(row-1, 0);
    printw("Enter your choice on the keyboard.\n");
    refresh();
    cinput = getch();
    
    int choice;
    if((choice = run_menu(cinput)) == 0xFF)
    {
      clear();
      move(0, 0);
      printw("Exiting. Press any key to continue.\n");
      refresh();
      getch();
      break;
    }
    else if(choice == 0xFE)
    {
      move(row-1, 0);
      printw("Please enter 0, 1, 2, 3, or \'q\'.\n");
      refresh();
      continue;
    }
  }

  //  close the curses terminal
  endwin();

  return (int) ERROR_OK;
}

int run_menu(char input)
{
  switch(input)
  {
    case '0':
    case '1':
    case '2':
    case '3':
    case 'q':
      return 0xFF;
      break;
    default:
      return 0xFE;
  }
    return ERROR_OK;
}
