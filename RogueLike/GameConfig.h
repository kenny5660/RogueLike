#pragma once
//#include "pch.h"
class GameConfig;
#include "GameObject.h"
class GameConfig {
 public:
  GameConfig(std::string path);
 const Zombie& Get_zombie();
 const Knight& Get_knight();
 const Wall& Get_wall();
 const AidKit& Get_aid_kit();
 const Dragon& Get_dragon();
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