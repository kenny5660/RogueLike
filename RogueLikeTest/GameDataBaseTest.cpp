#include "CppUnitTest.h"
#include "stdafx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RogueLikeTest {
TEST_CLASS(GameDatabaseTest){
  public :

      TEST_METHOD(Constructor_test){
		  GameDatabase game_database;
		  Assert::AreEqual(game_database.Total(), 0);
      }
	  TEST_METHOD(Insert_test){
		  GameDatabase game_database;
          Point pos = {0, 1};
          std::shared_ptr<GameObject> kn(new GameObject(pos,'K'));
          game_database.Insert(kn);
		  Assert::AreEqual(game_database.Total(), 1);
      }
	  TEST_METHOD(Remove_test){
		  GameDatabase game_database;
          Point pos = {0, 1};
          std::shared_ptr<GameObject> kn(new GameObject(pos,'K'));
          game_database.Insert(kn);
          game_database.Insert(std::shared_ptr<GameObject>(new Zombie()));
          game_database.Remove(kn->Get_id());
          Assert::AreEqual(game_database.Total(), 1);
          Assert::AreEqual(game_database.DataById(kn->Get_id()).second, false);
          Assert::AreEqual(game_database.DataById(kn->Get_id()).first.get() == (GameObject*)nullptr,true);
      }
	  TEST_METHOD(DataById_test){
		  GameDatabase game_database;
          Point pos = {0, 1};
          std::shared_ptr<GameObject> kn(new Knight());
          game_database.Insert(kn);
          game_database.Insert(std::shared_ptr<GameObject> (new Zombie()));
		  Assert::AreEqual(game_database.DataById(kn->Get_id()).second, true);
          Assert::AreEqual(game_database.DataById(kn->Get_id()).first->Get_id(), kn->Get_id());
      }
	  TEST_METHOD(Data_test){
		  GameDatabase game_database;
          Point pos = {0, 1};
          std::shared_ptr<GameObject> kn(new Knight());
          std::shared_ptr<GameObject> zm(new Zombie());
          game_database.Insert(kn);
          game_database.Insert(zm);
          std::vector<std::shared_ptr<GameObject>> data_vec = game_database.Data();
          Assert::AreEqual(data_vec.size(), (size_t)2);
          Assert::AreEqual(data_vec[0]->Get_id(), zm->Get_id());
          Assert::AreEqual(data_vec[1]->Get_id(), kn->Get_id());
      }
	  TEST_METHOD(Data_non_static_test){
		  GameDatabase game_database;
          Point pos = {0, 1};
          std::shared_ptr<GameObject> kn(new Knight());
          std::shared_ptr<GameObject> zm(new Zombie());
          game_database.Insert(kn);
          game_database.Insert(zm,true);
          std::vector<std::shared_ptr<GameObject>> data_vec = game_database.Data_non_static();
          Assert::AreEqual(data_vec.size(), (size_t)1);
          Assert::AreEqual(data_vec[0]->Get_id(), kn->Get_id());
      }
};
}