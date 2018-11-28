#pragma once
#include "pch.h"

class Scene {
 public:
  Scene();
  ~Scene();
  void Update();
  void Draw();

 protected:
  GameDatabase gameObjects;
};

class Dungeon_map : Scene {
 public:
  Dungeon_map(std::istream& textMap);

 private:
  void parse_file(std::istream& textMap);
};