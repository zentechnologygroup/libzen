
#include <cassert>
#include <tclap/CmdLine.h>
#include <units/pvt-units.H>
#include <units/unittest-utils.H>

using namespace TCLAP;

CmdLine cmd = { "GORGLRvolumeRatio", ' ', "0" };

SwitchArg passed = { "p", "passed", "Only print passed tests", cmd };

int
main(int argc, char* argv[])
{
  UnitTester tester;

  cmd.parse(argc, argv);
  tester.define_test("GORGLRvolumeRatio.csv",
                     2,
                     "SCF_STB",
                     "Mscf_STB",
                     515.058706049,
                     0.5150587060489,
                     1.0e-06);
  tester.define_test("GORGLRvolumeRatio.csv",
                     3,
                     "SCF_STB",
                     "MMscf_STB",
                     515.058706049,
                     0.000515058706049,
                     1.0e-06);
  tester.define_test("GORGLRvolumeRatio.csv",
                     4,
                     "SCF_STB",
                     "Sm3_Sm3",
                     515.058706049,
                     91.73587343357032,
                     1.0e-06);
  tester.define_test("GORGLRvolumeRatio.csv",
                     5,
                     "Mscf_STB",
                     "SCF_STB",
                     172.849161318,
                     172849.1613176,
                     1.0e-06);
  tester.define_test("GORGLRvolumeRatio.csv",
                     6,
                     "Mscf_STB",
                     "MMscf_STB",
                     172.849161318,
                     0.17284916131759995,
                     1.0e-06);
  tester.define_test("GORGLRvolumeRatio.csv",
                     7,
                     "Mscf_STB",
                     "Sm3_Sm3",
                     172.849161318,
                     30785.750438756215,
                     1.0e-06);
  tester.define_test("GORGLRvolumeRatio.csv",
                     8,
                     "MMscf_STB",
                     "SCF_STB",
                     529.844041681,
                     529844041.6809,
                     1.0e-06);
  tester.define_test("GORGLRvolumeRatio.csv",
                     9,
                     "MMscf_STB",
                     "Mscf_STB",
                     529.844041681,
                     529844.0419999999,
                     1.0e-06);
  tester.define_test("GORGLRvolumeRatio.csv",
                     10,
                     "MMscf_STB",
                     "Sm3_Sm3",
                     529.844041681,
                     94369254.23376623,
                     1.0e-06);
  tester.define_test("GORGLRvolumeRatio.csv",
                     11,
                     "Sm3_Sm3",
                     "SCF_STB",
                     811.3728226162,
                     4555.52032698053,
                     1.0e-06);
  tester.define_test("GORGLRvolumeRatio.csv",
                     12,
                     "Sm3_Sm3",
                     "Mscf_STB",
                     811.3728226162,
                     4.55552032698053,
                     1.0e-06);
  tester.define_test("GORGLRvolumeRatio.csv",
                     13,
                     "Sm3_Sm3",
                     "MMscf_STB",
                     811.3728226162,
                     0.004555520326981,
                     1.0e-06);
  tester.perform();
  if (passed.getValue()) {
    tester.report_passed();
  }

  tester.report_failed();
  return tester.all_passed() ? 0 : -1;
}
