#ifndef ZTG_CONVERSION_INTEGRITY_TEST_H
#define ZTG_CONVERSION_INTEGRITY_TEST_H

/* C++ System Headers */
#include <cmath>
#include <memory>
#include <algorithm>
#include <sstream>
#include <random>

/* External headers */
#include "gtest/gtest.h"

/* Project headers */
#include "unitslist.hpp"

/* Tests headers */
#include "global_environment.hpp"

class ConversionIntegrityTest : public ::testing::Test
{

protected:

  void generate_row(const Unit & unit, double val, double epsilon, bool verbose,
                    int precision, std::vector<std::string> & conversions)
  {
    VtlQuantity q(unit);

    try {
      if (verbose) {
        std::cout << "    sample = " << val << " (" << unit.symbol << ")"
                  << std::endl;
      }
      
      q = VtlQuantity(unit, val);

      if (verbose) {
        std::cout << "    Instantiated = " << q << std::endl;
      }
    }
    catch (std::exception & e) {
      std::ostringstream failMessage;
      failMessage << "Error with generated sample" << val << "\n"
                  << e.what() << "\n"
                  << "Sample " << val << " is not inside [" << unit.min_val
                  << ", " << unit.max_val << "]" << std::endl;

      FAIL() << failMessage.str();
    }

    //auto unit_family = to_vector(unit.family_units());
    
    //for (auto ut = unit.family_units().get_it(); ut.has_curr(); ut.next()) {
    for (const auto & unit_ptr : unit.family_units()) {
      VtlQuantity conv(*unit_ptr);
      
      try {
        if (verbose) {
          std::cout << "        Converting " << q << " to " << unit_ptr->symbol
                    << std::endl;
        }

        conv = VtlQuantity(*unit_ptr, q); // conversion

        if (verbose) {
          std::cout << "        done = " << conv << std::endl;
        }
      }
      catch (std::exception & e) {
        FAIL() << "Error converting " << q << " to " << unit_ptr->name << ": "
               << e.what() << std::endl;
      }

      if (verbose) {
        std::cout << "        Returning to " << unit.symbol << std::endl;
      }

      try {
        VtlQuantity inv(unit, conv);

        if (verbose) {
          std::cout << "        done = " << inv << "\n" << std::endl;
        }

        ASSERT_NEAR(q.get_value(), inv.get_value(), epsilon)
          << "\nConversion for value " << val << " from unit "
          << unit.name << " to unit " << unit_ptr->name
          << " does not satisfy epsilon threshold " << epsilon << "\n"
          << "  Original value     = " << q << "\n"
          << "  Intermediate value = " << conv << "\n"
          << "  Returned value = " << inv << std::endl;
      }
      catch (std::exception & e) {
        FAIL() << "Error converting " << unit.name << " to " << conv.unit.name
               << ": " << e.what() << std::endl;
      }

      conversions.push_back(double_to_string(conv.get_value(), precision));
    }
  }

  inline std::string double_to_string(double d, std::size_t precision)
  {
    std::ostringstream s;
    s.precision(precision);
    s << std::fixed << d;

    return s.str();
  }
}; // class ConversionIntegrityTest

TEST_F(ConversionIntegrityTest, ConvertExtremeValues)
{
  auto verbose = testglobalenv::args.verbose;
  auto epsilon = testglobalenv::args.epsilon;
  auto precision = testglobalenv::args.precision;
  auto max_range = testglobalenv::args.max_range;
  auto display_mode = testglobalenv::args.display_mode;

  if (verbose) {
    std::cout << "\nTesting with extremes\n" << std::endl;
  }

  for (auto quantity : testglobalenv::args.physical_quantities) {
    if (verbose) {
      std::cout << "\n"
              << "-----------------------------------------------------------\n"
              << "  Testing extreme values for " << quantity->name << "\n"
              << "-----------------------------------------------------------\n"
              << std::endl;
    }
    
    //auto units = to_vector(quantity->units());
    auto units = quantity->units();
    std::vector<std::vector<std::string>> rows;
  
    // generate the rows
    for (auto & unit_ptr : units) {
      const double min = unit_ptr->min_val;
      const double urange = std::min(unit_ptr->max_val - min, max_range);
      const double max = min + urange;

      std::vector<std::string> conversions;
      generate_row(*unit_ptr, min, epsilon, verbose, precision, conversions);
      generate_row(*unit_ptr, max, epsilon, verbose, precision, conversions);

      std::vector<std::string> row;
      row.push_back(unit_ptr->name);
      row.push_back(std::to_string(min));
      row.push_back(std::to_string(max));
      row.insert(row.end(), conversions.begin(), conversions.end());

      rows.push_back(row);
    }

    if (HasFatalFailure()) return;

    // generate title row
    std::vector<std::string> title{"Unit name"};
    std::vector<std::string> vals{"min", "max"};
    title.insert(title.end(), vals.begin(), vals.end());

    for (auto it = vals.begin(); it != vals.end(); it++) {
      const std::string & val = *it;
      for (const auto & unit : units) {
        const std::string name = val + "-" + unit->symbol;
        title.push_back(name);
      }
    }

    std::vector<std::vector<std::string>> matrix{std::move(title)};
    matrix.insert(matrix.end(), rows.begin(), rows.end());

    if (display_mode == "table") {
      std::cout << to_string(FormatTable(matrix)) << std::endl;
    }
    else if (display_mode == "csv") {
      std::cout << to_string(format_csv(matrix)) << std::endl;
    }
  }
}


