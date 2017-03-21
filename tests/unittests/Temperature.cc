
#include <cassert>
#include <tclap/CmdLine.h>
#include <units/pvt-units.H>
#include <units/unittest-utils.H>

using namespace TCLAP;

CmdLine cmd = { "Temperature", ' ', "0" };

SwitchArg passed = { "p", "passed", "Only print passed tests", cmd };

int
main(int argc, char* argv[])
{
  UnitTester tester;

  cmd.parse(argc, argv);
  tester.define_test("Temperature.csv", 2, "Kelvin", "Celsius", 346.139469,
                     72.989469, 1.0e-06);
  tester.define_test("Temperature.csv", 3, "Kelvin", "Fahrenheit", 346.139469,
                     163.3810442, 1.0e-06);
  tester.define_test("Temperature.csv", 4, "Kelvin", "Rankine", 346.139469,
                     623.0510442, 1.0e-06);
  tester.define_test("Temperature.csv", 5, "Celsius", "Kelvin", -156.988642,
                     116.161358, 1.0e-06);
  tester.define_test("Temperature.csv", 6, "Celsius", "Fahrenheit", -156.988642,
                     -250.5795556, 1.0e-06);
  tester.define_test("Temperature.csv", 7, "Celsius", "Rankine", -156.988642,
                     209.0904444, 1.0e-06);
  tester.define_test("Temperature.csv", 8, "Fahrenheit", "Kelvin", 70.174042,
                     294.3578011, 1.0e-06);
  tester.define_test("Temperature.csv", 9, "Fahrenheit", "Celsius", 70.174042,
                     21.20780111, 1.0e-06);
  tester.define_test("Temperature.csv", 10, "Fahrenheit", "Rankine", 70.174042,
                     529.844042, 1.0e-06);
  tester.define_test("Temperature.csv", 11, "Rankine", "Kelvin", 811.372823,
                     450.7626794, 1.0e-06);
  tester.define_test("Temperature.csv", 12, "Rankine", "Celsius", 811.372823,
                     177.6126794, 1.0e-06);
  tester.define_test("Temperature.csv", 13, "Rankine", "Fahrenheit", 811.372823,
                     351.702823, 1.0e-06);
  tester.perform();
  if (passed.getValue()) {
    tester.report_passed();
  }

  tester.report_failed();
  return tester.all_passed() ? 0 : -1;
}
