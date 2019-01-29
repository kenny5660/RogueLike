#include "CppUnitTest.h"
#include "stdafx.h"

#include "../RogueLike/CommonGameTypes.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RogueLikeTest {
TEST_CLASS(PointUnitTest){public :

      TEST_METHOD(Constructor_test){Point pt;
		Assert::AreEqual(pt.X, 0.0);
		Assert::AreEqual(pt.Y, 0.0);
		}  
	  TEST_METHOD(Constructor_with_XY_test) {
        double x = 4;
        double y = 5;
		Point pt (x,y);
		Assert::AreEqual(pt.X, x,0.1);
		Assert::AreEqual(pt.Y, y,0.1);
		}
	  TEST_METHOD(Constructor_copy_test) {
        double x = 4;
        double y = 5;
		Point pt (x,y);
        Point pt2 (pt);
		Assert::AreEqual(pt.X, pt2.X,0.1);
		Assert::AreEqual(pt.Y, pt2.Y,0.1);
		}
	  TEST_METHOD(Geter_int_test) {
        double x = 4;
        double y = 5;
		Point pt (x,y);
        
		Assert::AreEqual(pt.get_int_X(), (int)x);
		Assert::AreEqual(pt.get_int_Y(), (int)y);
		}
	  TEST_METHOD(operator_equal_test) {
        double x = 4;
        double y = 5;
		Point pt (x,y);
        Point pt2 (pt);
		Assert::AreEqual(pt == pt2, true);
		}
};
TEST_CLASS(LimitedValueUnitTest){
  public :

      TEST_METHOD(Constructor_test){
		VectorMath pt;
		Assert::AreEqual(pt.X, 0.0);
		Assert::AreEqual(pt.Y, 0.0);
		}  
	  TEST_METHOD(Constructor_with_XY_test) {
        double x = 4;
        double y = 5;
        VectorMath pt(x, y);
		Assert::AreEqual(pt.X, x,0.1);
		Assert::AreEqual(pt.Y, y,0.1);
		}
	  TEST_METHOD(Constructor_copy_test) {
        double x = 4;
        double y = 5;
        VectorMath pt(x, y);
        VectorMath pt2(pt);
		Assert::AreEqual(pt.X, pt2.X,0.1);
		Assert::AreEqual(pt.Y, pt2.Y,0.1);
		}
	  TEST_METHOD(Geter_int_test) {
        double x = 4;
        double y = 5;
        VectorMath pt(x, y);
        
		Assert::AreEqual(pt.get_int_X(), (int)x);
		Assert::AreEqual(pt.get_int_Y(), (int)y);
		}
	  TEST_METHOD(operator_equal_test) {
        double x = 4;
        double y = 5;
        VectorMath pt(x, y);
        VectorMath pt2(pt);
		Assert::AreEqual(pt == pt2, true);
		}
};
TEST_CLASS(VectorMathUnitTest){public :

      TEST_METHOD(Constructor_test){
		LimitedValue lv(5,10,1);
		Assert::AreEqual(lv.get_value(), 5);
		Assert::AreEqual(lv.get_max(), 10);
		Assert::AreEqual(lv.get_min(), 1);
		LimitedValue lv2(15,10,1);
		Assert::AreEqual(lv2.get_value(), lv2.get_max());
		Assert::AreEqual(lv2.get_max(), 10);
		Assert::AreEqual(lv2.get_min(), 1);
		}  
	  TEST_METHOD(Constructor_copy_test) {
        double x = 4;
        double y = 5;
        LimitedValue lv(5, 10, 1);
        LimitedValue lv2(lv);
        Assert::AreEqual(lv.get_value(), lv2.get_value());
        Assert::AreEqual(lv.get_max(), lv2.get_max());
        Assert::AreEqual(lv.get_min(), lv2.get_min());
		}
	  TEST_METHOD(Seter_test) {
        int val = 6;
        int min = 5;
        int max = 10;
        LimitedValue lv;
        lv.set_max(max);
        lv.set_min(min);
        lv.set_value(val);
        
		Assert::AreEqual(lv.get_value(), val);
        Assert::AreEqual(lv.get_max(), max);
        Assert::AreEqual(lv.get_min(), min);
		}
	  TEST_METHOD(Seter_val_below_min_test) {
        int val = 3;
        int min = 5;
        int max = 10;
        LimitedValue lv;
        lv.set_max(max);
        lv.set_min(min);
        lv.set_value(val);
        
		Assert::AreEqual(lv.get_value(), min);
        Assert::AreEqual(lv.get_max(), max);
        Assert::AreEqual(lv.get_min(), min);
	  }
	  TEST_METHOD(Seter_val_above_max_test) {
        int val = 30;
        int min = 5;
        int max = 10;
        LimitedValue lv;
        lv.set_max(max);
        lv.set_min(min);
        lv.set_value(val);
		Assert::AreEqual(lv.get_value(), max);
        Assert::AreEqual(lv.get_max(), max);
        Assert::AreEqual(lv.get_min(), min);
	  }
};
}  // namespace RogueLikeTest