#pragma once

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
  const GameDatabase& Get_gameObjects();
  bool Get_is_game_over();
  void Set_is_game_over(bool is_game_over);
  void Set_elapsed_time(double elapsed_time);
  double Get_elapsed_time();
 protected:
  GameDatabase gameObjects_;
  int width_;
  int heght_;
  bool is_game_over_ = false;
  double elapsed_time_ = 0;
};

class DungeonMap : public Scene {
 public:
  DungeonMap(std::istream& textMap, std::shared_ptr<Knight> kn,
             std::shared_ptr<GameConfig> game_config);
  void SpawnKnight();
  void Set_pos_spawn(Point pos);
  Point Get_pos_sawn();
  Knight& Get_Knight();
  std::shared_ptr<GameConfig> Get_game_config();
 private:
  std::shared_ptr<Knight> kn_;
  Point pos_spawn_;
  void ParseFile(std::istream& textMap);
  std::shared_ptr<GameConfig> game_config_;
};