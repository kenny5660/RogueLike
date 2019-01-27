#pragma once
#include "pch.h"
#include "GameObject.h"
class GameConfig {
 public:
  GameConfig(std::string path);
  Zombie& get_zombie();
  Knight& get_knight();
  Wall& get_wall();

 private:
  Zombie zombie;
  Knight knight;
  Wall wall;
};