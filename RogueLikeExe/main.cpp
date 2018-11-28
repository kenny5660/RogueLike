#include "pch.h"

#include <iostream>

int main() {
  auto window = initscr();
  keypad(stdscr, TRUE);
  curs_set(0);
  mvprintw(5, 5, "Hello, World!");
  if (getch() == KEY_UP) {
   mvaddch(15, 15, '#');
  mvprintw(8, 8, "Hello, World!");
  }
  getch();
  endwin();
  std::cout << "Thanks that play,game athor kenny5660!\n";
}
