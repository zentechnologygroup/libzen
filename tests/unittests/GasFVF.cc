
#include <cassert>
#include <tclap/CmdLine.h>
#include <units/pvt-units.H>
#include <units/unittest-utils.H>

using namespace TCLAP;

CmdLine cmd = { "GasFVF", ' ', "0" };

SwitchArg passed = { "p", "passed", "Only print passed tests", cmd };

int
main(int argc, char* argv[])
{
  UnitTester tester;

  cmd.parse(argc, argv);
  tester.define_test(
    "GasFVF.csv", 2, "RCF_SCF", "RM3_SM3", 5.150587061, 5.1505870605, 1.0e-06);
  tester.define_test(
    "GasFVF.csv", 3, "RCF_SCF", "RCF_MSCF", 5.150587061, 5150.5870605, 1.0e-06);
  tester.define_test("GasFVF.csv",
                     4,
                     "RCF_SCF",
                     "RB_SCF",
                     5.150587061,
                     0.9173587343376624,
                     1.0e-06);
  tester.define_test("GasFVF.csv",
                     5,
                     "RCF_SCF",
                     "RB_MSCF",
                     5.150587061,
                     917.3587343376624,
                     1.0e-06);
  tester.define_test(
    "GasFVF.csv", 6, "RM3_SM3", "RCF_SCF", 1.7284916132, 1.7284916132, 1.0e-06);
  tester.define_test("GasFVF.csv",
                     7,
                     "RM3_SM3",
                     "RCF_MSCF",
                     1.7284916132,
                     1728.4916132000003,
                     1.0e-06);
  tester.define_test("GasFVF.csv",
                     8,
                     "RM3_SM3",
                     "RB_SCF",
                     1.7284916132,
                     0.3078575043918367,
                     1.0e-06);
  tester.define_test("GasFVF.csv",
                     9,
                     "RM3_SM3",
                     "RB_MSCF",
                     1.7284916132,
                     307.85750439183676,
                     1.0e-06);
  tester.define_test("GasFVF.csv",
                     10,
                     "RCF_MSCF",
                     "RCF_SCF",
                     529.844041681,
                     0.5298440416808998,
                     1.0e-06);
  tester.define_test("GasFVF.csv",
                     11,
                     "RCF_MSCF",
                     "RM3_SM3",
                     529.844041681,
                     0.5298440419999998,
                     1.0e-06);
  tester.define_test("GasFVF.csv",
                     12,
                     "RCF_MSCF",
                     "RB_SCF",
                     529.844041681,
                     0.09436925418,
                     1.0e-06);
  tester.define_test("GasFVF.csv",
                     13,
                     "RCF_MSCF",
                     "RB_MSCF",
                     529.844041681,
                     94.36925423376623,
                     1.0e-06);
  tester.define_test("GasFVF.csv",
                     14,
                     "RB_SCF",
                     "RCF_SCF",
                     1.4451172033,
                     8.113730964361459,
                     1.0e-06);
  tester.define_test("GasFVF.csv",
                     15,
                     "RB_SCF",
                     "RM3_SM3",
                     1.4451172033,
                     8.113730964361459,
                     1.0e-06);
  tester.define_test("GasFVF.csv",
                     16,
                     "RB_SCF",
                     "RCF_MSCF",
                     1.4451172033,
                     8113.73096436145,
                     1.0e-06);
  tester.define_test(
    "GasFVF.csv", 17, "RB_SCF", "RB_MSCF", 1.4451172033, 1445.1172033, 1.0e-06);
  tester.define_test("GasFVF.csv",
                     18,
                     "RB_MSCF",
                     "RCF_SCF",
                     66.8084863573,
                     0.37510181402692394,
                     1.0e-06);
  tester.define_test("GasFVF.csv",
                     19,
                     "RB_MSCF",
                     "RM3_SM3",
                     66.8084863573,
                     0.37510181402692394,
                     1.0e-06);
  tester.define_test("GasFVF.csv",
                     20,
                     "RB_MSCF",
                     "RCF_MSCF",
                     66.8084863573,
                     375.101814026924,
                     1.0e-06);
  tester.define_test("GasFVF.csv",
                     21,
                     "RB_MSCF",
                     "RB_SCF",
                     66.8084863573,
                     0.06680848635729998,
                     1.0e-06);
  tester.perform();
  if (passed.getValue()) {
    tester.report_passed();
  }

  tester.report_failed();
  return tester.all_passed() ? 0 : -1;
}
