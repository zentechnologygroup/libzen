
#include <cassert>
#include <tclap/CmdLine.h>
#include <units/pvt-units.H>
#include <units/unittest-utils.H>

using namespace TCLAP;

CmdLine cmd = { "WaterSpecificGravity", ' ', "0" };

SwitchArg passed = { "p", "passed", "Only print passed tests", cmd };

int
main(int argc, char* argv[])
{
  UnitTester tester;

  cmd.parse(argc, argv);
  tester.define_test("WaterSpecificGravity.csv", 2, "Pwl_lb_ft3",
                     "Dissolved_Salt_Percent", 69.885605402, 16.18397076,
                     1.0e-06);
  tester.define_test("WaterSpecificGravity.csv", 3, "Pwl_lb_ft3", "Sgw_sg",
                     69.885605402, 1.120565203, 1.0e-06);
  tester.define_test("WaterSpecificGravity.csv", 4, "Pwl_lb_ft3",
                     "Dissolved_Salt_PPM", 69.885605402, 161839.7076, 1.0e-06);
  tester.define_test("WaterSpecificGravity.csv", 5, "Pwl_lb_ft3",
                     "Molality_NaCl", 69.885605402, 3.303900714, 1.0e-06);
  tester.define_test("WaterSpecificGravity.csv", 6, "Pwl_lb_ft3", "CgL",
                     69.885605402, 161.8397076, 0.001);
  tester.define_test("WaterSpecificGravity.csv", 7, "Pwl_lb_ft3",
                     "Dissolved_Salt_Fraction", 69.885605402, 0.1618397076,
                     1.0e-06);
  tester.define_test("WaterSpecificGravity.csv", 8, "Dissolved_Salt_Percent",
                     "Pwl_lb_ft3", 5.1854748395, 64.68540736, 1.0e-06);
  tester.define_test("WaterSpecificGravity.csv", 9, "Dissolved_Salt_Percent",
                     "Sgw_sg", 5.1854748395, 1.037183784, 1.0e-06);
  tester.define_test("WaterSpecificGravity.csv", 10, "Dissolved_Salt_Percent",
                     "Dissolved_Salt_PPM", 5.1854748395, 51854.7484, 1.0e-06);
  tester.define_test("WaterSpecificGravity.csv", 11, "Dissolved_Salt_Percent",
                     "Molality_NaCl", 5.1854748395, 0.9357991408, 1.0e-06);
  tester.define_test("WaterSpecificGravity.csv", 12, "Dissolved_Salt_Percent",
                     "CgL", 5.1854748395, 51.8547484, 0.001);
  tester.define_test("WaterSpecificGravity.csv", 13, "Dissolved_Salt_Percent",
                     "Dissolved_Salt_Fraction", 5.1854748395, 0.0518547484,
                     1.0e-06);
  tester.define_test("WaterSpecificGravity.csv", 14, "Sgw_sg", "Pwl_lb_ft3",
                     1.1240398485, 70.10230647, 1.0e-06);
  tester.define_test("WaterSpecificGravity.csv", 15, "Sgw_sg",
                     "Dissolved_Salt_Percent", 1.1240398485, 16.62520753,
                     1.0e-06);
  tester.define_test("WaterSpecificGravity.csv", 16, "Sgw_sg",
                     "Dissolved_Salt_PPM", 1.1240398485, 166252.0753, 1.0e-06);
  tester.define_test("WaterSpecificGravity.csv", 17, "Sgw_sg", "Molality_NaCl",
                     1.1240398485, 3.411939286, 1.0e-06);
  tester.define_test("WaterSpecificGravity.csv", 18, "Sgw_sg", "CgL",
                     1.1240398485, 166.2520753, 0.001);
  tester.define_test("WaterSpecificGravity.csv", 19, "Sgw_sg",
                     "Dissolved_Salt_Fraction", 1.1240398485, 0.1662520753,
                     1.0e-06);
  tester.define_test("WaterSpecificGravity.csv", 20, "Dissolved_Salt_PPM",
                     "Pwl_lb_ft3", 811.372822616, 62.40359759, 1.0e-06);
  tester.define_test("WaterSpecificGravity.csv", 21, "Dissolved_Salt_PPM",
                     "Dissolved_Salt_Percent", 811.372822616, 0.08113728226,
                     1.0e-06);
  tester.define_test("WaterSpecificGravity.csv", 22, "Dissolved_Salt_PPM",
                     "Sgw_sg", 811.372822616, 1.000029478, 0.001);
  tester.define_test("WaterSpecificGravity.csv", 23, "Dissolved_Salt_PPM",
                     "Molality_NaCl", 811.372822616, 0.01389446917, 1.0e-06);
  tester.define_test("WaterSpecificGravity.csv", 24, "Dissolved_Salt_PPM",
                     "CgL", 811.372822616, 0.8113728226, 0.001);
  tester.define_test("WaterSpecificGravity.csv", 25, "Dissolved_Salt_PPM",
                     "Dissolved_Salt_Fraction", 811.372822616, 0.0008113728226,
                     1.0e-06);
  tester.define_test("WaterSpecificGravity.csv", 26, "Molality_NaCl",
                     "Pwl_lb_ft3", 0.4899184919, 63.60126383, 1.0e-06);
  tester.define_test("WaterSpecificGravity.csv", 27, "Molality_NaCl",
                     "Dissolved_Salt_Percent", 0.4899184919, 2.783522449,
                     1.0e-06);
  tester.define_test("WaterSpecificGravity.csv", 28, "Molality_NaCl", "Sgw_sg",
                     0.4899184919, 1.019800325, 1.0e-06);
  tester.define_test("WaterSpecificGravity.csv", 29, "Molality_NaCl",
                     "Dissolved_Salt_PPM", 0.4899184919, 27835.22449, 1.0e-06);
  tester.define_test("WaterSpecificGravity.csv", 30, "Molality_NaCl", "CgL",
                     0.4899184919, 27.83522449, 0.001);
  tester.define_test("WaterSpecificGravity.csv", 31, "Molality_NaCl",
                     "Dissolved_Salt_Fraction", 0.4899184919, 0.02783522449,
                     1.0e-06);
  tester.define_test("WaterSpecificGravity.csv", 32, "CgL", "Pwl_lb_ft3",
                     169.2246779, 70.24864892, 0.0001);
  tester.define_test("WaterSpecificGravity.csv", 33, "CgL",
                     "Dissolved_Salt_Percent", 169.2246779, 16.92246779, 0.001);
  tester.define_test("WaterSpecificGravity.csv", 34, "CgL", "Sgw_sg",
                     169.2246779, 1.126386344, 0.0001);
  tester.define_test("WaterSpecificGravity.csv", 35, "CgL",
                     "Dissolved_Salt_PPM", 169.2246779, 169224.6779, 0.001);
  tester.define_test("WaterSpecificGravity.csv", 36, "CgL", "Molality_NaCl",
                     169.2246779, 3.485371647, 0.001);
  tester.define_test("WaterSpecificGravity.csv", 37, "CgL",
                     "Dissolved_Salt_Fraction", 169.2246779, 0.1692246779,
                     0.001);
  tester.define_test("WaterSpecificGravity.csv", 38, "Dissolved_Salt_Fraction",
                     "Pwl_lb_ft3", 0.2542720699, 74.55539628, 1.0e-06);
  tester.define_test("WaterSpecificGravity.csv", 39, "Dissolved_Salt_Fraction",
                     "Dissolved_Salt_Percent", 0.2542720699, 25.42720699,
                     1.0e-06);
  tester.define_test("WaterSpecificGravity.csv", 40, "Dissolved_Salt_Fraction",
                     "Sgw_sg", 0.2542720699, 1.195441927, 1.0e-06);
  tester.define_test("WaterSpecificGravity.csv", 41, "Dissolved_Salt_Fraction",
                     "Dissolved_Salt_PPM", 0.2542720699, 254272.07, 1.0e-06);
  tester.define_test("WaterSpecificGravity.csv", 42, "Dissolved_Salt_Fraction",
                     "Molality_NaCl", 0.2542720699, 5.834279547, 1.0e-06);
  tester.define_test("WaterSpecificGravity.csv", 43, "Dissolved_Salt_Fraction",
                     "CgL", 0.2542720699, 254.2720699, 0.001);
  tester.perform();
  if (passed.getValue()) {
    tester.report_passed();
  }

  tester.report_failed();
  return tester.all_passed() ? 0 : -1;
}
