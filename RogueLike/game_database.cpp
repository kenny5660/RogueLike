#include "pch.h"

bool operator>(const GameObject& a, const GameObject& b) {
  return a.Get_id() > b.Get_id();
}

GameDatabase::GameDatabase() : incID(0) {}

void GameDatabase::Insert(std::shared_ptr<GameObject> game_object,
                          bool is_static) {
  game_object->Set_id(incID++);
  data_base_.insert(std::pair<ObjectId, std::shared_ptr<GameObject>>(
      game_object->Get_id(), game_object));
  if (is_static) {
    static_objects_.insert(game_object->Get_id());
  }
}

void GameDatabase::Remove(ObjectId id) {
  data_base_.erase(id);
  if (static_objects_.find(id) != static_objects_.end()) {
    static_objects_.erase(id);
  }
}

int GameDatabase::Total() const { return data_base_.size(); }

std::pair<std::shared_ptr<GameObject>, bool> GameDatabase::DataById(
    ObjectId id) const {
  auto it = data_base_.find(id);
  if (it != data_base_.end()) {
    return std::make_pair(it->second, true);
  } else {
    return std::make_pair(nullptr, false);
  }
}

std::vector<std::shared_ptr<GameObject>> GameDatabase::Data() const {
  std::vector<std::shared_ptr<GameObject>> out;
  for (auto it = data_base_.begin(); it != data_base_.end(); ++it) {
    out.push_back(it->second);
  }
  return out;
}
std::vector<std::shared_ptr<GameObject>> GameDatabase::Data_non_static() const {
  std::vector<std::shared_ptr<GameObject>> out;
  for (auto it = data_base_.begin(); it != data_base_.end(); ++it) {
    auto itStatic = static_objects_.find((*it).first);
    if (itStatic == static_objects_.end()) {
      out.push_back(it->second);
    }
  }
  return out;
}