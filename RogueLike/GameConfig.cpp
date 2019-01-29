#include "pch.h"
#include "rapidjson/document.h"
#include "rapidjson/rapidjson.h"
void Entity_set_from_json(Entity& ent, rapidjson::Value& val) {
  ent.get_hp().set_max(val["hp"]["max"].GetInt());
  ent.get_hp().set_min(val["hp"]["min"].GetInt());
  ent.get_hp().set_value(val["hp"]["value"].GetInt());
  ent.get_mp().set_max(val["mp"]["max"].GetInt());
  ent.get_mp().set_min(val["mp"]["min"].GetInt());
  ent.get_mp().set_value(val["mp"]["value"].GetInt());
  ent.Set_damage(val["damage"].GetInt());
  ent.Set_texture(val["texture"].GetString()[0]);
}
GameConfig::GameConfig(std::string path) {
  rapidjson::Document doc;
  std::ifstream config_file(path);
  std::string config_str(std::istreambuf_iterator<char>(config_file), {});
  doc.Parse(config_str.c_str());
  Entity_set_from_json(zombie, doc["zombie"]);
  Entity_set_from_json(knight, doc["knight"]);
  Entity_set_from_json(dragon, doc["dragon"]);
  dragon.Set_radius(doc["dragon"]["radius"].GetInt());
  dragon.Set_damage_projectile(doc["dragon"]["projectile_damage"].GetInt());
  wall.Set_texture(doc["wall"]["texture"].GetString()[0]);
  aid_kit.Set_texture(doc["aid_kit"]["texture"].GetString()[0]);
  aid_kit.Set_hp_regen(doc["aid_kit"]["hp_regen"].GetInt());
}
const Zombie& GameConfig::Get_zombie() { return zombie; }
const Knight& GameConfig::Get_knight() { return knight; }
const Wall& GameConfig::Get_wall() { return wall; }

const AidKit& GameConfig::Get_aid_kit() { return aid_kit; }

const Dragon& GameConfig::Get_dragon() { return dragon; }
