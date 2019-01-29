#pragma once
#include "pch.h"
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
 private:
  Zombie zombie;
  Knight knight;
  Wall wall;
  AidKit aid_kit;
  Dragon dragon;
};