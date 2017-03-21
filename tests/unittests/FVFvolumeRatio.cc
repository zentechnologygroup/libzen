
#include <cassert>
#include <tclap/CmdLine.h>
#include <units/pvt-units.H>
#include <units/unittest-utils.H>

using namespace TCLAP;

CmdLine cmd = { "FVFvolumeRatio", ' ', "0" };

SwitchArg passed = { "p", "passed", "Only print passed tests", cmd };

int
main(int argc, char* argv[])
{
  UnitTester tester;

  cmd.parse(argc, argv);
  tester.define_test(
    "FVFvolumeRatio.csv", 2, "RB_STB", "Rm3_Sm3", 5.393058, 5.393058, 1.0e-06);
  tester.define_test(
    "FVFvolumeRatio.csv", 3, "Rm3_Sm3", "RB_STB", 2.142067, 2.142067, 1.0e-06);
  tester.perform();
  if (passed.getValue()) {
    tester.report_passed();
  }

  tester.report_failed();
  return tester.all_passed() ? 0 : -1;
}
