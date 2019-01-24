#include "pch.h"
#include <iostream>
#include <fstream>
void ReadConfig(std::string path) {

}

void StartGame() {
  auto window = initscr();
  int keyDown = '+';
  keypad(stdscr, TRUE);
  curs_set(0);
  noecho();
  raw();
  std::ifstream inputMap("maps/1lvl.map");
  Knight K_player({-1,-1});
  DungeonMap map_1lvl(inputMap, K_player);
  map_1lvl.spawn_knight();
  map_1lvl.Update();
  map_1lvl.Draw();
  while (keyDown != 'q') {
    keyDown = getch();
    clear();
    map_1lvl.getKnight().key_pressed(keyDown);
    map_1lvl.Update();
    map_1lvl.Draw();
    //mvprintw(5, 5, "Hello, World!");
    //if (keyDown == KEY_UP) {
    //mvaddch(15, 15, '#');
    //mvprintw(8, 8, "Hello, World!");
		//}
  }
  endwin();
}