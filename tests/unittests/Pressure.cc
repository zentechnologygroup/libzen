
#include <cassert>
#include <tclap/CmdLine.h>
#include <units/pvt-units.H>
#include <units/unittest-utils.H>

using namespace TCLAP;

CmdLine cmd = { "Pressure", ' ', "0" };

SwitchArg passed = { "p", "passed", "Only print passed tests", cmd };

int
main(int argc, char* argv[])
{
  UnitTester tester;

  cmd.parse(argc, argv);
  tester.define_test("Pressure.csv", 2, "Bar", "Pascal", 515.058706, 51505870.6,
                     1.0e-06);
  tester.define_test("Pressure.csv", 3, "Bar", "kPascal", 515.058706,
                     51505.8706, 1.0e-06);
  tester.define_test("Pressure.csv", 4, "Bar", "mPascal", 515.058706,
                     51.5058706, 1.0e-06);
  tester.define_test("Pressure.csv", 5, "Bar", "psia", 515.058706, 7470.294952,
                     1.0e-06);
  tester.define_test("Pressure.csv", 6, "Bar", "psig", 515.058706, 7455.599002,
                     1.0e-06);
  tester.define_test("Pressure.csv", 7, "Bar", "Atmosphere", 515.058706,
                     508.3234207, 1.0e-06);
  tester.define_test("Pressure.csv", 8, "Pascal", "Bar", 172.849161,
                     0.00172849161, 1.0e-06);
  tester.define_test("Pressure.csv", 9, "Pascal", "kPascal", 172.849161,
                     0.172849161, 1.0e-06);
  tester.define_test("Pressure.csv", 10, "Pascal", "mPascal", 172.849161,
                     0.000172849161, 1.0e-06);
  tester.define_test("Pressure.csv", 11, "Pascal", "psia", 172.849161,
                     0.02506965128, 1.0e-06);
  tester.define_test("Pressure.csv", 12, "Pascal", "psig", 172.849161,
                     -14.67087975, 1.0e-06);
  tester.define_test("Pressure.csv", 13, "Pascal", "Atmosphere", 172.849161,
                     0.001705888586, 1.0e-06);
  tester.define_test("Pressure.csv", 14, "kPascal", "Bar", 529.844042,
                     5.29844042, 1.0e-06);
  tester.define_test("Pressure.csv", 15, "kPascal", "Pascal", 529.844042,
                     529844.042, 1.0e-06);
  tester.define_test("Pressure.csv", 16, "kPascal", "mPascal", 529.844042,
                     0.529844042, 1.0e-06);
  tester.define_test("Pressure.csv", 17, "kPascal", "psia", 529.844042,
                     76.8473812, 1.0e-06);
  tester.define_test("Pressure.csv", 18, "kPascal", "psig", 529.844042,
                     62.1514318, 1.0e-06);
  tester.define_test("Pressure.csv", 19, "kPascal", "Atmosphere", 529.844042,
                     5.229154128, 1.0e-06);
  tester.define_test("Pressure.csv", 20, "mPascal", "Bar", 167.827121,
                     1678.27121, 1.0e-06);
  tester.define_test("Pressure.csv", 21, "mPascal", "Pascal", 167.827121,
                     167827121.0, 1.0e-06);
  tester.define_test("Pressure.csv", 22, "mPascal", "kPascal", 167.827121,
                     167827.121, 1.0e-06);
  tester.define_test("Pressure.csv", 23, "mPascal", "psia", 167.827121,
                     24341.26596, 1.0e-06);
  tester.define_test("Pressure.csv", 24, "mPascal", "psig", 167.827121,
                     24326.57001, 1.0e-06);
  tester.define_test("Pressure.csv", 25, "mPascal", "Atmosphere", 167.827121,
                     1656.324905, 1.0e-06);
  tester.define_test("Pressure.csv", 26, "psia", "Bar", 66.808486, 4.606282961,
                     1.0e-06);
  tester.define_test("Pressure.csv", 27, "psia", "Pascal", 66.808486,
                     460628.2961, 1.0e-06);
  tester.define_test("Pressure.csv", 28, "psia", "kPascal", 66.808486,
                     460.6282961, 1.0e-06);
  tester.define_test("Pressure.csv", 29, "psia", "mPascal", 66.808486,
                     0.4606282961, 1.0e-06);
  tester.define_test("Pressure.csv", 30, "psia", "psig", 66.808486, 52.1125366,
                     1.0e-06);
  tester.define_test("Pressure.csv", 31, "psia", "Atmosphere", 66.808486,
                     4.546047827, 1.0e-06);
  tester.define_test("Pressure.csv", 32, "psig", "Bar", 548.952952, 38.86222374,
                     1.0e-06);
  tester.define_test("Pressure.csv", 33, "psig", "Pascal", 548.952952,
                     3886222.374, 1.0e-06);
  tester.define_test("Pressure.csv", 34, "psig", "kPascal", 548.952952,
                     3886.222374, 1.0e-06);
  tester.define_test("Pressure.csv", 35, "psig", "mPascal", 548.952952,
                     3.886222374, 1.0e-06);
  tester.define_test("Pressure.csv", 36, "psig", "psia", 548.952952,
                     563.6489014, 1.0e-06);
  tester.define_test("Pressure.csv", 37, "psig", "Atmosphere", 548.952952,
                     38.3540328, 1.0e-06);
  tester.define_test("Pressure.csv", 38, "Atmosphere", "Bar", 847.573566,
                     858.8039157, 1.0e-06);
  tester.define_test("Pressure.csv", 39, "Atmosphere", "Pascal", 847.573566,
                     85880391.57, 1.0e-06);
  tester.define_test("Pressure.csv", 40, "Atmosphere", "kPascal", 847.573566,
                     85880.39157, 1.0e-06);
  tester.define_test("Pressure.csv", 41, "Atmosphere", "mPascal", 847.573566,
                     85.88039157, 1.0e-06);
  tester.define_test("Pressure.csv", 42, "Atmosphere", "psia", 847.573566,
                     12455.89771, 1.0e-06);
  tester.define_test("Pressure.csv", 43, "Atmosphere", "psig", 847.573566,
                     12441.20176, 1.0e-06);
  tester.perform();
  if (passed.getValue()) {
    tester.report_passed();
  }

  tester.report_failed();
  return tester.all_passed() ? 0 : -1;
}
