
#include <cassert>
#include <tclap/CmdLine.h>
#include <units/pvt-units.H>
#include <units/unittest-utils.H>

using namespace TCLAP;

CmdLine cmd = { "GasSpecificGravity", ' ', "0" };

SwitchArg passed = { "p", "passed", "Only print passed tests", cmd };

int
main(int argc, char* argv[])
{
  UnitTester tester;

  cmd.parse(argc, argv);
  tester.define_test("GasSpecificGravity.csv",
                     2,
                     "Sgg",
                     "rhog_kg_m3_atStandCond",
                     2.817764,
                     3.4517609,
                     1.0e-06);
  tester.define_test("GasSpecificGravity.csv",
                     3,
                     "Sgg",
                     "rhog_lb_ft3_atStandCond",
                     2.817764,
                     0.215486394,
                     1.0e-05);
  tester.define_test("GasSpecificGravity.csv",
                     4,
                     "rhog_kg_m3_atStandCond",
                     "Sgg",
                     1.565331,
                     1.277821224,
                     1.0e-06);
  tester.define_test("GasSpecificGravity.csv",
                     5,
                     "rhog_kg_m3_atStandCond",
                     "rhog_lb_ft3_atStandCond",
                     1.565331,
                     0.09772042196,
                     1.0e-05);
  tester.define_test("GasSpecificGravity.csv",
                     6,
                     "rhog_lb_ft3_atStandCond",
                     "Sgg",
                     0.220574,
                     2.884291042,
                     1.0e-05);
  tester.define_test("GasSpecificGravity.csv",
                     7,
                     "rhog_lb_ft3_atStandCond",
                     "rhog_kg_m3_atStandCond",
                     0.220574,
                     3.53325654,
                     1.0e-05);
  tester.perform();
  if (passed.getValue()) {
    tester.report_passed();
  }

  tester.report_failed();
  return tester.all_passed() ? 0 : -1;
}
