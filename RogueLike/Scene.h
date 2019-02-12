#pragma once

#include "GameConfig.h"
#include "game_database.h"
const int max_scene_width = 500;
const int max_scene_heght = 500;
enum class GameResult { NOT_OVER, WIN, LOSE };
class Scene {
 public:
  explicit Scene();
  void AddObject(std::shared_ptr<GameObject> game_object,
                 bool is_static = false);
  void DelObject(ObjectId id);
  void Update();
  void Draw();
  void CheckCollide();
  const GameDatabase& Get_game_objects();
  GameResult Get_game_result();
  void Set_game_result(GameResult game_over);
  void Set_elapsed_time(double elapsed_time);
  int Get_width();
  int Get_height();
  double Get_elapsed_time();

 protected:
  GameDatabase game_objects_;
  int width_;
  int height_;
  GameResult game_result_ = GameResult::NOT_OVER;
  double elapsed_time_ = 0;
};

class DungeonMap : public Scene, public std::enable_shared_from_this<Scene> {
 public:
  static std::shared_ptr<DungeonMap> create(
      std::istream& textMap, std::shared_ptr<Knight> kn,
      std::shared_ptr<GameConfig> game_config) {
    std::shared_ptr<DungeonMap> p(new DungeonMap(kn, game_config));
    p->init(textMap);
    return p;
  }

  void SpawnKnight();
  void SpawnPrincess();
  void Set_pos_spawn_knight(Point pos);
  Point Get_pos_sawn_knight();
  void Set_pos_spawn_princess(Point pos);
  Point Get_pos_sawn_princess();
  std::shared_ptr<Knight> Get_Knight();
  std::shared_ptr<GameConfig> Get_game_config();
  std::shared_ptr<Scene> Get_shared_ptr() { return shared_from_this(); }

 private:
  DungeonMap(std::shared_ptr<Knight> kn,
             std::shared_ptr<GameConfig> game_config);
  void init(std::istream& textMap);
  std::shared_ptr<Princess> pr_;
  std::shared_ptr<Knight> kn_;
  // std::weak_ptr<Scene> scene_shared_ptr_;
  Point pos_spawn_knight_;
  Point pos_spawn_princess_;
  void ParseFile(std::istream& textMap);
  std::shared_ptr<GameConfig> game_config_;
};