#include "CppUnitTest.h"
#include "stdafx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RogueLikeTest {
TEST_CLASS(WallTest){
  public :

      TEST_METHOD(Constructor_test){
		  Point pos(10, 12);
		  Wall wl(pos,'D');

		  Assert::AreEqual(wl.Get_pos().get_int_X(), pos.get_int_X());
		  Assert::AreEqual(wl.Get_pos().get_int_Y(), pos.get_int_Y());
		  Assert::AreEqual(wl.Get_texture(), 'D');
      }
	  TEST_METHOD(Constructor_copy_test){
		  Point pos(10, 12);
		  Point pos2(15, 11);
		  Wall wl(pos,'D');
          Wall wl2(wl, pos2);
		  Assert::AreEqual(wl2.Get_pos().get_int_X(), pos2.get_int_X());
          Assert::AreEqual(wl2.Get_pos().get_int_Y(), pos2.get_int_Y());
          Assert::AreEqual(wl.Get_texture(), wl2.Get_texture());
      }
};
TEST_CLASS(EntityTest){
  public :

      TEST_METHOD(Collide_aid_kit_test){
		  Zombie ideal_zm;
		  ideal_zm.get_hp().set_max(7);
		  ideal_zm.get_hp().set_min(0);
          ideal_zm.get_hp().set_value(3);
           
		  AidKit ideal_kit;
          ideal_kit.Set_texture('+');
          ideal_kit.Set_hp_regen(5);
  
          Scene sc;
          std::shared_ptr<Zombie> zm(new Zombie(ideal_zm, {0, 0}, &sc));
          std::shared_ptr<AidKit> kit(new AidKit(ideal_kit, {0, 0}));
          sc.AddObject(zm);
          sc.AddObject(kit);
          kit->Collide(*zm);
		  Assert::AreEqual(zm->get_hp().get_value(),ideal_zm.get_hp().get_max());
		  Assert::AreEqual(sc.Get_gameObjects().Total(), 1);
      }
	  TEST_METHOD(Dead_test){
		  Zombie ideal_zm;
		  ideal_zm.get_hp().set_max(7);
		  ideal_zm.get_hp().set_min(0);
          ideal_zm.get_hp().set_value(3);
  
          Scene sc;
          std::shared_ptr<Zombie> zm(new Zombie(ideal_zm, {0, 0}, &sc));
          sc.AddObject(zm);
          zm->dead();
		  Assert::AreEqual(sc.Get_gameObjects().Total(), 0);
      }
};

