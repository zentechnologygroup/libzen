# ifndef TCLAP_UTILS_H
# define TCLAP_UTILS_H

# include <iostream>
# include <tclap/CmdLine.h>

# include <htlist.H>

# include "zen-exceptions.H"

using namespace std;
using namespace TCLAP;

/** Range description for command line argument
   
   @ingroup Utils
 */
struct RangeDesc
{
  double min = 0, max = 0;
  size_t n = 1; // num of steps

  RangeDesc & operator = (const string & str)
  {
    istringstream iss(str);
    if (not (iss >> min >> max >> n))
      ZENTHROW(CommandLineError, str + " is not of form \"min max n\"");

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


# endif
