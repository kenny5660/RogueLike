#include "CppUnitTest.h"
#include "stdafx.h"

#include "../RogueLike/Scene.h"

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

};
}