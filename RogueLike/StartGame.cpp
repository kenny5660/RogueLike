#include "pch.h"

#include <time.h>
#include <fstream>
#include <iostream>
#include <thread>

void Init_curses() {
  auto window = initscr();
  keypad(stdscr, TRUE);
  curs_set(0);
  noecho();
  raw();
  nodelay(stdscr, TRUE);
  srand(time(0));
}
void StartGame() {
  Init_curses();
  int keyDown = '+';
  std::ifstream inputMap("maps/1lvl.dmap");
  std::shared_ptr<GameConfig> game_config(new GameConfig("game_config.json"));
  std::shared_ptr<Knight> K_player(
      new Knight(game_config->Get_knight(), {-1, -1}, nullptr));
  std::unique_ptr<DungeonMap> map_1lvl(
      new DungeonMap(inputMap, K_player, game_config));
  map_1lvl->SpawnKnight();
  map_1lvl->Draw();
  while (keyDown != 'q' && !map_1lvl->Get_is_game_over()) {
    auto begin = std::chrono::steady_clock::now();
    keyDown = getch();
    clear();
    map_1lvl->Get_Knight().key_pressed(keyDown);
    map_1lvl->Update();
    map_1lvl->ChekColide();
    map_1lvl->Draw();
    auto end = std::chrono::steady_clock::now();
    double elapsed_time = (end - begin).count() / 1000000000.0;
    map_1lvl->Set_elapsed_time(elapsed_time);
    // flushinp();
  }
  endwin();
  inputMap.close();
  std::cout << "Your points: " << K_player->Get_points() << std::endl;
}