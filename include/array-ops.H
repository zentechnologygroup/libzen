# ifndef ARRAY_OPS_H
# define ARRAY_OPS_H

#include <tpl_array.H>

inline double array_sum(const Array<double> & a)
{
  return a.foldl(0, [] (auto & acu, auto & v) { return acu + v; });
}

inline Array<double> array_pow(const Array<double> & a, double p)
{
  const size_t & n = a.size();
  Array<double> ret;
  ret.reserve(n);
  ret.putn(n);
  for (size_t i = 0; i < n; ++i)
    ret(i) = pow(a(i), p);

  return ret;
}

inline Array<double>
array_mult(const Array<double> & a1, const Array<double> & a2)
{
  const size_t & n = a1.size();
  Array<double> ret;
  ret.reserve(n);
  ret.putn(n);
  for (size_t i = 0; i < n; ++i)
    ret(i) = a1(i)*a2(i);

  return ret;
}

inline Array<double>
array_diff(const Array<double> & a1, const Array<double> & a2)
{
  const size_t & n = a1.size();
  Array<double> ret;
  ret.reserve(n);
  ret.putn(n);
  for (size_t i = 0; i < n; ++i)
    ret(i) = a1(i) - a2(i);

  return ret;
}

# endif
