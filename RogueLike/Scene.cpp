#include "pch.h"

Scene::Scene() {}
void Scene::AddObject(std::shared_ptr<GameObject> game_object, bool is_static) {
  game_objects_.Insert(game_object, is_static);
}
void Scene::DelObject(ObjectId id) { game_objects_.Remove(id); }
void Scene::Update() {
  auto vec_objects = game_objects_.Data();
  for (auto it = vec_objects.begin(); it != vec_objects.end(); it++) {
    (**it).Update();
  }
}
void Scene::CheckCollide() {
  auto vec_objects = game_objects_.Data();
  auto active_objects = game_objects_.Data_non_static();
  for (auto &it : vec_objects) {
    for (auto &it_col : active_objects){
      if (it != it_col) {
        if (it->Get_pos() == it_col->Get_pos()) {
          it->Collide(*it_col);
        }
      }
    }
  }
}

const GameDatabase& Scene::Get_game_objects() { return game_objects_; }

GameResult Scene::Get_game_result() { return game_result_; }

void Scene::Set_game_result(GameResult game_over) { game_result_ = game_over; }

void Scene::Set_elapsed_time(double elapsed_time) {
  elapsed_time_ = elapsed_time;
}

int Scene::Get_width() { return width_; }

int Scene::Get_height() { return height_; }

double Scene::Get_elapsed_time() { return elapsed_time_; }

void Scene::Draw() {
  auto vec_objects = game_objects_.Data();
  for (auto it = vec_objects.begin(); it != vec_objects.end(); it++) {
    (**it).Draw();
  }
}

void create_Wall(DungeonMap& map, const Point& pos) {
  map.AddObject(std::shared_ptr<GameObject>(
                    new Wall(map.Get_game_config()->Get_wall(), pos)),
                true);
}
void create_aid_kit(DungeonMap& map, const Point& pos) {
  map.AddObject(std::shared_ptr<GameObject>(
                    new AidKit(map.Get_game_config()->Get_aid_kit(), pos)),
                true);
}
void create_Zombie(DungeonMap& map, const Point& pos) {
  map.AddObject(std::shared_ptr<GameObject>(new Zombie(
      map.Get_game_config()->Get_zombie(), pos, map.Get_scene_shared_ptr())));
}
void create_dragon(DungeonMap& map, const Point& pos) {
  map.AddObject(std::shared_ptr<GameObject>(new Dragon(
      map.Get_game_config()->Get_dragon(), pos, map.Get_scene_shared_ptr())));
}

void set_spawn_knight(DungeonMap& map, const Point& pos) {
  map.Set_pos_spawn_knight(pos);
}
void set_spawn_princess(DungeonMap& map, const Point& pos) {
  map.Set_pos_spawn_princess(pos);
}

const std::map<char, void (*)(DungeonMap&, const Point&)> creators_map = {
    {'#', &create_Wall},    {'Z', &create_Zombie}, {'K', &set_spawn_knight},
    {'+', &create_aid_kit}, {'D', &create_dragon}, {'P', &set_spawn_princess}};

DungeonMap::DungeonMap(std::istream& textMap, std::shared_ptr<Knight> kn,
                       std::shared_ptr<GameConfig> game_config)
    : kn_(kn), game_config_(game_config), scene_shared_ptr_(this) {
  const double offset_x = 10;
  const double offset_y = 5;

  ParseFile(textMap);
  AddObject(std::shared_ptr<GameObject>(
                new GuiPlayer({width_ + offset_x, offset_y}, this->kn_)),
            true);
  SpawnPrincess();
}
void DungeonMap::SpawnKnight() {
  kn_->Set_pos(pos_spawn_knight_);
  kn_->Set_parent_scene(scene_shared_ptr_);
  AddObject(kn_);
}
void DungeonMap::SpawnPrincess() {
  pr_ = std::shared_ptr<Princess>(new Princess(Point(-1, -1), nullptr));
  pr_->Set_pos(pos_spawn_princess_);
  pr_->Set_parent_scene(scene_shared_ptr_);
  AddObject(pr_);
}
std::shared_ptr<Knight> DungeonMap::Get_Knight() { return kn_; }
std::shared_ptr<GameConfig> DungeonMap::Get_game_config() {
  return game_config_;
}
std::shared_ptr<Scene> DungeonMap::Get_scene_shared_ptr() {
  return scene_shared_ptr_;
}
void DungeonMap::Set_pos_spawn_knight(Point pos) { pos_spawn_knight_ = pos; }
Point DungeonMap::Get_pos_sawn_knight() { return pos_spawn_knight_; }

void DungeonMap::Set_pos_spawn_princess(Point pos) {
  pos_spawn_princess_ = pos;
}

Point DungeonMap::Get_pos_sawn_princess() { return pos_spawn_princess_; }

void DungeonMap::ParseFile(std::istream& textMap) {
  int curY = 0;
  char line[max_scene_width + 1];
  while (textMap.getline(line, max_scene_width)) {
    for (int i = 0; i < max_scene_width && line[i] != '\0'; ++i) {
      auto it = creators_map.find(line[i]);
      if (it != creators_map.end()) {
        it->second(*this, Point(i, curY));
      }
      width_ = std::max(width_, i);
    }

    height_ = std::max(height_, curY);
    curY++;
  }
}
