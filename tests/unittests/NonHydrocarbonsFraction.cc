
#include <cassert>
#include <tclap/CmdLine.h>
#include <units/pvt-units.H>
#include <units/unittest-utils.H>

using namespace TCLAP;

CmdLine cmd = { "NonHydrocarbonsFraction", ' ', "0" };

SwitchArg passed = { "p", "passed", "Only print passed tests", cmd };

int
main(int argc, char* argv[])
{
  UnitTester tester;

  cmd.parse(argc, argv);
  tester.define_test("NonHydrocarbonsFraction.csv",
                     2,
                     "MoleFraction",
                     "VolumeFraction",
                     0.515059,
                     0.515059,
                     1.0e-06);
  tester.define_test("NonHydrocarbonsFraction.csv",
                     3,
                     "MoleFraction",
                     "MolePercent",
                     0.515059,
                     51.5059,
                     1.0e-06);
  tester.define_test("NonHydrocarbonsFraction.csv",
                     4,
                     "MoleFraction",
                     "VolumePercent",
                     0.515059,
                     51.5059,
                     1.0e-06);
  tester.define_test("NonHydrocarbonsFraction.csv",
                     5,
                     "VolumeFraction",
                     "MoleFraction",
                     0.172849,
                     0.172849,
                     1.0e-06);
  tester.define_test("NonHydrocarbonsFraction.csv",
                     6,
                     "VolumeFraction",
                     "MolePercent",
                     0.172849,
                     17.2849,
                     1.0e-06);
  tester.define_test("NonHydrocarbonsFraction.csv",
                     7,
                     "VolumeFraction",
                     "VolumePercent",
                     0.172849,
                     17.2849,
                     1.0e-06);
  tester.define_test("NonHydrocarbonsFraction.csv",
                     8,
                     "MolePercent",
                     "MoleFraction",
                     52.984404,
                     0.52984404,
                     1.0e-06);
  tester.define_test("NonHydrocarbonsFraction.csv",
                     9,
                     "MolePercent",
                     "VolumeFraction",
                     52.984404,
                     0.52984404,
                     1.0e-06);
  tester.define_test("NonHydrocarbonsFraction.csv",
                     10,
                     "MolePercent",
                     "VolumePercent",
                     52.984404,
                     52.984404,
                     1.0e-06);
  tester.define_test("NonHydrocarbonsFraction.csv",
                     11,
                     "VolumePercent",
                     "MoleFraction",
                     81.137282,
                     0.81137282,
                     1.0e-06);
  tester.define_test("NonHydrocarbonsFraction.csv",
                     12,
                     "VolumePercent",
                     "VolumeFraction",
                     81.137282,
                     0.81137282,
                     1.0e-06);
  tester.define_test("NonHydrocarbonsFraction.csv",
                     13,
                     "VolumePercent",
                     "MolePercent",
                     81.137282,
                     81.137282,
                     1.0e-06);
  tester.perform();
  if (passed.getValue()) {
    tester.report_passed();
  }

  tester.report_failed();
  return tester.all_passed() ? 0 : -1;
}
