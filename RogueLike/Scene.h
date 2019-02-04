#pragma once

#include "game_database.h"
#include "GameConfig.h"
const int max_scene_width = 500;
const int max_scene_heght = 500;
enum GameResult { GAME_RESULT_NOT_OVER, GAME_RESULT_WIN, GAME_RESULT_LOSE };
class Scene {
 public:
  Scene();
  void AddObject(std::shared_ptr<GameObject> game_object,bool is_static = false);
  void DelObject(ObjectId id);
  void Update();
  void Draw();
  void ChekColide();
  const GameDatabase& Get_gameObjects();
  GameResult Get_game_result();
  void Set_game_result(GameResult game_over);
  void Set_elapsed_time(double elapsed_time);
  int Get_width();
  int Get_height();
  double Get_elapsed_time();
 protected:
  GameDatabase gameObjects_;
  int width_;
  int height_;
  GameResult game_result_ = GAME_RESULT_NOT_OVER;
  double elapsed_time_ = 0;
};

class DungeonMap : public Scene {
 public:
  DungeonMap(
      std::istream& textMap, std::shared_ptr<Knight> kn,
             std::shared_ptr<GameConfig> game_config);
  void SpawnKnight();
  void SpawnPrincess();
  void Set_pos_spawn_knight(Point pos);
  Point Get_pos_sawn_knight();
  void Set_pos_spawn_princess(Point pos);
  Point Get_pos_sawn_princess();
  std::shared_ptr<Knight> Get_Knight();
  std::shared_ptr<GameConfig> Get_game_config();
 private:
  std::shared_ptr<Princess> pr_;
  std::shared_ptr<Knight> kn_;
  Point pos_spawn_knight_;
  Point pos_spawn_princess_;
  void ParseFile(std::istream& textMap);
  std::shared_ptr<GameConfig> game_config_;
};