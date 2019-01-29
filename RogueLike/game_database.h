#pragma once
#include "GameObject.h"
#include <functional>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>

class GameDatabase {
 public:
  GameDatabase();
  void Insert(std::shared_ptr<GameObject> game_object,bool is_static = false);

  void Remove(ObjectId id);
  int Total() const;
  std::pair<std::shared_ptr<GameObject>, bool> DataById(ObjectId id) const;
  std::vector<std::shared_ptr<GameObject>> Data() const;
  std::vector<std::shared_ptr<GameObject>> Data_non_static()const;

 private:
  ObjectId incID = 0;
  std::map<ObjectId, std::shared_ptr<GameObject>, std::greater<ObjectId>> data_base_;
  std::set<ObjectId> static_objects_;
};
