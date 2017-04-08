# ifndef UTILS_H
# define UTILS_H

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

template <class C>
inline std::string Rvector(const std::string & name, const C & c)
{
  std::ostringstream s;
  s << name << " <- c(";
  auto last_ptr = &c.get_last();
  for (auto it = c.get_it(); it.has_curr(); it.next())
    {
      const auto & v = it.get_curr();
      s << v;
      if (&v != last_ptr)
	s << ", ";
    }
  s << ")";

  return s.str();
}

double interpolate(double x1, double x2, double y1, double y2, double x)
{
  assert(x > x1 and x < x2 and x >- x1);
  return y1 + (y2 - y1)*(x - x1)/(x2 - x1);
}    





# endif // UTILS_H
