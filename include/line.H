#ifndef LINE_H
#define LINE_H

# include <zen-exceptions.H>

struct LineEq
{
  mutable double y0 = 0;
  mutable double m = 1;

  LineEq(const double __y0, const double __m) : y0(__y0), m(__m) {}

  LineEq(const double x1, const double x2, const double y1, const double y2)
  {
    if (x1 >= x2)
      ZENTHROW(OutOfRange, "value x1 = " + to_string(x1) +
	       " is greater or equal than x2 = " + to_string(x2));
    if (y1 == y2)
      ZENTHROW(OutOfRange, "value of y1 = " + to_string(y1) + " == y2 = " +
	       to_string(y2));
    m = (y2 - y1)/(x2 - x1);
    y0 = y1 - m*x1;
  }

  double operator() (const double x) const noexcept { return y0 + m*x; }

  pair<double, double> intersection(const LineEq & l) const
  {
    if (m == l.m)
      ZENTHROW(OutOfRange, "parallel lines");

    double x = (y0 - l.y0)/(l.m - m);

    return pair<double, double>(x, (*this)(x));
  }
};

#endif
 
