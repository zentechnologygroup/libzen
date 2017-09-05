/** Zen Polynome definition and evaluation

 */
#ifndef POLY_H
#define POLY_H

# include <memory>
# include <iostream>
# include <complex>

# include <gsl/gsl_complex.h>
# include <gsl/gsl_poly.h>

# include <ahFunctional.H>
# include <tpl_array.H>

# include <zen-exceptions.H>

DEFINE_ZEN_EXCEPTION(RootFindingAlgorithmFailed, "root finding failed");

/** Define and perform evaluations of a polynome

   @ingroup Utils
   @author Leandro Rabindranath Leon
 */
class Polynome
{
  Array<double> coefs;

public:

  /// Return `true` if the polynome is zero
  bool is_empty() const noexcept { return coefs.is_empty(); }

  /// Return `true` if the polynome is zero
  bool is_zero() const noexcept { return coefs.is_empty(); }

  /** Set or change polynome coefficients.

      First parameter is corresponds to coefficient of degree 0 (x^0),
      second corresponds to degree 1 (x^1) and so on.
   */
  template <typename ... Args> void set(Args ... args)
  {
    coefs.nappend(args...);
  }

  /** Create a new polynome given its coefficients sorted from x^0
      until the highest degree.

      Note that you must specify all the coefficients from 0 to n
      degree, event if any coefficient is zero
   */
  template <typename ... Args> Polynome(Args ... args)
  {
    set(args...);
  }

  /// Create a empty polynome
  Polynome()
  {
    assert(coefs.is_empty());
  }

  /// Return the value of polynome evaluated at `x`
  double eval(double x) const noexcept
  {
    if (coefs.is_empty())
      return 0;

    return gsl_poly_eval(&coefs.base(), coefs.size(), x);
  }

  /// Return an array of coefficients sorted from zero degree until
  /// highest degree
  const Array<double> & get_coefs() const noexcept { return coefs; }

  /** Return a list with the roots of polynome
      
      Each item of list is of standard type `complex`. You could know
      whether the root is real or not by looking up its complex part
      (zero if is real)
   */
  DynList<complex<double>> roots() const
  {
    const size_t n = coefs.size();
    unique_ptr<double[]> roots(new double[2*(n - 1)]);
    gsl_poly_complex_workspace * w = gsl_poly_complex_workspace_alloc(n);
    if (not w)
      ZENTHROW(OutOfMemory, "No enough memory");

    int status = gsl_poly_complex_solve(&coefs.base(), n, w, roots.get());
    if (status != GSL_SUCCESS)
      ZENTHROW(RootFindingAlgorithmFailed, "Roots findinf failed with code " +
	       ::to_string(status));

    gsl_poly_complex_workspace_free(w);

    DynList<complex<double>> ret;
    for (size_t i = 0; i < n; ++i)
      ret.emplace(roots[2*i], roots[2*i + 1]);

    return ret;
  }

  /// Return a string of form c0 + c1*x + ... + cn*x^n
  string to_string() const
  {
    if (coefs.is_empty())
      return "Not defined";
    
    ostringstream s;
    s << coefs.get_first();
    size_t i = 1;
    for (auto it = coefs.get_it(1); it.has_curr(); it.next(), ++i)
      {
	s << " + " << it.get_curr() << "*x";
	if (i > 1)
	  s << "^" << i;
      }
    return s.str();
  }

  /** Evaluate the polynome in a range.

      This function takes an range [start, end], divides it in n
      steps, and returns a list of pair x,y where x belongs to the
      interval and y is the polynome evaluated at x
   */
  DynList<pair<double, double>> eval(double start, double end, size_t n) const
  {
    if (n == 0)
      ZENTHROW(InvalidValue, "n cannot be zero");

    const double step = n > 1 ? (end - start) / (n - 1) : end - start;
    double x = start;
    DynList<pair<double, double>> ret;
    for (size_t i = 0; i < n; ++i, x += step)
      ret.append(make_pair(x, eval(x)));

    return ret;
  }

  friend ostream & operator << (ostream & out, const Polynome & p)
  {
    return out << p.to_string();
  }

  DynList<string> to_dynlist() const
  {
    return coefs.maps<string>([] (auto c) { return ::to_string(c); });
  }
};

#endif
