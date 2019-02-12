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
		  std::shared_ptr<Scene> sc = std::make_shared<Scene>();
		Point pos = {3,3};
		char texture = 'F';
        std::shared_ptr<GameObject> kn = std::make_shared<GameObject>(pos, texture);
        sc->AddObject(kn);
        Assert::AreEqual(sc->Get_game_objects().DataById(kn->Get_id()).second, true);
		Assert::AreEqual(sc->Get_game_objects().DataById(kn->Get_id()).first->Get_texture(), texture);
      }
	  TEST_METHOD(DelObject_test){
		  std::shared_ptr<Scene> sc = std::make_shared<Scene>();
		Point pos = {3,3};
		char texture = 'K';
        std::shared_ptr<GameObject> kn = std::make_shared<GameObject>(pos, texture);
        sc->AddObject(kn);
        sc->DelObject(kn->Get_id());
        Assert::AreEqual(sc->Get_game_objects().DataById(kn->Get_id()).second, false);
      }
	  TEST_METHOD(Update_test){
		  std::shared_ptr<Scene> sc = std::make_shared<Scene>();
        sc->Set_elapsed_time(1);
		Point pos = {3,3};
		char texture = 'K';
        std::shared_ptr<GameObject> kn = std::make_shared<GameObject>(pos, texture);
        sc->AddObject(kn);
		sc->Update();
        Assert::AreEqual(sc->Get_game_objects().DataById(kn->Get_id()).first->Get_pos().X, pos.X);
      }
	  TEST_METHOD(Draw_test){
        Init—urses();
		  std::shared_ptr<Scene> sc = std::make_shared<Scene>();
        sc->Set_elapsed_time(1);
		Point pos = {3,3};
		char texture = 'K';
        std::shared_ptr<GameObject> kn = std::make_shared<GameObject>(pos, texture);
        sc->AddObject(kn);
		sc->Draw();
        char real_text = mvinch(kn->Get_pos().get_int_Y(), kn->Get_pos().get_int_X());
        Assert::AreEqual(real_text,
            kn->Get_texture());
		endwin();
      }
	  TEST_METHOD(Get_and_set_is_game_over_test) {
		  std::shared_ptr<Scene> sc = std::make_shared<Scene>();
            sc->Set_game_result(GameResult::WIN); 
		Assert::AreEqual(sc->Get_game_result() == GameResult::WIN, true);
      }
	  TEST_METHOD(Get_and_set_elapsed_time) {
		  std::shared_ptr<Scene> sc = std::make_shared<Scene>();
        sc->Set_elapsed_time(0.8); 
		Assert::AreEqual(sc->Get_elapsed_time(), 0.8,0.1);
      }


};
TEST_CLASS(DungeonMapTest){
  public :
	  TEST_METHOD(Constructor_test){
		Point pos = {3,3};
		char texture = 'K';
        std::shared_ptr<Knight> kn(new Knight());
		kn->Set_cur_vec_move({1,0});
        std::ifstream inputMap(TEST_CASE_DIRECTORY +"\\test_map.txt");
                std::shared_ptr<GameConfig> game_config(new GameConfig(
                    TEST_CASE_DIRECTORY +"\\test_game_config.json"));
        std::shared_ptr<DungeonMap> sc =
                    DungeonMap::create(inputMap, kn, game_config);
        sc->Set_elapsed_time(1);

        kn->Set_parent_scene(sc);
        Assert::AreEqual(sc->Get_width(), 30);
        Assert::AreEqual(sc->Get_height(), 12);
        Assert::AreEqual(sc->Get_game_objects().Total(),47);
      }
	  TEST_METHOD(Spawn_test){
        Point pos = {3, 3};
        char texture = 'K';
   

        std::ifstream inputMap(TEST_CASE_DIRECTORY + "\\test_map.txt");
        std::shared_ptr<GameConfig> game_config(
            new GameConfig(TEST_CASE_DIRECTORY + "\\test_game_config.json"));
        std::shared_ptr<Knight> kn =
            std::make_shared<Knight>(game_config->Get_knight(), Point{-1, -1},
                                     nullptr, game_config->Get_control_keys());
        kn->Set_cur_vec_move({1, 0});
        std::shared_ptr<DungeonMap> sc =
            DungeonMap::create(inputMap, kn, game_config);
        sc->Set_elapsed_time(1);
        std::shared_ptr<Scene> sc_share(sc);
        kn->Set_parent_scene(sc_share);
        sc->Set_pos_spawn_knight({3,5});
        sc->SpawnKnight();
        Assert::AreEqual(sc->Get_pos_sawn_knight().get_int_X(), kn->Get_pos().get_int_X());
		Assert::AreEqual(sc->Get_pos_sawn_knight().get_int_Y(), kn->Get_pos().get_int_Y());
        Assert::AreEqual(sc->Get_game_objects().Total(), 48);
      }
	  TEST_METHOD(Get_game_config_test){
        Point pos = {3, 3};
        char texture = 'K';

        std::ifstream inputMap(TEST_CASE_DIRECTORY + "\\test_map.txt");
        std::shared_ptr<GameConfig> game_config(
            new GameConfig(TEST_CASE_DIRECTORY + "\\test_game_config.json"));
        std::shared_ptr<Knight> kn =
            std::make_shared<Knight>(game_config->Get_knight(), Point{-1, -1},
                                     nullptr, game_config->Get_control_keys());
        kn->Set_cur_vec_move({1, 0});

        std::shared_ptr<DungeonMap> sc =
            DungeonMap::create(inputMap, kn, game_config);
        
        Assert::AreEqual(sc->Get_game_config().get() == game_config.get(),true);
      }
	  TEST_METHOD(Get_Knight_test){
        Point pos = {3, 3};
        char texture = 'K';

        std::ifstream inputMap(TEST_CASE_DIRECTORY + "\\test_map.txt");
        std::shared_ptr<GameConfig> game_config(
            new GameConfig(TEST_CASE_DIRECTORY + "\\test_game_config.json"));
        std::shared_ptr<Knight> kn =
            std::make_shared<Knight>(game_config->Get_knight(), Point{-1, -1},
                                     nullptr, game_config->Get_control_keys());
        kn->Set_cur_vec_move({1, 0});
        std::shared_ptr<DungeonMap> sc =
            DungeonMap::create(inputMap, kn, game_config);
        sc->SpawnKnight();
		Assert::AreEqual(kn.get() == sc->Get_Knight().get(),true);
        sc.~shared_ptr();
      }
};
}