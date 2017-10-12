
# include <gmock/gmock.h>

# include <iostream>

# include <line.H>

using namespace std;
using namespace testing;
using namespace Aleph;

TEST(LineEq, basic)
{
  LineEq l1;
  LineEq l2 = l1;
  LineEq l3 = { 1, 1 };

  EXPECT_EQ(l1, l2);
  EXPECT_NE(l1, l3);

  EXPECT_THROW(LineEq(1, 2, 1, 3), OutOfRange);
  EXPECT_THROW(LineEq(2, 1, 3, 1), OutOfRange);
}

TEST(LineEq, simple_line)
{
  LineEq l;

  EXPECT_EQ(l(-1), -1);
  EXPECT_EQ(l(-10), -10);
  EXPECT_EQ(l(-100), -100);
  EXPECT_EQ(l(-1000), -1000);
  EXPECT_EQ(l(1), 1);
  EXPECT_EQ(l(10), 10);
  EXPECT_EQ(l(100), 100);
  EXPECT_EQ(l(1000), 1000);
}

TEST(LineEq, with_y0)
{
  LineEq l = { 1, 1 };

  EXPECT_EQ(l(0), 1);
  EXPECT_EQ(l(1), 2);
  EXPECT_EQ(l(2), 3);
  EXPECT_EQ(l(3), 4);
}

TEST(LineEq, with_2m)
{
  LineEq l = { 1, 2 };

  EXPECT_EQ(l(1), 3);
  EXPECT_EQ(l(2), 5);
}

TEST(LineEq, Equality)
{
  LineEq l1 = { -1, 2 };
  LineEq l2 = { 1, l1(1), 2, l1(2) };
  LineEq l3 = { 1, l2(1), l2.m };

  EXPECT_EQ(l1, l2);
  EXPECT_EQ(l2, l2);
  EXPECT_EQ(l2, l3);
}

TEST(LineEq, intersection)
{
  LineEq l1 = { 1, 2 };
  LineEq l2 = { -1, -2 };
  LineEq l3 = { -3, 0.5 };
  LineEq l4 = { 2, 10 };

  auto p12 = l1.intersection(l2);
  auto p13 = l1.intersection(l3);
  auto p14 = l1.intersection(l4);
  auto p23 = l2.intersection(l3);
  auto p24 = l2.intersection(l4);
  auto p34 = l3.intersection(l4);

  EXPECT_NEAR(p12.first, -0.5, 1e-15);
  EXPECT_NEAR(p12.second, 0, 1e-15);

  EXPECT_NEAR(p13.first, -2.6666667, 1e-7);
  EXPECT_NEAR(p13.second, -4.3333333, 1e-7);

  EXPECT_NEAR(p14.first, -0.125, 1e-15);
  EXPECT_NEAR(p14.second, 0.75, 1e-15);

  EXPECT_NEAR(p23.first, 0.8, 1e-15);
  EXPECT_NEAR(p23.second, -2.6, 1e-15);

  EXPECT_NEAR(p24.first, -0.25, 1e-15);
  EXPECT_NEAR(p24.second, -0.5, 1e-15);

  EXPECT_NEAR(p34.first, -0.526316, 1e-6);
  EXPECT_NEAR(p34.second, -3.26316, 1e-5);

}
