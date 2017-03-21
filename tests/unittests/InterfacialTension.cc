
#include <cassert>
#include <tclap/CmdLine.h>
#include <units/pvt-units.H>
#include <units/unittest-utils.H>

using namespace TCLAP;

CmdLine cmd = { "InterfacialTension", ' ', "0" };

SwitchArg passed = { "p", "passed", "Only print passed tests", cmd };

int
main(int argc, char* argv[])
{
  UnitTester tester;

  cmd.parse(argc, argv);
  tester.define_test("InterfacialTension.csv",
                     2,
                     "dynes_cm",
                     "N_m",
                     515.058706,
                     0.515058706,
                     1.0e-06);
  tester.define_test("InterfacialTension.csv",
                     3,
                     "dynes_cm",
                     "mN_m",
                     515.058706,
                     515.058706,
                     1.0e-06);
  tester.define_test("InterfacialTension.csv",
                     4,
                     "dynes_cm",
                     "gram_force_cm",
                     515.058706,
                     0.5252137132,
                     1.0e-06);
  tester.define_test("InterfacialTension.csv",
                     5,
                     "dynes_cm",
                     "pound_force_inch",
                     515.058706,
                     0.002941061,
                     1.0e-06);
  tester.define_test("InterfacialTension.csv",
                     6,
                     "N_m",
                     "dynes_cm",
                     172.849161,
                     172849.161,
                     1.0e-06);
  tester.define_test("InterfacialTension.csv",
                     7,
                     "N_m",
                     "mN_m",
                     172.849161,
                     172849.161,
                     1.0e-06);
  tester.define_test("InterfacialTension.csv",
                     8,
                     "N_m",
                     "gram_force_cm",
                     172.849161,
                     176.2570919,
                     1.0e-06);
  tester.define_test("InterfacialTension.csv",
                     9,
                     "N_m",
                     "pound_force_inch",
                     172.849161,
                     0.9869941351,
                     1.0e-06);
  tester.define_test("InterfacialTension.csv",
                     10,
                     "mN_m",
                     "dynes_cm",
                     529.844042,
                     529.844042,
                     1.0e-06);
  tester.define_test("InterfacialTension.csv",
                     11,
                     "mN_m",
                     "N_m",
                     529.844042,
                     0.529844042,
                     1.0e-06);
  tester.define_test("InterfacialTension.csv",
                     12,
                     "mN_m",
                     "gram_force_cm",
                     529.844042,
                     0.54029056,
                     1.0e-06);
  tester.define_test("InterfacialTension.csv",
                     13,
                     "mN_m",
                     "pound_force_inch",
                     529.844042,
                     0.0030254874,
                     1.0e-06);
  tester.define_test("InterfacialTension.csv",
                     14,
                     "gram_force_cm",
                     "dynes_cm",
                     811.372823,
                     795684.9295,
                     1.0e-06);
  tester.define_test("InterfacialTension.csv",
                     15,
                     "gram_force_cm",
                     "N_m",
                     811.372823,
                     795.6849295,
                     1.0e-06);
  tester.define_test("InterfacialTension.csv",
                     16,
                     "gram_force_cm",
                     "mN_m",
                     811.372823,
                     795684.9295,
                     1.0e-06);
  tester.define_test("InterfacialTension.csv",
                     17,
                     "gram_force_cm",
                     "pound_force_inch",
                     811.372823,
                     4.543477991,
                     1.0e-06);
  tester.define_test("InterfacialTension.csv",
                     18,
                     "pound_force_inch",
                     "dynes_cm",
                     0.381486,
                     66808.43654,
                     1.0e-06);
  tester.define_test("InterfacialTension.csv",
                     19,
                     "pound_force_inch",
                     "N_m",
                     0.381486,
                     66.80843654,
                     1.0e-06);
  tester.define_test("InterfacialTension.csv",
                     20,
                     "pound_force_inch",
                     "mN_m",
                     0.381486,
                     66808.43654,
                     1.0e-06);
  tester.define_test("InterfacialTension.csv",
                     21,
                     "pound_force_inch",
                     "gram_force_cm",
                     0.381486,
                     68.1256459,
                     1.0e-06);
  tester.perform();
  if (passed.getValue()) {
    tester.report_passed();
  }

  tester.report_failed();
  return tester.all_passed() ? 0 : -1;
}
