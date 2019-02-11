#include "CppUnitTest.h"
#include "stdafx.h"
#define TEST_CASE_DIRECTORY std::string("C:\\Users\\misha\\YandexDisk\\OneDrive\\Projects\\C++\\RogueLike\\RogueLikeTest")

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RogueLikeTest {
TEST_CLASS(GameConfigTest){
  public :

      TEST_METHOD(constructor_and_get_test){
		  std::shared_ptr<GameConfig> game_config(new GameConfig(TEST_CASE_DIRECTORY +"\\test_game_config.json"));
		  Zombie ideal_zm;
          ideal_zm.set_hp(LimitedValue(7, 7,0));
		  ideal_zm.set_mp(LimitedValue(10, 10,0));
          ideal_zm.Set_damage(2);
          ideal_zm.Set_texture('Z');
          ideal_zm.Set_speed(1);
          Assert::AreEqual(game_config->Get_zombie().get_hp().get_max(),
                           ideal_zm.get_hp().get_max());
          Assert::AreEqual(game_config->Get_zombie().get_hp().get_min(),
                           ideal_zm.get_hp().get_min());
          Assert::AreEqual(game_config->Get_zombie().get_hp().get_value(),
                           ideal_zm.get_hp().get_value());
          Assert::AreEqual(game_config->Get_zombie().get_mp().get_max(),
                           ideal_zm.get_mp().get_max());
          Assert::AreEqual(game_config->Get_zombie().get_mp().get_min(),
                           ideal_zm.get_mp().get_min());
          Assert::AreEqual(game_config->Get_zombie().get_mp().get_value(),
                           ideal_zm.get_mp().get_value());
          Assert::AreEqual(game_config->Get_zombie().Get_damage(),
                           ideal_zm.Get_damage());
          Assert::AreEqual(game_config->Get_zombie().Get_texture(),
                           ideal_zm.Get_texture());
          Assert::AreEqual(game_config->Get_zombie().Get_speed(),
                           ideal_zm.Get_speed());

		  Knight ideal_kn;
		  ideal_kn.Set_damage_projectile(3);
		  ideal_kn.Set_speed_projectile(6);
		  Assert::AreEqual(game_config->Get_knight().Get_damage_projectile(),
						   ideal_kn.Get_damage_projectile());
          Assert::AreEqual(game_config->Get_knight().Get_speed_projectile(),
                      ideal_kn.Get_speed_projectile());
		  Wall ideal_wl;
          ideal_wl.Set_texture('#');
		  Assert::AreEqual(game_config->Get_wall().Get_texture(),
                           ideal_wl.Get_texture());
		  AidKit ideal_kit;
          ideal_kit.Set_texture('+');
          ideal_kit.Set_hp_regen(5);
          Assert::AreEqual(game_config->Get_aid_kit().Get_texture(),
                           ideal_kit.Get_texture());
          Assert::AreEqual(game_config->Get_aid_kit().Get_hp_regen(),
                           ideal_kit.Get_hp_regen());

		  Dragon ideal_dg;
		  ideal_dg.Set_damage_projectile(2);
		  ideal_dg.Set_speed_projectile(7);
		  Assert::AreEqual(game_config->Get_dragon().Get_damage_projectile(),
                      ideal_dg.Get_damage_projectile());
          Assert::AreEqual(game_config->Get_dragon().Get_speed_projectile(),
                      ideal_dg.Get_speed_projectile());

      }

};
}