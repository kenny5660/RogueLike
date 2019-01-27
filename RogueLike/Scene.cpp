#include "pch.h"
Scene::Scene() {}
void Scene::AddObject(std::shared_ptr<GameObject> game_object, bool is_static) {
  gameObjects_.Insert(game_object, is_static);
}
void Scene::DelObject(ObjectId id) { gameObjects_.Remove(id); }
void Scene::Update() {
  auto vec_objects = gameObjects_.Data();
  for (auto it = vec_objects.begin(); it != vec_objects.end(); it++) {
    (**it).Update();
  }
}
void Scene::ChekColide() {
  auto vec_objects = gameObjects_.Data();
  auto active_objects = gameObjects_.Data_non_static();
  for (auto it = vec_objects.begin(); it != vec_objects.end(); it++) {
    for (auto it_col = active_objects.begin(); it_col != active_objects.end();
         it_col++) {
      if ((*it)->get_id() != (*it_col)->get_id()) {
        if ((*it)->get_pos() == (*it_col)->get_pos()) {
          (*it)->Collide(**it_col);
        }
      }
    }
  }
}

void Scene::Draw() {
  auto vec_objects = gameObjects_.Data();
  for (auto it = vec_objects.begin(); it != vec_objects.end(); it++) {
    (**it).Draw();
  }
}

void create_Wall(DungeonMap& map, const Point& pos) {
  map.AddObject(std::shared_ptr<GameObject>(new Wall(map.get_game_config()->get_wall(),pos)), true);
}
void create_Zombie(DungeonMap& map, const Point& pos) {
  map.AddObject(std::shared_ptr<GameObject>(
      new Zombie(map.get_game_config()->get_zombie(), pos)));
}

void set_spawn_knight(DungeonMap& map, const Point& pos) {
  map.set_pos_spawn(pos);
}

const std::map<char, void (*)(DungeonMap&, const Point&)> creators_map = {
    {'#', &create_Wall}, {'Z', &create_Zombie}, {'K', &set_spawn_knight}};

DungeonMap::DungeonMap(std::istream& textMap, std::shared_ptr<Knight> kn,
                       std::shared_ptr<GameConfig> game_config)
    : kn_(kn),game_config_(game_config) {
  parse_file(textMap);
}
void DungeonMap::spawn_knight() {
  kn_->set_pos(pos_spawn_);
  AddObject(kn_);
}
Knight& DungeonMap::getKnight() { return *kn_; }
std::shared_ptr<GameConfig> DungeonMap::get_game_config() {
  return game_config_;
}
void DungeonMap::set_pos_spawn(Point pos) { pos_spawn_ = pos; }
Point DungeonMap::get_pos_sawn() { return pos_spawn_; }

void DungeonMap::parse_file(std::istream& textMap) {
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

    heght_ = std::max(heght_, curY);
    curY++;
  }
}
