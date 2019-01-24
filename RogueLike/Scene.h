#pragma once
#include "pch.h"
const int max_scene_width = 500;
const int max_scene_heght = 500;

class Scene {
 public:
  Scene();
  void AddObject(std::shared_ptr<GameObject> game_object);
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
  DungeonMap(std::istream& textMap, std::shared_ptr<Knight> kn);
  void spawn_knight();
  void set_pos_spawn(Point pos);
  Point get_pos_sawn();
  Knight& getKnight();
 private:
  std::shared_ptr<Knight> kn_;
  Point pos_spawn_;
  void parse_file(std::istream& textMap);


};