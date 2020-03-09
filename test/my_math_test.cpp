#include "pch.h"
#include "CppUnitTest.h"
#include "..\c_practice\my_math.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace mymathtest
{
	TEST_CLASS(mymathtest)
	{
	public:
		TEST_METHOD(TestMethod2)	//	两线相交一点
		{
			Point p;
			Point a1(5, 2);
			Point b1(0, -3);
			Point a2(-5, 3);
			Point b2(4, -1);

			Line l1(a1,b1);
			Line l2(a2,b2);
			p = l1.find_intersection(l2);

			Point i(2.6153846153846, -0.3846153846154);
			Assert::AreEqual(true, p == i);
		}
		TEST_METHOD(TestMethod3)	//	两线相交一点
		{
			Point p;
			Point a1(2, 2);
			Point b1(4, 4);
			Point a2(4, 2);
			Point b2(2, 6);

			Line l1(a1, b1);
			Line l2(a2, b2);
			p = l1.find_intersection(l2);

			Point i(3.3333333333333, 3.3333333333333);
			Assert::AreEqual(true, p == i);
		}

		TEST_METHOD(TestMethod4)	//	两线平行
		{
			Point p;
			Point a1(2, 2);
			Point b1(4, 8);
			Point a2(4, 2);
			Point b2(6, 8);

			Line l1(a1, b1);
			Line l2(a2, b2);
			p = l1.find_intersection(l2);
			Point i(INFINITY, INFINITY);

			Assert::AreEqual(true, p == i);
		}
		TEST_METHOD(TestMethod5)	//	两线平行
		{
			Point p;
			Point a1(-2, 0);
			Point b1(2, 6);
			Point a2(6, 2);
			Point b2(10, 8);

			Line l1(a1, b1);
			Line l2(a2, b2);
			p = l1.find_intersection(l2);

			Assert::AreEqual(true, p.get_x() == INFINITY && p.get_y() == INFINITY);
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////	圆线交点
		TEST_METHOD(TestMethod7)
		{
			Point p(0,0);
			double r = 1;
			Line l1(0, 1, -1);
			Circle o1(p, r);
			int n;
			Point p_list[2];
			n = o1.find_intersection(l1,p_list);
			Assert::AreEqual(1, n);
		}

		TEST_METHOD(TestMethod8)
		{
			Point p(0, 0);
			double r = 1;
			Line l1(-1, 1, -sqrt(2));
			Circle o1(p, r);
			int n;
			Point p_list[2];
			n = o1.find_intersection(l1, p_list);
			Assert::AreEqual(1, n);
		}
		TEST_METHOD(TestMethod9)
		{
			Line l1(-1, 1, -1);

			Point p(0, 0);
			double r = 1;
			Circle o1(p, r);

			int n;
			Point p_list[2];
			n = o1.find_intersection(l1, p_list);

			Point a(0,1);
			Point b(-1,0);
			Assert::AreEqual(true, p_list[0] == a || p_list[0] == b);
			Assert::AreEqual(true, p_list[1] == a || p_list[1] == b);
		}

		TEST_METHOD(TestMethod9_)
		{
			Line l1(2, 5, -6);

			Point p1(-1, 3);
			double r1 = sqrt(7);
			Circle o1(p1, r1);

			int n;
			Point p_list[2];
			n = o1.find_intersection(l1, p_list);

			Point a(-3.6223575251708, 2.6489430100683);
			Point b(0.6568402837915, 0.9372638864834);
			Assert::AreEqual(true, p_list[0] == a || p_list[0] == b);
			Assert::AreEqual(true, p_list[1] == a || p_list[1] == b);
		}

		//TEST_METHOD(TestMethod9__)
		//{
		//	Point p_1(-1, 4);
		//	Point p_2(4, -1);
		//	Line l1(p_1, p_2);

		//	Point p1(2, 2);
		//	double r1 = 1;
		//	Circle o1(p1, r1);

		//	int n;
		//	Point p_list[2];
		//	n = o1.find_intersection(l1, p_list);

		//	Point a(-3.6223575251708, 2.6489430100683);
		//	Point b(0.6568402837915, 0.9372638864834);
		//	Assert::AreEqual(true, p_list[0] == a || p_list[0] == b);
		//	Assert::AreEqual(true, p_list[1] == a || p_list[1] == b);
		//}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////	圆圆交点
		TEST_METHOD(TestMethod10)
		{
			Point p1(0, 0);
			double r1 = 1;
			Circle o1(p1, r1);

			Point p2(1, 0);
			double r2 = 1;
			Circle o2(p2, r2);

			int n;
			Point p_list[2];
			n = o1.find_intersection(o2, p_list);

			Point a(1.0/2.0, sqrt(3)/2.0);
			Point b(1.0/2.0, -sqrt(3)/2.0);
			Assert::AreEqual(true, p_list[0] == a || p_list[0] == b);
			Assert::AreEqual(true, p_list[1] == a || p_list[1] == b);
		}

		TEST_METHOD(TestMethod12)	
		{
			Point p1(-1, 3);
			double r1 = sqrt(7);
			Circle o1(p1, r1);

			Point p2(1, 2);
			double r2 = sqrt(7);
			Circle o2(p2, r2);

			int n;
			Point p_list[2];
			n = o1.find_intersection(o2, p_list);

			Point a(1.0723805294764, 4.6447610589527);
			Point b(-1.0723805294764, 0.3552389410473);
			Assert::AreEqual(true, p_list[0] == a || p_list[0] == b);
			Assert::AreEqual(true, p_list[1] == a || p_list[1] == b);
		}
		TEST_METHOD(TestMethod13)
		{
			Point p1(-1, 3);
			double r1 = sqrt(7);
			Circle o1(p1, r1);

			Point p2(2, 2);
			double r2 = sqrt(7);
			Circle o2(p2, r2);

			int n;
			Point p_list[2];
			n = o1.find_intersection(o2, p_list);

			Point a(1.1708203932499, 4.5124611797498);
			Point b(-0.1708203932499, 0.4875388202502);
			Assert::AreEqual(true, p_list[0] == a || p_list[0] == b);
			Assert::AreEqual(true, p_list[1] == a || p_list[1] == b);
		}
		TEST_METHOD(TestMethod14)
		{
			Point p1(-1, 3);
			double r1 = sqrt(7);
			Circle o1(p1, r1);

			Point p2(2*sqrt(7)-1, 3);
			double r2 = sqrt(7);
			Circle o2(p2, r2);

			int n;
			Point p_list[2];
			n = o1.find_intersection(o2, p_list);

			Point a(sqrt(7)-1, 3);
			Assert::AreEqual(1, n);
			Assert::AreEqual(true, p_list[0] == a);
		}
		TEST_METHOD(TestMethod15)
		{
			Point p1(-1, 3);
			double r1 = sqrt(7);
			Circle o1(p1, r1);

			Point p2(-1.0/2.0, 3);
			double r2 = sqrt(7)-1.0/2.0;
			Circle o2(p2, r2);

			int n;
			Point p_list[2];
			n = o1.find_intersection(o2, p_list);

			Point a(sqrt(7) - 1, 3);
			Assert::AreEqual(1, n);
			Assert::AreEqual(true, p_list[0] == a);
		}

		TEST_METHOD(TestMethod16)
		{
			Point p1(-1, 3);
			double r1 = sqrt(7);
			Circle o1(p1, r1);

			Point p2(-1.0 / 2.0, 3);
			double r2 = 10;
			Circle o2(p2, r2);

			int n;
			Point p_list[2];
			n = o1.find_intersection(o2, p_list);

			Assert::AreEqual(0, n);
		}
	};
}
