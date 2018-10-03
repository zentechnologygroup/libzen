#ifndef ZTG_TEST_GLOBAL_ENVIRONMENT_H
#define ZTG_TEST_GLOBAL_ENVIRONMENT_H

#include <string>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "unitslist.hpp"

struct TestArguments
{
  std::size_t nsamples;
  double max_range;
  double epsilon;
  std::vector<const PhysicalQuantity *> physical_quantities;
  std::size_t precision;
  std::string display_mode;
  bool verbose;
  unsigned long seed;
};

namespace testglobalenv
{

TestArguments args;

}

class TestGlobalEnvironment : public testing::Environment
{
public:

  explicit TestGlobalEnvironment(const TestArguments & arguments)
  {
    testglobalenv::args = arguments;
  }
};

#endif  // ZTG_TEST_GLOBAL_ENVIRONMENT_H