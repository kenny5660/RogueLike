#pragma once
#include "pch.h"
class GameConfig;
#include "GameObject.h"
class GameConfig {
 public:
  GameConfig(std::string path);
  Zombie& Get_zombie();
  Knight& Get_knight();
  Wall& Get_wall();
  AidKit& Get_aid_kit();
 private:
  Zombie zombie;
  Knight knight;
  Wall wall;
  AidKit aid_kit;
};