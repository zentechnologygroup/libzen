#include <iostream>
#include <chrono>

#include "gtest/gtest.h"
#include <tclap/CmdLine.h>

#include "unitslist.hpp"
#include "global_environment.hpp"
#include "conversion_integrity_test.hpp"
#include "unit_conversion_test.hpp"

class Epsilon
{
public:

  std::string symbol;
  double epsilon;

  Epsilon & operator = (const std::string & str)
  {
    std::istringstream iss(str);
    if (not (iss >> symbol >> epsilon))
      throw TCLAP::ArgParseException(str + " is not a pair unit-symbol epsilon");

    return *this;
  }

  friend std::ostream& operator << (std::ostream &os, const Epsilon & a) 
  {
    return os << a.symbol << " " << a.epsilon;
  }
  
  std::ostream& print(std::ostream &os) const
  {
    return os << *this;
  }
};

namespace TCLAP
{
  template<> struct ArgTraits<Epsilon> { typedef StringLike ValueCategory; };
}

TestArguments parse_arguments(int argc, char ** argv)
{
  TCLAP::CmdLine cmd(argv[0], ' ', "0");

  TCLAP::ValueArg<size_t> nsamples("n", "num-samples",
                                   "number of random samples",
                                   false, 3, "number of samples", cmd);

  TCLAP::ValueArg<double> max_range("m", "max", "maximum range of a unit",
                                    false, 1000, "maximum range of a unit",
                                    cmd);

  unsigned long default_seed =
    std::chrono::system_clock::now().time_since_epoch().count();
  TCLAP::ValueArg<unsigned long> seed("s", "seed",
                                      "seed for random number generator",
                                      false, default_seed, "random seed", cmd);

  std::vector<std::string> allowed_display_values{"table", "csv", "none"};
  TCLAP::ValuesConstraint<std::string> allowed_display(allowed_display_values);
  TCLAP::ValueArg<std::string> display_mode("D", "display", "display mode",
                                            false, "none", &allowed_display,
                                            cmd);

  TCLAP::ValueArg<double> epsilon("E", "Epsilon",
                                  "precision threshold for numeric comparaisons",
                                  false, 1e-4, "precision threshold", cmd);

  TCLAP::MultiArg<Epsilon> epsilons("e", "epsilon",
                                    "epsilon of form \"unit-symbol epsilon\"",
                                    false, "epsilon threshold", cmd);

  std::vector<std::string> physical_quantities = PhysicalQuantity::names();
  for (const auto & p : PhysicalQuantity::quantities()) {
    physical_quantities.push_back(p->name);
  }
  physical_quantities.push_back("");
  TCLAP::ValuesConstraint<std::string> allowed(physical_quantities);
  TCLAP::ValueArg<std::string> physical_quantity_name("Q", "physical-quantity",
                                                 "name of physical quantity",
                                                 false, "", &allowed, cmd);

  TCLAP::SwitchArg print("p", "print", "print units", cmd, false);

  TCLAP::SwitchArg print_pq("P", "print-pq", "print physical quantities", cmd,
                            false);

  TCLAP::SwitchArg ver("v", "verbose", "verbose mode", cmd, false);

  TCLAP::ValueArg<size_t> digits("d", "digits", "number of digits", false, 6,
                                 "number of digits", cmd);

  cmd.parse(argc, argv);
  
  if (print_pq.getValue()) {
    for (const auto & name : PhysicalQuantity::names()) {
      std::cout << name << std::endl;
    }
    
    exit(0);
  }
        
  /*
  if (not physical_quantity_name.isSet()){ 
    std::cerr << "PARSE ERROR:\n"
              << "\tRequired argument missing: physical-quantity"
              << std::endl;
    abort();
  }
  */

  /*
  std::unique_ptr<gsl_rng, decltype(gsl_rng_free)*>
    r(gsl_rng_alloc(gsl_rng_mt19937), gsl_rng_free);
  gsl_rng_set(r.get(), seed.getValue() % gsl_rng_max(r.get()));
  */

  std::vector<const PhysicalQuantity *> physical_quantities_to_test;

  if (physical_quantity_name.getValue() != "") {
    auto physical_quantity_ptr =
      PhysicalQuantity::search(physical_quantity_name.getValue());

    if (physical_quantity_ptr == nullptr) {
      std::cerr << "Physical quantity " << physical_quantity_name.getValue()
                << " not found " << std::endl;
      abort();
    }

    auto conversions_check_result = check_conversions(*physical_quantity_ptr);

    if (not conversions_check_result.first) {
      std::cerr << "Missing conversions: " << std::endl;
      for (const auto & conversion : conversions_check_result.second) {
        std::cout << "  " << conversion << std::endl;
      }

      abort();
    }

    if (print.getValue() and physical_quantity_ptr != nullptr) {
      std::cout << physical_quantity_ptr->to_string(60) << std::endl;
      for (const auto & unit : physical_quantity_ptr->units()) {
        std::cout << *unit << std::endl << std::endl;
      }
    }

    physical_quantities_to_test.push_back(physical_quantity_ptr);
  }
  else {
    physical_quantities_to_test = PhysicalQuantity::quantities();
  }

  for (auto ep : epsilons.getValue()) {
    auto unit_ptr = Unit::search_by_symbol(ep.symbol);

    if (unit_ptr == nullptr) {
      std::cerr << "In epsilon specification: unit symbol " << ep.symbol
                << " not found" << std::endl;
      abort();
    }

    if (ep.epsilon <= 0 or ep.epsilon >= 1) {
      std::cerr << "In epsilon specification of unit" << unit_ptr->name
                << " (" << ep.symbol << "): value " << ep.epsilon
                << " is not inside the range (0, 1)" << std::endl;
      abort();
    }
  
    unit_ptr->set_epsilon(ep.epsilon);
  }

  /*
  if (digits.isSet()) {
    precision = digits.getValue();
  }
  */

  std::cout << "Seed = " << seed.getValue() << std::endl;

  return TestArguments{nsamples.getValue(), max_range.getValue(),
                       epsilon.getValue(), physical_quantities_to_test,
                       digits.getValue(), display_mode.getValue(),
                       ver.getValue(), seed.getValue()};

  /*
  DynList<DynList<string>> mat;
  if (extremes.getValue())
    mat = test_extremes_conversions(*physical_quantity_ptr, verbose,
            max_range.getValue(), epsilon.getValue());
  else
    mat = test_random_conversions(*physical_quantity_ptr, verbose, nsamples.getValue(),
          max_range.getValue(), epsilon.getValue(), r.get());
  
  cout << "Seed = " << seed.getValue() << std::endl;

  if (csv.getValue())
    cout << to_string(format_string_csv(mat)) << std::endl;
  else
    cout << to_string(format_string(mat)) << std::endl;
  */
}

int main(int argc, char ** argv)
{
  // Parse gtest command line arguments 
  ::testing::InitGoogleTest(&argc, argv);

  // Parse non-gtest command line arguments
  auto custom_arguments = parse_arguments(argc, argv);
  ::testing::AddGlobalTestEnvironment(new TestGlobalEnvironment(custom_arguments));

  return RUN_ALL_TESTS();
}