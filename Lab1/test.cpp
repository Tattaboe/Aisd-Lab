#include <gtest/gtest.h>
#include "vector.cpp"
#include <complex>

TEST(VectorTest, Exam) {
	Vector<double> a(1, 4);
	Vector<double> b(4, 2);
	Vector<double> dot = a * a * b;
	Vector<double> result(4, 32);
	EXPECT_EQ(dot,result);
}