TEST_F(ConversionIntegrityTest, ConvertRandomValues)
{
  using Puv = std::pair<const Unit * const, std::vector<double>>;

  auto verbose = testglobalenv::args.verbose;
  auto nsamples = testglobalenv::args.nsamples;
  auto epsilon = testglobalenv::args.epsilon;
  auto precision = testglobalenv::args.precision;
  auto max_range = testglobalenv::args.max_range;
  auto display_mode = testglobalenv::args.display_mode;

  std::mt19937 generator(testglobalenv::args.seed);
  std::uniform_real_distribution<double> distribution(0.0, 1.0);
  
  for (auto quantity : testglobalenv::args.physical_quantities) {
    if (verbose) {
      std::cout << "\n"
              << "-----------------------------------------------------------\n"
              << "  Testing " << nsamples << " random values for "
              << quantity->name << "\n"
              << "-----------------------------------------------------------\n"
              << std::endl;
    }

    // only the units related to physical quantity pq
    //auto units = to_vector(quantity->units());
    auto units = quantity->units();

    if (verbose) { 
      std::cout << "Generating random samples " << std::endl;
    }

    std::vector<Puv> samples;

    for (const auto & unit_ptr : units) {
      if (verbose) {
        std::cout << "    For " << unit_ptr->name << ":";
      }

      auto min = unit_ptr->min_val;
      auto urange = std::min(unit_ptr->max_val - min, max_range);
      std::vector<double> values;

      for (size_t i = 0; i < nsamples; ++i) {
        auto val = min + urange * distribution(generator);
        values.push_back(val);

        if (verbose) {
          std::cout << " " << val;
        }
      }

      if (verbose) {
        std::cout << std::endl;
      }

      samples.push_back(std::make_pair(unit_ptr, std::move(values)));
    }

    
    if (verbose) {
      std::cout << std::endl << "Testing " << std::endl << std::endl;
    }

    // generate the rows
    std::vector<std::vector<std::string>> rows(samples.size());

    std::transform(samples.begin(), samples.end(), rows.begin(),
                   [&units, epsilon, verbose, precision, this] (Puv & p)
                   {
                      std::vector<std::string> conversions;
                      const std::vector<double> & samples = p.second;

                      for (const auto & sample : samples) {
                        generate_row(*p.first, sample, epsilon, verbose,
                                     precision, conversions);
                      }
                      
                      std::vector<std::string> ret;
                      ret.push_back(p.first->name);
                      for (const auto & sample : samples) {
                        ret.push_back(std::to_string(sample));
                      }
                      ret.insert(ret.end(), conversions.begin(),
                                 conversions.end());

                      return ret;
                   });

    if (HasFatalFailure()) return;

    // generate title row
    std::vector<std::string> title{"Unit name"};
    std::vector<std::string> vals(nsamples, "sample-");
    for (int i = 0; i < nsamples; i++) {
      vals[0] += std::to_string(i);
    }

    title.insert(title.end(), vals.begin(), vals.end());

    for (auto it = vals.begin(); it != vals.end(); it++) {
      const std::string & val = *it;

      for (const auto & unit : units) {
        const std::string name = val + "-" + unit->symbol;
        title.push_back(name);
      }
    }

    std::vector<std::vector<std::string>> matrix{title};

    for (auto & row : rows) {
      matrix.push_back(row);
    }

    if (display_mode == "table") {
      std::cout << to_string(FormatTable(matrix)) << std::endl;
    }
    else if (display_mode == "csv") {
      std::cout << to_string(format_csv(matrix)) << std::endl;
    }
  }
}

/*
INSTANTIATE_TEST_CASE_P(
  Default, ConversionIntegrityTest,
  testing::ValuesIn(to_vector(PhysicalQuantity::names()))
);
*/

#endif //ZTG_CONVERSION_INTEGRITY_TEST_H