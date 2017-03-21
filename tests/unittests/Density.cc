
#include <cassert>
#include <tclap/CmdLine.h>
#include <units/pvt-units.H>
#include <units/unittest-utils.H>

using namespace TCLAP;

CmdLine cmd = { "Density", ' ', "0" };

SwitchArg passed = { "p", "passed", "Only print passed tests", cmd };

int
main(int argc, char* argv[])
{
  UnitTester tester;

  cmd.parse(argc, argv);
  tester.define_test(
    "Density.csv", 2, "Gr_cm3", "Kg_m3", 1.699742, 1699.742, 1.0e-06);
  tester.define_test(
    "Density.csv", 3, "Gr_cm3", "Kg_L", 1.699742, 1.699742, 1.0e-06);
  tester.define_test(
    "Density.csv", 4, "Gr_cm3", "Lb_ft3", 1.699742, 106.1114266, 1.0e-06);
  tester.define_test(
    "Density.csv", 5, "Gr_cm3", "Lb_Gal", 1.699742, 14.18503445, 1.0e-05);
  tester.define_test(
    "Density.csv", 6, "Gr_cm3", "Lb_Inch3", 1.699742, 0.0614070756, 1.0e-05);
  tester.define_test(
    "Density.csv", 7, "Gr_cm3", "Sg", 1.699742, 1.701416194, 1.0e-06);
  tester.define_test(
    "Density.csv", 8, "Kg_m3", "Gr_cm3", 172.949161, 0.172949161, 1.0e-06);
  tester.define_test(
    "Density.csv", 9, "Kg_m3", "Kg_L", 172.949161, 0.172949161, 1.0e-06);
  tester.define_test(
    "Density.csv", 10, "Kg_m3", "Lb_ft3", 172.949161, 10.79686341, 1.0e-06);
  tester.define_test(
    "Density.csv", 11, "Kg_m3", "Lb_Gal", 172.949161, 1.443330698, 1.0e-05);
  tester.define_test(
    "Density.csv", 12, "Kg_m3", "Lb_Inch3", 172.949161, 0.0062481848, 1.0e-06);
  tester.define_test(
    "Density.csv", 13, "Kg_m3", "Sg", 172.949161, 0.1731195106, 1.0e-06);
  tester.define_test(
    "Density.csv", 14, "Kg_L", "Gr_cm3", 1.748532, 1.748532, 1.0e-06);
  tester.define_test(
    "Density.csv", 15, "Kg_L", "Kg_m3", 1.748532, 1748.532, 1.0e-06);
  tester.define_test(
    "Density.csv", 16, "Kg_L", "Lb_ft3", 1.748532, 109.1572868, 1.0e-06);
  tester.define_test(
    "Density.csv", 17, "Kg_L", "Lb_Gal", 1.748532, 14.59220674, 1.0e-05);
  tester.define_test(
    "Density.csv", 18, "Kg_L", "Lb_Inch3", 1.748532, 0.0631697261, 1.0e-05);
  tester.define_test(
    "Density.csv", 19, "Kg_L", "Sg", 1.748532, 1.75025425, 1.0e-06);
  tester.define_test(
    "Density.csv", 20, "Lb_ft3", "Gr_cm3", 167.153553, 2.677543067, 1.0e-06);
  tester.define_test(
    "Density.csv", 21, "Lb_ft3", "Kg_m3", 167.153553, 2677.543067, 1.0e-06);
  tester.define_test(
    "Density.csv", 22, "Lb_ft3", "Kg_L", 167.153553, 2.677543067, 1.0e-06);
  tester.define_test(
    "Density.csv", 23, "Lb_ft3", "Lb_Gal", 167.153553, 22.34517983, 1.0e-06);
  tester.define_test(
    "Density.csv", 24, "Lb_ft3", "Lb_Inch3", 167.153553, 0.0967323802, 1.0e-06);
  tester.define_test(
    "Density.csv", 25, "Lb_ft3", "Sg", 167.153553, 2.680180364, 1.0e-05);
  tester.define_test(
    "Density.csv", 26, "Lb_Gal", "Gr_cm3", 1.840668, 0.2205606703, 1.0e-05);
  tester.define_test(
    "Density.csv", 27, "Lb_Gal", "Kg_m3", 1.840668, 220.5606703, 1.0e-05);
  tester.define_test(
    "Density.csv", 28, "Lb_Gal", "Kg_L", 1.840668, 0.2205606703, 1.0e-05);
  tester.define_test(
    "Density.csv", 29, "Lb_Gal", "Lb_ft3", 1.840668, 13.76915283, 1.0e-06);
  tester.define_test(
    "Density.csv", 30, "Lb_Gal", "Lb_Inch3", 1.840668, 0.0079682597, 1.0e-06);
  tester.define_test(
    "Density.csv", 31, "Lb_Gal", "Sg", 1.840668, 0.2207779158, 1.0e-05);
  tester.define_test(
    "Density.csv", 32, "Lb_Inch3", "Gr_cm3", 0.0672, 1.860089597, 1.0e-05);
  tester.define_test(
    "Density.csv", 33, "Lb_Inch3", "Kg_m3", 0.0672, 1860.089597, 1.0e-06);
  tester.define_test(
    "Density.csv", 34, "Lb_Inch3", "Kg_L", 0.0672, 1.860089597, 1.0e-05);
  tester.define_test(
    "Density.csv", 35, "Lb_Inch3", "Lb_ft3", 0.0672, 116.1216, 1.0e-06);
  tester.define_test(
    "Density.csv", 36, "Lb_Inch3", "Lb_Gal", 0.0672, 15.5232, 1.0e-06);
  tester.define_test(
    "Density.csv", 37, "Lb_Inch3", "Sg", 0.0672, 1.861921728, 1.0e-05);
  tester.define_test(
    "Density.csv", 38, "Sg", "Gr_cm3", 2.799763, 2.797008033, 1.0e-06);
  tester.define_test(
    "Density.csv", 39, "Sg", "Kg_m3", 2.799763, 2797.008033, 1.0e-06);
  tester.define_test(
    "Density.csv", 40, "Sg", "Kg_L", 2.799763, 2.797008033, 1.0e-06);
  tester.define_test(
    "Density.csv", 41, "Sg", "Lb_ft3", 2.799763, 174.6115072, 1.0e-05);
  tester.define_test(
    "Density.csv", 42, "Sg", "Lb_Gal", 2.799763, 23.34216329, 1.0e-05);
  tester.define_test(
    "Density.csv", 43, "Sg", "Lb_Inch3", 2.799763, 0.1010483259, 0.0001);
  tester.perform();
  if (passed.getValue()) {
    tester.report_passed();
  }

  tester.report_failed();
  return tester.all_passed() ? 0 : -1;
}
