#include "CppUnitTest.h"
#include "stdafx.h"

#include "../RogueLike/Scene.h"
#define TEST_CASE_DIRECTORY std::string("C:\\Users\\misha\\YandexDisk\\OneDrive\\Projects\\C++\\RogueLike\\RogueLikeTest")
//#define TEST_CASE_DIRECTORY std::string(__FILE__)
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace RogueLikeTest {
TEST_CLASS(SceneTest){
  public :

      TEST_METHOD(AddObject_test){
		Scene sc;
		Point pos = {3,3};
		char texture = 'F';
        std::shared_ptr<Knight> kn(new Knight(pos, texture));
        sc.AddObject(kn);
        Assert::AreEqual(sc.Get_gameObjects().DataById(kn->Get_id()).second, true);
		Assert::AreEqual(sc.Get_gameObjects().DataById(kn->Get_id()).first->Get_texture(), texture);
      }
	  TEST_METHOD(DelObject_test){
		Scene sc;
		Point pos = {3,3};
		char texture = 'K';
        std::shared_ptr<Knight> kn(new Knight(pos, texture));
        sc.AddObject(kn);
        sc.DelObject(kn->Get_id());
        Assert::AreEqual(sc.Get_gameObjects().DataById(kn->Get_id()).second, false);
      }
	  TEST_METHOD(Update_test){
		Scene sc;
        sc.Set_elapsed_time(1);
		Point pos = {3,3};
		char texture = 'K';
        std::shared_ptr<Knight> kn(new Knight(pos, texture));
		kn->Set_cur_vec_move({1,0});
        kn->Set_parent_scene(&sc);
        sc.AddObject(kn);
		sc.Update();
        Assert::AreNotEqual(sc.Get_gameObjects().DataById(kn->Get_id()).first->Get_pos().X, pos.X);
      }
	  TEST_METHOD(Draw_test){
        Init_curses();
		Scene sc;
        sc.Set_elapsed_time(1);
		Point pos = {3,3};
		char texture = 'K';
        std::shared_ptr<Knight> kn(new Knight(pos, texture));
		kn->Set_cur_vec_move({1,0});
        kn->Set_parent_scene(&sc);
        sc.AddObject(kn);
		sc.Draw();
        char real_text = mvinch(kn->Get_pos().get_int_Y(), kn->Get_pos().get_int_X());
        Assert::AreEqual(real_text,
            kn->Get_texture());
		endwin();
      }
	  TEST_METHOD(Get_and_set_is_game_over_test) {
		Scene sc;
        sc.Set_is_game_over(true); 
		Assert::AreEqual(sc.Get_is_game_over(), true);
      }
	  TEST_METHOD(Get_and_set_elapsed_time) {
		Scene sc;
        sc.Set_elapsed_time(0.8); 
		Assert::AreEqual(sc.Get_elapsed_time(), 0.8,0.1);
      }


};
TEST_CLASS(DungeonMapTest){
  public :
	  TEST_METHOD(Constructor_test){
		Point pos = {3,3};
		char texture = 'K';
        std::shared_ptr<Knight> kn(new Knight(pos, texture));
		kn->Set_cur_vec_move({1,0});
        std::ifstream inputMap(TEST_CASE_DIRECTORY +"\\test_map.txt");
                std::shared_ptr<GameConfig> game_config(new GameConfig(
                    TEST_CASE_DIRECTORY +"\\test_game_config.json"));
        DungeonMap sc(inputMap, kn, game_config);
        sc.Set_elapsed_time(1);
        kn->Set_parent_scene(&sc);
        Assert::AreEqual(sc.Get_width(), 30);
        Assert::AreEqual(sc.Get_height(), 12);
        Assert::AreEqual(sc.Get_gameObjects().Total(),46);
      }
	  TEST_METHOD(Spawn_test){
        Point pos = {3, 3};
        char texture = 'K';
        std::shared_ptr<Knight> kn(new Knight(pos, texture));
        kn->Set_cur_vec_move({1, 0});
        std::ifstream inputMap(TEST_CASE_DIRECTORY + "\\test_map.txt");
        std::shared_ptr<GameConfig> game_config(
            new GameConfig(TEST_CASE_DIRECTORY + "\\test_game_config.json"));
        DungeonMap sc(inputMap, kn, game_config);
        sc.Set_elapsed_time(1);
        kn->Set_parent_scene(&sc);
        sc.Set_pos_spawn({3,5});
        sc.SpawnKnight();
        Assert::AreEqual(sc.Get_pos_sawn().get_int_X(), kn->Get_pos().get_int_X());
		Assert::AreEqual(sc.Get_pos_sawn().get_int_Y(), kn->Get_pos().get_int_Y());
        Assert::AreEqual(sc.Get_gameObjects().Total(), 47);
      }
	  TEST_METHOD(Get_game_config_test){
        Point pos = {3, 3};
        char texture = 'K';
        std::shared_ptr<Knight> kn(new Knight(pos, texture));
        kn->Set_cur_vec_move({1, 0});
        std::ifstream inputMap(TEST_CASE_DIRECTORY + "\\test_map.txt");
        std::shared_ptr<GameConfig> game_config(
            new GameConfig(TEST_CASE_DIRECTORY + "\\test_game_config.json"));
        DungeonMap sc(inputMap, kn, game_config);
        
        Assert::AreEqual(sc.Get_game_config().get() == game_config.get(),true);
      }
	  TEST_METHOD(Get_Knight_test){
        Point pos = {3, 3};
        char texture = 'K';
        std::shared_ptr<Knight> kn(new Knight(pos, texture));
        kn->Set_cur_vec_move({1, 0});
        std::ifstream inputMap(TEST_CASE_DIRECTORY + "\\test_map.txt");
        std::shared_ptr<GameConfig> game_config(
            new GameConfig(TEST_CASE_DIRECTORY + "\\test_game_config.json"));
        DungeonMap sc(inputMap, kn, game_config);
        sc.SpawnKnight();
		Assert::AreEqual(kn.get() == sc.Get_Knight().get(),true);
      }
};
}