#pragma once
#include "pch.h"

#include "game_database.h"
#include "GameConfig.h"
const int max_scene_width = 500;
const int max_scene_heght = 500;

class Scene {
 public:
  Scene();
  void AddObject(std::shared_ptr<GameObject> game_object,bool is_static = false);
  void DelObject(ObjectId id);
  void Update();
  void Draw();
  void ChekColide();
  bool get_is_game_over();
  void set_is_game_over(bool is_game_over);
 protected:
  GameDatabase gameObjects_;
  int width_;
  int heght_;
  bool is_game_over_ = false;
};

class DungeonMap : public Scene {
 public:
  DungeonMap(std::istream& textMap, std::shared_ptr<Knight> kn,
             std::shared_ptr<GameConfig> game_config);
  void spawn_knight();
  void set_pos_spawn(Point pos);
  Point get_pos_sawn();
  Knight& getKnight();
  std::shared_ptr<GameConfig> get_game_config();
 private:
  std::shared_ptr<Knight> kn_;
  Point pos_spawn_;
  void parse_file(std::istream& textMap);
  std::shared_ptr<GameConfig> game_config_;
};