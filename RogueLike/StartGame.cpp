#include "pch.h"

#include <time.h>
#include <fstream>
#include <iostream>
#include <thread>

void Init—urses() {
  auto window = initscr();
  keypad(stdscr, TRUE);
  curs_set(0);
  noecho();
  raw();
  nodelay(stdscr, TRUE);
  srand(time(0));
}
void StartGame() {
  Init—urses();
  int keyDown = ERR;
  std::ifstream input_map("maps/1lvl.dmap");
  std::shared_ptr<GameConfig> game_config = std::make_shared<GameConfig>(std::string("game_config.json"));
  std::shared_ptr<Knight> K_player  = std::make_shared<Knight>(game_config->Get_knight(), Point{-1, -1}, nullptr,game_config->Get_control_keys());
  std::unique_ptr<DungeonMap> map_1lvl(
      new DungeonMap(input_map, K_player, game_config));
  map_1lvl->SpawnKnight();
  map_1lvl->Draw();
  while (keyDown != game_config->Get_control_keys().at("exit") &&
         map_1lvl->Get_game_result() == GameResult::NOT_OVER) {
    auto begin = std::chrono::steady_clock::now();
    keyDown = getch();
    clear();
    map_1lvl->Get_Knight()->KeyPressed(keyDown);
    map_1lvl->Update();
    map_1lvl->CheckCollide();
    map_1lvl->Draw();
    auto end = std::chrono::steady_clock::now();
    double elapsed_time = (end - begin).count() / 1000000000.0;
    map_1lvl->Set_elapsed_time(elapsed_time);
    // flushinp();
  }
  endwin();
  input_map.close();
  const std::map<GameResult, std::string>& game_result_text_map =
      game_config->Get_game_result_text_map();
  std::cout << game_result_text_map.at(map_1lvl->Get_game_result())
            << " Your points: " << K_player->Get_points() << std::endl;
}