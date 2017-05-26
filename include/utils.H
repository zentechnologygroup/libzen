# ifndef UTILS_H
# define UTILS_H

# include <sys/stat.h>
# include <cstdlib>
# include <memory>
# include <cxxabi.h>
# include <string>
# include <sstream>
# include <typeinfo>

# include <ah-convert.H>
# include <htlist.H>
# include <tpl_array.H>

inline std::string demangle(const char* name)
{
  int status = -4; // some arbitrary value to eliminate the compiler warning
  // enable c++11 by passing the flag -std=c++11 to g++
  std::unique_ptr<char, void(*)(void*)> res
    { abi::__cxa_demangle(name, NULL, NULL, &status), std::free };
  return (status==0) ? res.get() : name ;
}

# define CLASSNAME_TO_STRING(class_ptr) demangle(typeid(*class_ptr).name())

inline bool exists_file(const string & name)
{
  struct stat buffer;
  return (stat (name.c_str(), &buffer) == 0);
}

template <class C>
inline std::string Rvector(const std::string & name, const C & c)
{
  std::ostringstream s;
  s << name << " <- c(";
  auto last_ptr = &c.get_last();
  for (auto it = c.get_it(); it.has_curr(); it.next())
    {
      auto & v = it.get_curr();
      s << v;
      if (&v != last_ptr)
	s << ", ";
    }
  s << ")";

  return s.str();
}

inline
double interpolate(double x1, double x2, double y1, double y2, double x)
{
  assert(x2 > x1 and x < x2 and x > x1);
  return y1 + (y2 - y1)*(x - x1)/(x2 - x1);
}    

inline
double extrapolate_left(double x1, double x2, double y1, double y2, double x)
{
  assert(x2 > x1 and x < x1);
  return y1 - (y2 - y1)*(x1 - x)/(x2 - x1);
}    

inline
double extrapolate_right(double x1, double x2, double y1, double y2, double x)
{
  assert(x2 > x1 and x > x2);
  return y2 - (y2 - y1)*(x - x2)/(x2 - x1);
}    

inline double next_value(double val)
{
  return nextafter(val, numeric_limits<double>::max());
}

inline double prev_value(double val)
{
  return nextafter(val, numeric_limits<double>::min());
}



# endif // UTILS_H
