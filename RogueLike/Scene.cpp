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
      if ((*it)->Get_id() != (*it_col)->Get_id()) {
        if ((*it)->Get_pos() == (*it_col)->Get_pos()) {
          (*it)->Collide(**it_col);
        }
      }
    }
  }
}

bool Scene::Get_is_game_over() { return is_game_over_; }

void Scene::Set_is_game_over(bool is_game_over) {
  is_game_over_ = is_game_over;
}

void Scene::Set_elapsed_time(double elapsed_time) {
  elapsed_time_ = elapsed_time;
}

double Scene::Get_elapsed_time() { return elapsed_time_; }


void Scene::Draw() {
  auto vec_objects = gameObjects_.Data();
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
  map.AddObject(std::shared_ptr<GameObject>(
      new Zombie(map.Get_game_config()->Get_zombie(), pos, &map)));
}
void create_dragon(DungeonMap& map, const Point& pos) {
  map.AddObject(std::shared_ptr<GameObject>(
      new Dragon(map.Get_game_config()->Get_dragon(), pos, &map)));
}

void set_spawn_knight(DungeonMap& map, const Point& pos) {
  map.Set_pos_spawn(pos);
}

const std::map<char, void (*)(DungeonMap&, const Point&)> creators_map = {
    {'#', &create_Wall},
    {'Z', &create_Zombie},
    {'K', &set_spawn_knight},
    {'+', &create_aid_kit}, 
	{'D', &create_dragon},
};

DungeonMap::DungeonMap(std::istream& textMap, std::shared_ptr<Knight> kn,
                       std::shared_ptr<GameConfig> game_config)
    : kn_(kn), game_config_(game_config) {
  ParseFile(textMap);
  AddObject(std::shared_ptr<GameObject>(
                new GuiPlayer({width_ + 10.0, 5}, this->kn_)),
            true);
}
void DungeonMap::SpawnKnight() {
  kn_->Set_pos(pos_spawn_);
  kn_->Set_parent_scene(this);
  AddObject(kn_);
}
Knight& DungeonMap::Get_Knight() { return *kn_; }
std::shared_ptr<GameConfig> DungeonMap::Get_game_config() {
  return game_config_;
}
void DungeonMap::Set_pos_spawn(Point pos) { pos_spawn_ = pos; }
Point DungeonMap::Get_pos_sawn() { return pos_spawn_; }

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

    heght_ = std::max(heght_, curY);
    curY++;
  }
}
