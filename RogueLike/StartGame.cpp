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
  std::ifstream inputMap("maps/1lvl.dmap");
  std::shared_ptr<Knight> K_player(new Knight({-1, -1}));
  std::unique_ptr<DungeonMap> map_1lvl(new DungeonMap(inputMap, K_player));
  map_1lvl->spawn_knight();
  map_1lvl->Update();
  map_1lvl->Draw();
  while (keyDown != 'q') {
    keyDown = getch();
    clear();
    map_1lvl->getKnight().key_pressed(keyDown);
    map_1lvl->Update();
    map_1lvl->ChekColide();
    map_1lvl->Draw();
   // flushinp();
  }
  endwin();
  inputMap.close();
}