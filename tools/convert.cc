#include <fstream>						// Files stream
#include <istream>						// Input stream					
#include <tclap/CmdLine.h>		// Parses the command line
#include <iomanip>						// IO Manipulators

#include "unitslist.hpp"

using namespace TCLAP;

const Unit * search_unit(const std::string & name)
{
  auto unit_ptr = Unit::search_by_name(name);
  if (unit_ptr == nullptr)
    {
      unit_ptr = Unit::search_by_symbol(name);
      if (unit_ptr == nullptr)
	{
	  std::cout << "Unit " << name << " not found" << std::endl;
	  abort();
	}
    }
  return unit_ptr;
}

void convert(const Unit * src_unit, const Unit * tgt_unit, std::istream & in)
{
  double val;
  while (in >> val)
    std::cout << unit_convert(*src_unit, val, *tgt_unit) << " ";
  std::cout << std::endl;
}

std::string generate_horizontal_line(std::vector <int> & line_width) {

	std::string line = "+";

	int count = line_width.size();

	for(auto entry: line_width) {
		count--;
		line += std::string(entry, '-');
		line += "+";
	}

	return line;
}

void list_all_units()
{
  std::vector<std::vector<std::string>> rows;
  auto quantitie_vector = PhysicalQuantity::quantities();

  std::vector<int> line_width{28,18,15,28,25,28};
	std::cout << "\n" << generate_horizontal_line(line_width) << "\n";
	std::cout << '|' << std::left << std::setw(28) << "     Physical-Quantity"
						<< '|' << std::left << std::setw(18) << "      Symbol"
						<< '|' << std::left << std::setw(15) << "  LaTeX Symbol"
						<< '|' << std::left << std::setw(28) << "         Unit Name"
						<< '|' << std::left << std::setw(25) << "        Unit Symbol"
						<< '|' << std::left << std::setw(28) << "        LaTeX symbol"
						<< '|' << std::endl;



	std::cout << generate_horizontal_line(line_width) << std::endl;


  for(auto entry: quantitie_vector) {

  	std::vector<const Unit * > unit_vector = entry->units();
    std::vector<std::string> info_unit_vector;

    for(auto unit: unit_vector){

			std::cout << '|' << std::left << std::setw(28) << entry->name
								<< '|' << std::left << std::setw(18) << entry->symbol
								<< '|' << std::left << std::setw(15) << entry->latex_symbol
								<< '|' << std::left << std::setw(28) << unit->name
								<< '|' << std::left << std::setw(25) << unit->symbol
								<< '|' << std::left << std::setw(28) << unit->latex_symbol
								<< '|' << std::endl;
			
    }
  	std::cout << generate_horizontal_line(line_width) << std::endl;
  }

	exit(0);
}

void test(int argc, char *argv[])
{
	CmdLine cmd(argv[0], ' ', "0");

	std::vector<std::string> units;
	auto units_vector = Unit::units();
	for(auto entry : units_vector){
		units.push_back(entry->symbol);
	}


  ValuesConstraint<std::string> allowed(units);
  ValueArg<std::string> unit = { "u", "unit-symbol", "symbol of unit", false, "", &allowed, cmd };
  MultiArg<std::string> unit_desc = { "U", "Unit-symbol", "describe unit", false, &allowed, cmd };
  ValueArg<double> sample = {"s", "sample", "sample", false, 0, "sample", cmd};
  ValueArg<std::string> source = {"S", "source-unit", "source unit", false,"", "source unit", cmd};
  ValueArg<std::string> target = {"T", "target-unit", "target unit", false,"", "target unit", cmd};
  SwitchArg l = { "l", "list", "list all units", cmd, false };
  SwitchArg v("v", "verbose", "verbose mode", cmd, false);
  ValueArg<std::string> file = { "f", "file", "input file name", false, "","input file name", cmd };
  SwitchArg pipe = { "p", "pipe", "input by cin", cmd };

  cmd.parse(argc, argv);

  if (l.getValue())
    if (not unit.isSet())
      list_all_units();


  auto verbose = v.getValue();

  if (unit_desc.isSet())
    {
      for (const auto & s : unit_desc.getValue())
	std::cout << Unit::search_by_symbol(s)->to_string(2) << std::endl
	     << std::endl;
      exit(0);
    }

  if (source.isSet() and target.isSet())
    {
      auto src_ptr = search_unit(source.getValue());
      auto tgt_ptr = search_unit(target.getValue());

      if (file.isSet() or pipe.getValue())
	{
	  if (pipe.isSet())
	    convert(src_ptr, tgt_ptr, std::cin);
	  else
	    {
	      std::ifstream in(file.getValue());
	      if (not in.good())
		{
		  std::cout << "Cannot open " << file.getValue() << std::endl;
		  abort();
		}
	      convert(src_ptr, tgt_ptr, in);
	    }
	  exit(0);
	}

      VtlQuantity val(*src_ptr, sample.getValue());
      std::cout << VtlQuantity(*tgt_ptr, val).raw() << std::endl;
      exit(0);
    }

  if (not unit.isSet() and not sample.isSet())
    {
      std::cout << "Flags -u and -s must be set" << std::endl;
      abort();
    }

  auto unit_ptr = search_unit(unit.getValue());
  if (unit_ptr == nullptr)
    {
      std::cout << "Unit symbol " << unit.getValue() << " not found" << std::endl;
      abort();
    }

  std::cout << *unit_ptr << std::endl
       << std::endl
       << "Conversions:" << std::endl
       << std::endl;

  VtlQuantity val(*unit_ptr, sample.getValue());

  for (auto u : Unit::units(unit_ptr->physical_quantity))
    {
      if (verbose)
	std::cout << "    " << val << " to " << u->symbol << std::endl;
      if (exist_conversion(*unit_ptr, *u))
	std::cout << "    " << val << " = " << VtlQuantity(*u, val) << std::endl;
      else
	std::cout << "    "  << val << " = "
	     << "WARNING: there is no conversion from " << unit_ptr->symbol
	     << " to " << u->symbol << std::endl;
    }
  std::cout << std::endl;
}

int main(int argc, char *argv[])
{
  test(argc, argv);
  return 0;
}
