#pragma once
//#include "pch.h"
class GameConfig;
#include "GameObject.h"
class GameConfig {
 public:
  GameConfig(std::string path);
  Zombie& Get_zombie();
  Knight& Get_knight();
  Wall& Get_wall();
  AidKit& Get_aid_kit();
  Dragon& Get_dragon();
  const std::map<GameResult, std::string>& Get_game_result_text_map();
  const std::map<std::string, int>& Get_control_keys();

 private:
  Zombie zombie_;
  Knight knight_;
  Wall wall_;
  AidKit aid_kit_;
  Dragon dragon_;
  std::map<GameResult, std::string> game_result_text_map_;
  std::map<std::string, int> control_keys_;
};