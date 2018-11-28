#include "pch.h"

bool operator>(const GameObject& a, const GameObject& b) {
  return a.get_id() > b.get_id();
}

class GameDatabase {
 public:
  GameDatabase() : incID(0) {}
  void Insert(GameObject& game_object) {
    game_object.set_id(incID++);
    auto it = data_base_.find(game_object.get_id());
    if (it == data_base_.end()) {
      data_base_.insert(
          std::pair<ObjectId, GameObject>(game_object.get_id(), game_object));
      deleted.erase(game_object.get_id());
    } else {
      auto itPos = data_base_pos.find(
          std::make_pair((*it).second.get_pos().get_int_X(),
                                       (*it).second.get_pos().get_int_Y()));
      (*itPos).second.erase((*it).first);
      (*it).second = game_object;
      deleted.erase(game_object.get_id());
    }

    auto itPos = data_base_pos.find(std::make_pair(
        game_object.get_pos().get_int_X(), game_object.get_pos().get_int_Y()));
    if (itPos == data_base_pos.end()) {
      std::set<ObjectId, std::greater<ObjectId>> setId;
      setId.insert(game_object.get_id());
      data_base_pos.insert(
          make_pair(std::make_pair(game_object.get_pos().get_int_X(),
                              game_object.get_pos().get_int_Y()),
                    setId));
    } else {
      (*itPos).second.insert(game_object.get_id());
    }
  }

  void Remove(ObjectId id) {
    data_base_.erase(id);
    deleted.insert(id);
  }

  std::pair<GameObject, bool> DataById(ObjectId id) const {
    auto it = data_base_.find(id);
    auto itDel = deleted.find(id);
    if (it != data_base_.end() && itDel == deleted.end()) {
      return std::make_pair((*it).second, true);
    } else {
      return std::make_pair(GameObject(), false);
    }
  }

  std::vector<GameObject> DataByPosition(size_t x, size_t y) const {
    std::vector<GameObject> out;
    auto itName = data_base_pos.find(std::make_pair(x, y));
    if (itName != data_base_pos.end()) {
      for (auto it = (*itName).second.begin(); it != (*itName).second.end();
           ++it) {
        auto itDel = deleted.find(*it);

        if (itDel == deleted.end()) {
          auto itData = data_base_.find(*it);
          out.push_back((*itData).second);
        }
      }
    }
    return out;
  }

  std::vector<GameObject> Data() const {
    std::vector<GameObject> out;
    for (auto it = data_base_.begin(); it != data_base_.end(); ++it) {
      auto itDel = deleted.find((*it).first);
      if (itDel == deleted.end()) {
        out.push_back((*it).second);
      }
    }

    return out;
  }

 private:
  ObjectId incID = 0;
  std::map<ObjectId, GameObject, std::greater<ObjectId>> data_base_;
  std::map<std::pair<int, int>, std::set<ObjectId, std::greater<ObjectId>>> data_base_pos;
  std::set<ObjectId> deleted;
};
