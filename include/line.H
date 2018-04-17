/** Line equation helper class

    Aleph-w Leandro Rabindranath Leon    
 */

#ifndef LINE_H
#define LINE_H

# include <aleph-exceptions.H>

/** Build a Lin equation
   
    @author Leandro Rabindranath Leon
    @ingroup Utils
 */
struct LineEq
{
  mutable double y0 = 0;
  mutable double m = 1;

  /// Build y = x
  LineEq() {}

  /// Build a line given cut with y axis and its slope
  LineEq(const double __y0, const double __m) : y0(__y0), m(__m) {}

  /// Build a line given a point (x1,y1) and its slope
  LineEq(const double x1, const double y1, const double __m) : m(__m)
  {
    y0 = y1 - m*x1;
  }

  /// Build a line given two points
  LineEq(const double x1, const double y1, const double x2, const double y2)
  {
    if (x1 >= x2)
      ALEPHTHROW(OutOfRange, "value x1 = " + ::to_string(x1) +
	       " is greater or equal than x2 = " + ::to_string(x2));
    if (y1 == y2)
      ALEPHTHROW(OutOfRange, "value of y1 = " + ::to_string(y1) + " == y2 = " +
	       ::to_string(y2));
    m = (y2 - y1)/(x2 - x1);
    y0 = y1 - m*x1;
  }

  /// Return the line value at x value
  double operator() (const double x) const noexcept { return y0 + m*x; }

  /// Return a pair with the intersection point of this with
  /// `l`. Throws `OutOfRange` if lines are parallel
  pair<double, double> intersection(const LineEq & l) const
  {
    if (m == l.m)
      ALEPHTHROW(OutOfRange, "parallel lines");

    double x = (y0 - l.y0)/(l.m - m);

    return pair<double, double>(x, (*this)(x));
  }

  bool operator == (const LineEq & l) const noexcept
  {
    return y0 == l.y0 and m == l.m;
  }

  bool operator != (const LineEq & l) const noexcept
  {
    return not (*this == l);
  }

  string to_string() const
  {
    ostringstream s;
    s << "y = " << y0 << " + " << m << " * x";
    return s.str();
  }

  friend ostream & operator << (ostream & out, const LineEq & l)
  {
    return out << l.to_string();
  }
};

#endif
 
