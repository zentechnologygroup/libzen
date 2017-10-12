
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

  ASSERT_EQ(l1, l2);
  ASSERT_NE(l1, l3);

  ASSERT_THROW(LineEq(1, 2, 3, 3), OutOfRange);
  ASSERT_THROW(LineEq(2, 1, 3, 4), OutOfRange);
}

TEST(LineEq, simple_line)
{
  LineEq l;

  ASSERT_EQ(l(-1), -1);
  ASSERT_EQ(l(-10), -10);
  ASSERT_EQ(l(-100), -100);
  ASSERT_EQ(l(-1000), -1000);
  ASSERT_EQ(l(1), 1);
  ASSERT_EQ(l(10), 10);
  ASSERT_EQ(l(100), 100);
  ASSERT_EQ(l(1000), 1000);
}

TEST(LineEq, with_y0)
{
  LineEq l = { 1, 1 };

  ASSERT_EQ(l(0), 1);
  ASSERT_EQ(l(1), 2);
  ASSERT_EQ(l(2), 3);
  ASSERT_EQ(l(3), 4);
}

TEST(LineEq, with_2m)
{
  LineEq l = { 1, 2 };

  ASSERT_EQ(l(1), 3);
  ASSERT_EQ(l(2), 5);
}

TEST(LineEq, intersection)
{
  LineEq l1 = { 1, 2 };
  LineEq l2 = { -1, -2 };

  auto p = l1.intersection(l2); 
  cout << p.first << " , " << p.second << endl;
}
