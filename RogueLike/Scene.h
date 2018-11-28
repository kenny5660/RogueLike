#pragma once
#include "pch.h"
const int max_scene_width = 500;
const int max_scene_heght = 500;

class Scene {
 public:
  Scene();
  void AddObject(GameObject& game_object);
  void DelObject(ObjectId id);
  void Update();
  void Draw();

 protected:
  GameDatabase gameObjects_;
  int width_;
  int heght_;
};

class DungeonMap : public Scene {
 public:
  DungeonMap(std::istream& textMap);

 private:
  void parse_file(std::istream& textMap);
  void create_Wall(Point pos);
  void create_EmptyBlock(Point pos);


};