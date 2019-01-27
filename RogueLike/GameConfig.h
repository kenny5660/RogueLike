#pragma once
#include "pch.h"
class GameConfig;
#include "GameObject.h"
class GameConfig {
 public:
  GameConfig(std::string path);
  Zombie& get_zombie();
  Knight& get_knight();
  Wall& get_wall();
  Aid_kit& get_aid_kit();
 private:
  Zombie zombie;
  Knight knight;
  Wall wall;
  Aid_kit aid_kit;
};