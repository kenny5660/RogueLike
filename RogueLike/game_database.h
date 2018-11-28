#pragma once
#include <functional>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>

class GameDatabase {
 public:
  GameDatabase();
  void Insert(GameObject& game_object);

  void Remove(ObjectId id);

  std::pair<GameObject, bool> DataById(ObjectId id) const;

  std::vector<GameObject> DataByPosition(Point pos) const;

  std::vector<GameObject> Data() const;

 private:
  ObjectId incID = 0;
  std::map<ObjectId, GameObject, std::greater<ObjectId>> data_base_;
  std::map<std::pair<int, int>, std::set<ObjectId, std::greater<ObjectId>>>
      data_base_pos;
  std::set<ObjectId> deleted;
};
