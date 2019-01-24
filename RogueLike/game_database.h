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
  void Insert(std::shared_ptr<GameObject> game_object);

  void Remove(ObjectId id);

  std::pair<std::shared_ptr<GameObject>, bool> DataById(ObjectId id) const;

  std::vector<std::shared_ptr<GameObject>> DataByPosition(Point pos) const;

  std::vector<std::shared_ptr<GameObject>> Data() const;

 private:
  ObjectId incID = 0;
  std::map<ObjectId, std::shared_ptr<GameObject>, std::greater<ObjectId>> data_base_;
  std::map<std::pair<int, int>, std::set<ObjectId, std::greater<ObjectId>>>
      data_base_pos;
  std::set<ObjectId> deleted;
};
