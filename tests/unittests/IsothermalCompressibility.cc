
#include <cassert>
#include <tclap/CmdLine.h>
#include <units/pvt-units.H>
#include <units/unittest-utils.H>

using namespace TCLAP;

CmdLine cmd = { "IsothermalCompressibility", ' ', "0" };

SwitchArg passed = { "p", "passed", "Only print passed tests", cmd };

int
main(int argc, char* argv[])
{
  UnitTester tester;

  cmd.parse(argc, argv);
  tester.define_test("IsothermalCompressibility.csv",
                     2,
                     "Pascal_1",
                     "mPa_1",
                     7.47e-07,
                     0.747,
                     1.0e-06);
  tester.define_test("IsothermalCompressibility.csv",
                     3,
                     "Pascal_1",
                     "psia_1",
                     7.47e-07,
                     0.005150383698,
                     1.0e-06);
  tester.define_test("IsothermalCompressibility.csv",
                     4,
                     "Pascal_1",
                     "Bar_1",
                     7.47e-07,
                     0.0747,
                     1.0e-06);
  tester.define_test("IsothermalCompressibility.csv",
                     5,
                     "Pascal_1",
                     "Atmosphere_1",
                     7.47e-07,
                     0.075689775,
                     1.0e-06);
  tester.define_test("IsothermalCompressibility.csv",
                     6,
                     "mPa_1",
                     "Pascal_1",
                     0.2506976477,
                     2.507e-07,
                     1.0e-05);
  tester.define_test("IsothermalCompressibility.csv",
                     7,
                     "mPa_1",
                     "psia_1",
                     0.2506976477,
                     0.001728499435,
                     1.0e-06);
  tester.define_test("IsothermalCompressibility.csv",
                     8,
                     "mPa_1",
                     "Bar_1",
                     0.2506976477,
                     0.02506976477,
                     1.0e-06);
  tester.define_test("IsothermalCompressibility.csv",
                     9,
                     "mPa_1",
                     "Atmosphere_1",
                     0.2506976477,
                     0.02540193915,
                     1.0e-06);
  tester.define_test("IsothermalCompressibility.csv",
                     10,
                     "psia_1",
                     "Pascal_1",
                     0.0052984451,
                     7.6847e-07,
                     1.0e-05);
  tester.define_test("IsothermalCompressibility.csv",
                     11,
                     "psia_1",
                     "mPa_1",
                     0.0052984451,
                     0.76847,
                     1.0e-05);
  tester.define_test("IsothermalCompressibility.csv",
                     12,
                     "psia_1",
                     "Bar_1",
                     0.0052984451,
                     0.07684744908,
                     1.0e-06);
  tester.define_test("IsothermalCompressibility.csv",
                     13,
                     "psia_1",
                     "Atmosphere_1",
                     0.0052984451,
                     0.07786567778,
                     1.0e-06);
  tester.define_test("IsothermalCompressibility.csv",
                     14,
                     "Bar_1",
                     "Pascal_1",
                     0.1176796754,
                     1.1768e-06,
                     1.0e-05);
  tester.define_test("IsothermalCompressibility.csv",
                     15,
                     "Bar_1",
                     "mPa_1",
                     0.1176796754,
                     1.176796754,
                     1.0e-06);
  tester.define_test("IsothermalCompressibility.csv",
                     16,
                     "Bar_1",
                     "psia_1",
                     0.1176796754,
                     0.008113728002,
                     1.0e-06);
  tester.define_test("IsothermalCompressibility.csv",
                     17,
                     "Bar_1",
                     "Atmosphere_1",
                     0.1176796754,
                     0.1192389311,
                     1.0e-06);
  tester.define_test("IsothermalCompressibility.csv",
                     18,
                     "Atmosphere_1",
                     "Pascal_1",
                     0.0098182789,
                     9.6899e-08,
                     1.0e-05);
  tester.define_test("IsothermalCompressibility.csv",
                     19,
                     "Atmosphere_1",
                     "mPa_1",
                     0.0098182789,
                     0.096899,
                     1.0e-05);
  tester.define_test("IsothermalCompressibility.csv",
                     20,
                     "Atmosphere_1",
                     "psia_1",
                     0.0098182789,
                     0.0006680942517,
                     1.0e-06);
  tester.define_test("IsothermalCompressibility.csv",
                     21,
                     "Atmosphere_1",
                     "Bar_1",
                     0.0098182789,
                     0.009689887886,
                     1.0e-06);
  tester.perform();
  if (passed.getValue()) {
    tester.report_passed();
  }

  tester.report_failed();
  return tester.all_passed() ? 0 : -1;
}
