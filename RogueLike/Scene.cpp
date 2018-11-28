#include "pch.h"

#include "Scene.h"

Scene::Scene() {}
void Scene::AddObject(GameObject& game_object) {
  gameObjects_.Insert(game_object);
}
void Scene::DelObject(ObjectId id) { gameObjects_.Remove(id); }
void Scene::Update() {
  auto vec_objects = gameObjects_.Data();
  for (auto it = vec_objects.begin(); it != vec_objects.end(); it++) {
    (*it).Update();
  }
}

void Scene::Draw() {
  auto vec_objects = gameObjects_.Data();
  for (auto it = vec_objects.begin(); it != vec_objects.end(); it++) {
    (*it).Draw();
  }
}

void create_Wall(DungeonMap& map, const Point& pos) { 
	GameObject wall = Wall(pos);
	map.AddObject(wall); 
}
void create_EmptyBlock(DungeonMap& map, const Point& pos) {
  GameObject empty = EmptyBlock(pos);
  map.AddObject(empty);
}

const std::map<char, void (*)(DungeonMap&,const Point&)> creators_map = {
    {'#', &create_Wall},
    {'.', &create_EmptyBlock},

};

DungeonMap::DungeonMap(std::istream& textMap) { parse_file(textMap); }

void DungeonMap::parse_file(std::istream& textMap) {
  int curY = 0;
  char line[max_scene_width + 1];
  while (textMap.getline(line, max_scene_width)) {
    for (int i = 0; i < max_scene_width && line[i] != '\n'; ++i) {
      creators_map.at(line[i])(*this,Point(i,curY));
    }
    curY++;
  }
}
