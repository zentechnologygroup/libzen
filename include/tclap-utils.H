# ifndef TCLAP_UTILS_H
# define TCLAP_UTILS_H

# include <iostream>
# include <tclap/CmdLine.h>

# include <htlist.H>

# include "zen-exceptions.H"
# include "utils.H"
# include "units.H"

using namespace std;
using namespace TCLAP;

/** Range description for command line argument
   
   @ingroup Utils
 */
struct RangeDesc
{
  const Unit * unit_ptr = nullptr;
  double min = 0, max = 0;
  size_t n = 1; // num of steps

  RangeDesc(const Unit * unit_ptr = nullptr) : unit_ptr(unit_ptr) {}

  RangeDesc & operator = (const string & str)
  {
    istringstream iss(str);
    string data;
    iss >> data;
    if (not is_double(data))
      {
	unit_ptr = Unit::search(data);
	if (unit_ptr == nullptr)
	  ZENTHROW(CommandLineError, "Unit " + data + " not found");
	if (not (iss >> min))
	  ZENTHROW(CommandLineError, "RangeDesc: cannot read minimum value");
      }
    else
      min = atol(data);

    if (not (iss >> max >> n))
      ZENTHROW(CommandLineError, "RangeDesc: " + str +
	       " is not of form \"[unit-name] min max n\"");

    if (n <= 1)
      ZENTHROW(CommandLineError, ::to_string(n) + " n must be greater than 1");

    if (min > max)
      {
	ostringstream s;
	s << "min value " << min << " greater than max value " << max;
	ZENTHROW(CommandLineError, s.str());
      }

    return *this;
  }

  double step() const noexcept { return (max - min) / (n - 1); }

  friend ostream & operator << (ostream & os, const RangeDesc & d)
  {
    return os << d.min<< " " << d.max << " " << d.n;
  }

  DynList<double> values() const
  {
    DynList<double> l;
    const double step = this->step();
    double val = this->min;
    for (size_t i = 0; i < n; ++i, val += step)
      l.append(val);

    return l;
  }
};

struct Values
{
  const Unit * unit_ptr = nullptr;
  DynList<double> vals;
  size_t n = 0;

  Values(const Unit * unit_ptr) : unit_ptr(unit_ptr) {}

  Values & operator = (const string & str)
  {
    istringstream iss(str);
    string data;
    iss >> data;
    if (not is_double(data))
      {
	const Unit * unit_ptr = Unit::search(data);
	if (unit_ptr == nullptr)
	  ZENTHROW(CommandLineError, "Unit " + data + " not found");
	if (not this->unit_ptr->is_sibling(*unit_ptr))
	  ZENTHROW(CommandLineError, "Unit " + data + " is not for " +
		   this->unit_ptr->physical_quantity.name);
	this->unit_ptr = unit_ptr;
      }
    else
      {
	vals.append(atof(data));
	n = 1;;
      }

    while (iss >> data)
      {
	if (not is_double(data))
	  ZENTHROW(CommandLineError, "read data " + data + " is not a double");
	vals.append(atof(data));
	++n;
      }

    return *this;
  }

  friend ostream & operator << (ostream & os, const Values & values)
  {
    values.vals.for_each([&os] (auto & v) { os << v << " "; });
    return os << values.unit_ptr->name;
  }
};

// this variable should be defined in the command line interface
extern DynSetTree<string> par_name_tbl; 

// input parameter unit change specification
//
// form is: --unit "par-name unit"
struct ArgUnit
{
  string name;
  string unit_name;

  ArgUnit() {}

  ArgUnit & operator = (const string & str)
  {
    istringstream iss(str);
    if (not (iss >> name >> unit_name))
      ZENTHROW(CommandLineError, str + " is not a pair par-name unit");

    if (not par_name_tbl.contains(name))
      ZENTHROW(CommandLineError, name + " is an invalid parameter name");

    return *this;
  }

  friend ostream& operator << (ostream &os, const ArgUnit & a) 
  {
    return os << a.name << " " << a.unit_name;
  }
};

struct ValList
{
  DynList<string> vals;
  size_t n = 0;

  ValList & operator = (const string & str)
  {
    istringstream iss(str);
    string data;
    while (iss >> data)
      {
	vals.append(data);
	++n;
      }

    return *this;
  }

  friend ostream & operator << (ostream & os, const ValList & l)
  {
    return os << join(l.vals, " ");
  }
};


# endif