TEST_CLASS(KnightTest){
  public :

      TEST_METHOD(Constructor_copy_test){
		  Knight ideal_kn;
		  ideal_kn.get_hp().set_max(7);
		  ideal_kn.get_hp().set_min(0);
          ideal_kn.get_hp().set_value(7);
		  ideal_kn.get_mp().set_max(10);
          ideal_kn.get_mp().set_min(0);
          ideal_kn.get_mp().set_value(10);
          ideal_kn.Set_damage(2);
          ideal_kn.Set_texture('K');
          ideal_kn.Set_speed(1);
          ideal_kn.Set_damage_projectile(3);
          ideal_kn.Set_speed_projectile(6);
          Point pos(2, 5);
          Knight kn(ideal_kn,pos,nullptr);
          Assert::AreEqual(kn.get_hp().get_max(),ideal_kn.get_hp().get_max());
          Assert::AreEqual(kn.get_hp().get_min(), ideal_kn.get_hp().get_min());
          Assert::AreEqual(kn.get_hp().get_value(), ideal_kn.get_hp().get_value());
          Assert::AreEqual(kn.get_mp().get_max(), ideal_kn.get_mp().get_max());
          Assert::AreEqual(kn.get_mp().get_min(), ideal_kn.get_mp().get_min());
          Assert::AreEqual(kn.get_mp().get_value(),ideal_kn.get_mp().get_value());
          Assert::AreEqual(kn.Get_texture(), ideal_kn.Get_texture());
          Assert::AreEqual(kn.Get_damage(), ideal_kn.Get_damage());
          Assert::AreEqual(kn.Get_speed(), ideal_kn.Get_speed());
          Assert::AreEqual(kn.Get_damage_projectile(), ideal_kn.Get_damage_projectile());
		  Assert::AreEqual(kn.Get_speed_projectile(), ideal_kn.Get_speed_projectile());
      }
	  TEST_METHOD(Colide_monster_test){
		  Zombie ideal_zm;
		  ideal_zm.get_hp().set_max(7);
		  ideal_zm.get_hp().set_min(0);
          ideal_zm.get_hp().set_value(1);
          ideal_zm.Set_damage(2);
          Knight ideal_kn;
		  ideal_kn.get_hp().set_max(7);
		  ideal_kn.get_hp().set_min(0);
          ideal_kn.get_hp().set_value(3);
          ideal_kn.Set_damage(2);
          ideal_kn.Set_texture('K');

          Scene sc;
          std::shared_ptr<Zombie> zm(new Zombie(ideal_zm, {0, 0}, &sc));
          std::shared_ptr<Zombie> zm2(new Zombie(ideal_zm, {0, 0}, &sc));
          std::shared_ptr<Knight> kn(new Knight(ideal_kn, {0, 0}, &sc));
          sc.AddObject(zm);
          sc.AddObject(kn);
          sc.AddObject(zm2);
          kn->Collide(*zm);
		  Assert::AreEqual(kn->get_hp().get_value(),1);
		  Assert::AreEqual(sc.Get_gameObjects().DataById(zm->Get_id()).second, false);
          Assert::AreEqual(kn->Get_points(), 1);
		  kn->Collide(*zm2);
	      Assert::AreEqual(kn->get_hp().get_value(), 0);
		  Assert::AreEqual(sc.Get_gameObjects().DataById(zm2->Get_id()).second, false);
		  Assert::AreEqual(sc.Get_game_result() ==  GAME_RESULT_LOSE,true);
      }
	  TEST_METHOD(Key_pressed_test){
		  Knight ideal_kn;
          ideal_kn.key_pressed(KEY_UP);
          VectorMath vec(0,-1);
          Assert::AreEqual(ideal_kn.Get_cur_vector_move().get_int_X(),vec.get_int_X());
	      Assert::AreEqual(ideal_kn.Get_cur_vector_move().get_int_Y(),vec.get_int_Y());
		  ideal_kn.key_pressed(KEY_DOWN);
          vec = {0,1};
          Assert::AreEqual(ideal_kn.Get_cur_vector_move().get_int_X(),vec.get_int_X());
	      Assert::AreEqual(ideal_kn.Get_cur_vector_move().get_int_Y(),vec.get_int_Y());
		  ideal_kn.key_pressed(KEY_RIGHT);
          vec = {1,0};
          Assert::AreEqual(ideal_kn.Get_cur_vector_move().get_int_X(),vec.get_int_X());
	      Assert::AreEqual(ideal_kn.Get_cur_vector_move().get_int_Y(),vec.get_int_Y());
		  ideal_kn.key_pressed(KEY_LEFT);
          vec = {-1,0};
          Assert::AreEqual(ideal_kn.Get_cur_vector_move().get_int_X(),vec.get_int_X());
	      Assert::AreEqual(ideal_kn.Get_cur_vector_move().get_int_Y(),vec.get_int_Y());
	   }

	};
        TEST_CLASS(ZombietTest) {
         public:
          TEST_METHOD(Constructor_test) {
			Point pos(5,7);
			char texture = 'Z';
            Zombie zm(pos,texture);
            Assert::AreEqual(zm.Get_pos().get_int_Y(),pos.get_int_Y());
            Assert::AreEqual(zm.Get_pos().get_int_X(), pos.get_int_X());
			Assert::AreEqual(zm.Get_texture(),texture);
          }
		  TEST_METHOD(Colide_knight_test){
		  Zombie ideal_zm;
		  ideal_zm.get_hp().set_max(7);
		  ideal_zm.get_hp().set_min(0);
          ideal_zm.get_hp().set_value(1);
          ideal_zm.Set_damage(2);
          Knight ideal_kn;
		  ideal_kn.get_hp().set_max(7);
		  ideal_kn.get_hp().set_min(0);
          ideal_kn.get_hp().set_value(3);
          ideal_kn.Set_damage(2);
          ideal_kn.Set_texture('K');

          Scene sc;
          std::shared_ptr<Zombie> zm(new Zombie(ideal_zm, {0, 0}, &sc));
          std::shared_ptr<Zombie> zm2(new Zombie(ideal_zm, {0, 0}, &sc));
          std::shared_ptr<Knight> kn(new Knight(ideal_kn, {0, 0}, &sc));
          sc.AddObject(zm);
          sc.AddObject(kn);
          sc.AddObject(zm2);
          zm->Collide(*kn);
		  Assert::AreEqual(kn->get_hp().get_value(),1);
		  Assert::AreEqual(sc.Get_gameObjects().DataById(zm->Get_id()).second, false);
          Assert::AreEqual(kn->Get_points(), 1);
		  zm2->Collide(*kn);
	      Assert::AreEqual(kn->get_hp().get_value(), 0);
		  Assert::AreEqual(sc.Get_gameObjects().DataById(zm2->Get_id()).second, false);
		  Assert::AreEqual(sc.Get_game_result() == GAME_RESULT_LOSE,true);
      }
	TEST_METHOD(Colide_wall_test){
		  Zombie ideal_zm;
		  ideal_zm.get_hp().set_max(7);
		  ideal_zm.get_hp().set_min(0);
          ideal_zm.get_hp().set_value(1);
          ideal_zm.Set_damage(2);
          Scene sc;
          Point zm_pos(1, 3);
          std::shared_ptr<Zombie> zm(new Zombie(ideal_zm, zm_pos, &sc));
          std::shared_ptr<Wall> wall(new Wall({2, 2}));
          zm->Collide(*wall);
          Assert::AreEqual(zm->Get_pos().get_int_X(), zm_pos.get_int_X());
          Assert::AreEqual(zm->Get_pos().get_int_Y(), zm_pos.get_int_Y());
      }
	TEST_METHOD(Colide_monster_test){
		  Zombie ideal_zm;
		  ideal_zm.get_hp().set_max(7);
		  ideal_zm.get_hp().set_min(0);
          ideal_zm.get_hp().set_value(1);
          ideal_zm.Set_damage(2);
          Scene sc;
          Point zm_pos(1, 3);
          std::shared_ptr<Zombie> zm(new Zombie(ideal_zm, zm_pos, &sc));
          std::shared_ptr<GameObject> zm2(new Zombie(ideal_zm, zm_pos, &sc));
          zm->Collide(*zm2);
          Assert::AreEqual(zm->Get_pos().get_int_X(), zm_pos.get_int_X());
          Assert::AreEqual(zm->Get_pos().get_int_Y(), zm_pos.get_int_Y());
      }
  };
   TEST_CLASS(AidKitTest) {
         public:
          TEST_METHOD(Constructor_test) {
			Point pos(5,7);
			char texture = 'Z';
            AidKit zm(pos,5);
            Assert::AreEqual(zm.Get_pos().get_int_Y(),pos.get_int_Y());
            Assert::AreEqual(zm.Get_pos().get_int_X(), pos.get_int_X());
			Assert::AreEqual(zm.Get_hp_regen(),5);
          }
  };
  TEST_CLASS(GuiPlayerTest) {public : TEST_METHOD(Draw_test){
	      Init_curses();
		  Point pos(1,2);
		  Knight ideal_kn;
		  ideal_kn.get_hp().set_max(7);
		  ideal_kn.get_hp().set_min(0);
          ideal_kn.get_hp().set_value(7);
		  ideal_kn.get_mp().set_max(10);
          ideal_kn.get_mp().set_min(0);
          ideal_kn.get_mp().set_value(10);
          ideal_kn.Set_damage(2);
          ideal_kn.Set_texture('K');
          ideal_kn.Set_speed(1);
          ideal_kn.Set_damage_projectile(3);
          ideal_kn.Set_speed_projectile(6);
          std::shared_ptr<Knight> kn(new Knight(ideal_kn, {0, 0}, nullptr));
          GuiPlayer gui(pos, kn);
          gui.Draw();
          std::string str1;
          for (int i = 0; i < 7; ++i) {
            str1 += (char)mvinch(pos.get_int_Y(), pos.get_int_X()+i);
		  }
          Assert::AreEqual(str1, std::string("HP: 7/7"));
		  std::string str2;
          for (int i = 0; i < 9; ++i) {
            str2 += (char)mvinch(pos.get_int_Y()+1, pos.get_int_X()+i);
		  }
          Assert::AreEqual(str2, std::string("MP: 10/10"));
		  std::string str3;
          for (int i = 0; i < 10; ++i) {
            str3 += (char)mvinch(pos.get_int_Y()+2, pos.get_int_X()+i);
		  }
          Assert::AreEqual(str3, std::string("Points: 0 "));
         }
  };
  TEST_CLASS(projectileTest) {
         public:
          TEST_METHOD(Constructor_test) {
			Knight ideal_kn;
		  ideal_kn.get_hp().set_max(7);
		  ideal_kn.get_hp().set_min(0);
          ideal_kn.get_hp().set_value(7);
		  ideal_kn.get_mp().set_max(10);
          ideal_kn.get_mp().set_min(0);
          ideal_kn.get_mp().set_value(10);
          ideal_kn.Set_damage(2);
          ideal_kn.Set_texture('K');
          ideal_kn.Set_speed(1);
          ideal_kn.Set_damage_projectile(3);
          ideal_kn.Set_speed_projectile(6);
		  Scene sc;
          std::shared_ptr<Knight> kn(new Knight(ideal_kn, {0, 0}, &sc));
		  sc.AddObject(kn);
          kn->key_pressed(KEY_UP);
          kn->key_pressed(' ');
		  Assert::AreEqual(sc.Get_gameObjects().Total(),2);
          Assert::AreEqual(sc.Get_gameObjects().DataById(1).first->Get_texture(), '^');
          sc.DelObject(1);
		  kn->key_pressed(KEY_DOWN);
          kn->key_pressed(' ');
          Assert::AreEqual(sc.Get_gameObjects().DataById(2).first->Get_texture(), 'V');
		  kn->key_pressed(KEY_RIGHT);
          kn->key_pressed(' ');
          Assert::AreEqual(sc.Get_gameObjects().DataById(3).first->Get_texture(), '>');
		  kn->key_pressed(KEY_LEFT);
          kn->key_pressed(' ');
          Assert::AreEqual(sc.Get_gameObjects().DataById(4).first->Get_texture(), '<');
          }
          TEST_METHOD(Collide_wall_test){
            Scene sc;
            std::shared_ptr<Projectile> tle(new Projectile({0, 0},2,{0,1},6, &sc));
			std::shared_ptr<Wall> wl(new Wall({0, 0}));
            sc.AddObject(wl);
            sc.AddObject(tle);
            tle->Collide(*wl);
            Assert::AreEqual(sc.Get_gameObjects().Total(), 1);
		  }
          TEST_METHOD(Collide_tile_test) {
            Scene sc;
            std::shared_ptr<Projectile> tle(
                new Projectile({0, 0}, 2, {0, 1}, 6, &sc));
            std::shared_ptr<Projectile> tle2(
                new Projectile({0, 0}, 2, {0, 1}, 6, &sc));
            sc.AddObject(tle2);
            sc.AddObject(tle);
            tle->Collide(*tle2);
            Assert::AreEqual(sc.Get_gameObjects().Total(), 0);
          }
		   TEST_METHOD(Collide_monster_test){
            Scene sc;
            std::shared_ptr<Projectile> tle(new Projectile({0, 0},2,{0,1},6, &sc));
			 Zombie ideal_zm;
			 ideal_zm.get_hp().set_max(7);
			 ideal_zm.get_hp().set_min(0);
		     ideal_zm.get_hp().set_value(1);
		     ideal_zm.Set_damage(2);
          std::shared_ptr<Zombie> zm(new Zombie(ideal_zm, {0, 0}, &sc));
            sc.AddObject(zm);
            sc.AddObject(tle);
            tle->Collide(*zm);
            Assert::AreEqual(sc.Get_gameObjects().Total(), 0);
		  }
		   TEST_METHOD(Collide_projectTileknight_monster_test){
            Scene sc;
         
			 Zombie ideal_zm;
			 ideal_zm.get_hp().set_max(7);
			 ideal_zm.get_hp().set_min(0);
		     ideal_zm.get_hp().set_value(1);
		     ideal_zm.Set_damage(2);
			 Knight ideal_kn;
			 ideal_kn.get_hp().set_max(7);
			 ideal_kn.get_hp().set_min(0);
		     ideal_kn.get_hp().set_value(1);
		     ideal_kn.Set_damage(2);
            std::shared_ptr<Knight> kn(new Knight(ideal_kn, {0, 0}, &sc));
            std::shared_ptr<Zombie> zm(new Zombie(ideal_zm, {0, 0}, &sc));
		    std::shared_ptr<Projectile> tle(new ProjectileKnight({0, 0},2,{0,1},6, kn.get()));
            sc.AddObject(kn);
            sc.AddObject(zm);
            sc.AddObject(tle);
            tle->Collide(*zm);
            Assert::AreEqual(sc.Get_gameObjects().Total(), 1);
            Assert::AreEqual(kn->Get_points(), 1);
		  }
		   TEST_METHOD(Collide_knight_test){
            Scene sc;
            std::shared_ptr<Projectile> tle(new Projectile({0, 0},2,{0,1},6, &sc));
			 Knight ideal_zm;
			 ideal_zm.get_hp().set_max(7);
			 ideal_zm.get_hp().set_min(0);
		     ideal_zm.get_hp().set_value(1);
		     ideal_zm.Set_damage(2);
          std::shared_ptr<Knight> zm(new Knight(ideal_zm, {0, 0}, &sc));
            sc.AddObject(zm);
            sc.AddObject(tle);
            tle->Collide(*zm);
            Assert::AreEqual(sc.Get_gameObjects().Total(), 1);
            Assert::IsTrue(sc.Get_game_result()  == GAME_RESULT_LOSE);
		  }
  };
  TEST_CLASS(DragonTest) {
         public:
          TEST_METHOD(Constructor_test) {
			Point pos(5,7);
			char texture = 'D';
            Dragon zm(pos,texture);
            Assert::AreEqual(zm.Get_pos().get_int_Y(),pos.get_int_Y());
            Assert::AreEqual(zm.Get_pos().get_int_X(), pos.get_int_X());
			Assert::AreEqual(zm.Get_texture(),texture);
          }
		  TEST_METHOD(Create_projectile_test){
		  Dragon ideal_d;
		  ideal_d.get_hp().set_max(7);
		  ideal_d.get_hp().set_min(0);
          ideal_d.get_hp().set_value(1);
          ideal_d.Set_damage(2);
          ideal_d.Set_speed_projectile(7);
		  ideal_d.Set_damage_projectile(7);
          Scene sc;
          Point zm_pos(1, 3);
          std::shared_ptr<Dragon> d(new Dragon(ideal_d, zm_pos, &sc));
          sc.AddObject(d);
          d->Create_projectile({5,8},{0,1});
          Assert::AreEqual(sc.Get_gameObjects().Total(), 2);
		}
		  TEST_METHOD(Colide_knight_test){
		  Dragon ideal_d;
		  ideal_d.get_hp().set_max(7);
		  ideal_d.get_hp().set_min(0);
          ideal_d.get_hp().set_value(1);
          ideal_d.Set_damage(2);
          Knight ideal_kn;
		  ideal_kn.get_hp().set_max(7);
		  ideal_kn.get_hp().set_min(0);
          ideal_kn.get_hp().set_value(3);
          ideal_kn.Set_damage(2);
          ideal_kn.Set_texture('K');

          Scene sc;
          std::shared_ptr<Dragon> zm(new Dragon(ideal_d, {0, 0}, &sc));
          std::shared_ptr<Dragon> zm2(new Dragon(ideal_d, {0, 0}, &sc));
          std::shared_ptr<Knight> kn(new Knight(ideal_kn, {0, 0}, &sc));
          sc.AddObject(zm);
          sc.AddObject(kn);
          sc.AddObject(zm2);
          zm->Collide(*kn);
		  Assert::AreEqual(kn->get_hp().get_value(),1);
		  Assert::AreEqual(sc.Get_gameObjects().DataById(zm->Get_id()).second, false);
          Assert::AreEqual(kn->Get_points(), 1);
		  zm2->Collide(*kn);
	      Assert::AreEqual(kn->get_hp().get_value(), 0);
		  Assert::AreEqual(sc.Get_gameObjects().DataById(zm2->Get_id()).second, false);
		  Assert::AreEqual((int)sc.Get_game_result(), (int)GAME_RESULT_LOSE);
      }
	TEST_METHOD(Colide_wall_test){
		  Zombie ideal_zm;
		  ideal_zm.get_hp().set_max(7);
		  ideal_zm.get_hp().set_min(0);
          ideal_zm.get_hp().set_value(1);
          ideal_zm.Set_damage(2);
          Scene sc;
          Point zm_pos(1, 3);
          std::shared_ptr<Zombie> zm(new Zombie(ideal_zm, zm_pos, &sc));
          std::shared_ptr<Wall> wall(new Wall({2, 2}));
          zm->Collide(*wall);
          Assert::AreEqual(zm->Get_pos().get_int_X(), zm_pos.get_int_X());
          Assert::AreEqual(zm->Get_pos().get_int_Y(), zm_pos.get_int_Y());
      }
	TEST_METHOD(Colide_monster_test){
		  Dragon ideal_d;
		  ideal_d.get_hp().set_max(7);
		  ideal_d.get_hp().set_min(0);
          ideal_d.get_hp().set_value(1);
          ideal_d.Set_damage(2);
          Scene sc;
          Point zm_pos(1, 3);
          std::shared_ptr<Dragon> zm(new Dragon(ideal_d, zm_pos, &sc));
          std::shared_ptr<Dragon> zm2(new Dragon(ideal_d, zm_pos, &sc));
          zm->Collide(*zm2);
          Assert::AreEqual(zm->Get_pos().get_int_X(), zm_pos.get_int_X());
          Assert::AreEqual(zm->Get_pos().get_int_Y(), zm_pos.get_int_Y());
      }
  };
}