#ifndef ZTG_UNIT_CONVERSION_TEST_H
#define ZTG_UNIT_CONVERSION_TEST_H

/* C++ System Headers */
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <cstdlib>

/* External headers */
#include "gtest/gtest.h"

/* Project headers */
#include "unitslist.hpp"

/* Tests headers */
#include "global_environment.hpp"

class UnitConversionTest : public ::testing::Test
{
protected:

  struct Conversion
  {
    std::string src_unit_name = "Undefined";
    std::string tgt_unit_name = "Undefined";
    double value = 0;
    double expected = 0;
    double tolerance = 0;
  };

  const std::string CSV_FILES_FILENAME = "./test/test_files/csv_files.txt";

  const std::string CSV_FILES_DIRECTORY = "./test/test_files";

  std::unordered_set<std::string> csv_filenames;

  void SetUp()
  {
    std::ifstream input;
    input.open(this->CSV_FILES_FILENAME);

    ASSERT_FALSE(not input) << "Could not open file "
                            << this->CSV_FILES_FILENAME;

    std::string csv_filename;

    while (input >> csv_filename) {
      if (not input.good()) {
        break;
      }

      this->csv_filenames.insert(csv_filename);
    }
  }

  bool read_csv_header(std::ifstream & input,
                       std::unordered_map<std::string, int> & columns)
  {
    std::string header;

    std::getline(input, header);

    if (not input.good()) {
      return false;
    }

    std::stringstream stream(header);
    std::string column_name;
    int column_index = 0;

    while (std::getline(stream, column_name, ',')) {
      columns.emplace(column_name, column_index++);
    }
  
    return true;
  }

  bool parse_line(const std::string & line,
                  std::unordered_map<std::string, int> & columns,
                  Conversion & conversion)
  {
    std::stringstream stream(line);
    std::vector<std::string> values;
    std::string value;

    while (std::getline(stream, value, ',')) {
      values.push_back(value);
    }

    // This checks for a trailing comma with no data after it.
    if (not stream and value.empty()) {
      values.push_back("");
    }

    if (values.size() != columns.size()) {
      return false;
    }

    conversion.src_unit_name = values[columns["convert from"]];
    conversion.tgt_unit_name = values[columns["convert to"]];

    char * end_ptr;
    const char * value_cstr = values[columns["value"]].c_str();
    conversion.value = std::strtod(value_cstr, &end_ptr);
    if (conversion.value == 0 and value_cstr == end_ptr) {
      return false;
    }
    value_cstr = values[columns["result"]].c_str();
    conversion.expected = std::strtod(value_cstr, &end_ptr);
    if (conversion.expected == 0 and value_cstr == end_ptr) {
      return false;
    }
    value_cstr = values[columns["tolerance"]].c_str();
    conversion.tolerance = std::strtod(value_cstr, &end_ptr);
    if (conversion.tolerance == 0 and value_cstr == end_ptr) {
      return false;
    }

    return true;
  }

}; // class UnitConversionTest

TEST_F(UnitConversionTest, Converts)
{
  auto verbose = testglobalenv::args.verbose;

  for (auto quantity : testglobalenv::args.physical_quantities) {
    if (verbose) {
      std::cout << "\n"
                << "---------------------------------------------------------\n"
                << "  Testing conversions for quantity " << quantity->name
                << "\n"
                << "---------------------------------------------------------\n"
                << std::endl;
    }

    auto csv_filename_iterator =
      this->csv_filenames.find(quantity->name + ".csv");

    if (csv_filename_iterator == this->csv_filenames.end()) {
      std::cerr << "\n[ WARNING ] There is no CSV conversions test file for "
                << "quantity " << quantity->name << ". Skipping it"
                << std::endl;

      continue;
    }

    std::string filename(*csv_filename_iterator);
    std::ifstream csv_input(this->CSV_FILES_DIRECTORY + "/" + filename);

    if (not csv_input.good()) {
      std::cerr << "\n[ WARNING ] CSV conversions test file for quantity "
                << quantity->name << " not found. Skipping quantity"
                << std::endl;

      continue;
    }

    std::unordered_map<std::string, int> columns;

    if (not this->read_csv_header(csv_input, columns)) {
      ADD_FAILURE() << "Could not read header in CSV conversions test file "
                    << "for quantity " << quantity->name << ". Skipping it";

      continue;
    }

    int line_number = 2;
    std::string line;

    while (std::getline(csv_input, line)) {
      Conversion conversion;
      int current_line_number = line_number++;

      if (not this->parse_line(line, columns, conversion)) {
        ADD_FAILURE() << "Malformed line " << current_line_number
                      << " in CSV conversions test file for quantity "
                      << quantity->name << ". Skipping it.";
        continue;
      }

      if (verbose) {
        std::cout << "   CSV " << filename << ", line " << current_line_number
                  << ":\n"
                  << "      Converting " << conversion.value << " "
                  << conversion.src_unit_name << " to "
                  << conversion.tgt_unit_name << "\n";
      }

      double result = unit_convert_name_to_name(conversion.src_unit_name,
                                                conversion.value,
                                                conversion.tgt_unit_name);

      EXPECT_LE((conversion.expected - result) / conversion.expected,
                conversion.tolerance)
          << "\n[In CSV " << filename
          << ", line " << current_line_number << "]: "
          << "Conversion for value " << conversion.value << " from unit "
          << conversion.src_unit_name << " to unit " << conversion.tgt_unit_name
          << " does not satisfy tolerance " << conversion.tolerance << "\n"
          << "  Expected result     = " << conversion.expected << "\n"
          << "  Actual result = " << result << std::endl;

      if (verbose) {
        std::cout << "      Done: " << result << " " << conversion.tgt_unit_name
                  << std::endl;
      }
    }

    if (verbose) {
      std::cout << "\n"
                << "---------------------------------------------------------\n"
                << "  [DONE] Testing conversions for quantity "
                << quantity->name << "\n"
                << "---------------------------------------------------------"
                << std::endl;
    }
  }
}

#endif //ZTG_UNIT_CONVERSION_TEST_H