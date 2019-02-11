#include "pch.h"
#include "rapidjson/document.h"
#include "rapidjson/rapidjson.h"
void Entity_set_from_json(Entity& ent, rapidjson::Value& val) {
  ent.set_hp(LimitedValue(val["hp"]["value"].GetInt(), val["hp"]["max"].GetInt(),
                          val["hp"]["min"].GetInt()));
  ent.set_mp(LimitedValue(val["mp"]["value"].GetInt(),
                          val["mp"]["max"].GetInt(),
                          val["mp"]["min"].GetInt()));
  ent.Set_damage(val["damage"].GetInt());
  ent.Set_texture(val["texture"].GetString()[0]);
  ent.Set_speed(val["speed"].GetDouble());
}
GameConfig::GameConfig(std::string path) {
  rapidjson::Document doc;
  std::ifstream config_file(path);
  std::string config_str(std::istreambuf_iterator<char>(config_file), {});
  doc.Parse(config_str.c_str());
  Entity_set_from_json(zombie_, doc["zombie"]);
  Entity_set_from_json(knight_, doc["knight"]);
  Entity_set_from_json(dragon_, doc["dragon"]);
  dragon_.Set_radius(doc["dragon"]["radius"].GetInt());
  dragon_.Set_damage_projectile(doc["dragon"]["projectile_damage"].GetInt());
  dragon_.Set_speed_projectile(doc["dragon"]["speed_projectile"].GetDouble());
  knight_.Set_damage_projectile(doc["knight"]["projectile_damage"].GetInt());
  knight_.Set_speed_projectile(doc["knight"]["speed_projectile"].GetDouble());
  wall_.Set_texture(doc["wall"]["texture"].GetString()[0]);
  aid_kit_.Set_texture(doc["aid_kit"]["texture"].GetString()[0]);
  aid_kit_.Set_hp_regen(doc["aid_kit"]["hp_regen"].GetInt());
  game_result_text_map_.insert(std::make_pair(GameResult::WIN,doc["win_text"].GetString()));
  game_result_text_map_.insert(std::make_pair(GameResult::LOSE,doc["lose_text"].GetString()));
  game_result_text_map_.insert(
      std::make_pair(GameResult::NOT_OVER, doc["not_over_text"].GetString()));
  for (auto& elm : doc["control_keys"].GetObject()) {
    if (elm.value.IsInt()) {
    control_keys_.insert(std::make_pair(elm.name.GetString(), elm.value.GetInt()));
	}
    if (elm.value.IsString()) {
      control_keys_.insert(
          std::make_pair(elm.name.GetString(), elm.value.GetString()[0]));
    }
  }
}
Zombie& GameConfig::Get_zombie() { return zombie_; }
Knight& GameConfig::Get_knight() { return knight_; }
Wall& GameConfig::Get_wall() { return wall_; }
AidKit& GameConfig::Get_aid_kit() { return aid_kit_; }
Dragon& GameConfig::Get_dragon() { return dragon_; }

const std::map<GameResult, std::string>&
GameConfig::Get_game_result_text_map() {
  return game_result_text_map_;
}

const std::map<std::string, int>& GameConfig::Get_control_keys() {
  return control_keys_;
}
