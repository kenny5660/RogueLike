#include "pch.h"
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
GameConfig::GameConfig(std::string path) {
	rapidjson::Document doc;
	std::ifstream config_file(path); 
	std::string config_str;
}
Zombie& GameConfig::get_zombie() { return zombie; }
Knight& GameConfig::get_knight() { return knight; }
Wall& GameConfig::get_wall() { return wall; }