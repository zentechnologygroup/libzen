
#include <cassert>
#include <tclap/CmdLine.h>
#include <units/pvt-units.H>
#include <units/unittest-utils.H>

using namespace TCLAP;

CmdLine cmd = { "OilGravity", ' ', "0" };

SwitchArg passed = { "p", "passed", "Only print passed tests", cmd };

int
main(int argc, char* argv[])
{
  UnitTester tester;

  cmd.parse(argc, argv);
  tester.define_test("OilGravity.csv", 2, "Api", "Sg_do", 58.596223,
                     0.7443598708, 1.0e-06);
  tester.define_test("OilGravity.csv", 3, "Sg_do", "Api", 0.665147, 81.23492927,
                     1.0e-06);
  tester.perform();
  if (passed.getValue()) {
    tester.report_passed();
  }

  tester.report_failed();
  return tester.all_passed() ? 0 : -1;
}
