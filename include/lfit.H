# ifndef LFIT_H
# define LFIT_H

# include <gsl/gsl_fit.h>

# include <string>
# include <tpl_array.H>

# include <zen-exceptions.H>

struct LFit
{
  mutable double c = 0;
  mutable double m = 1;
  mutable double cov00 = 0;
  mutable double cov01 = 0;
  mutable double cov11 = 0;
  mutable double sumsq = 0;

  LFit() noexcept {}

  LFit(const Array<double> & x, const Array<double> & y)
  {
    if (x.size() != y.size())
      ZENTHROW(SizeMismatch, "x and y have different sizes");

    if (y.size() == 1)
      ZENTHROW(SizeMismatch, "arrays have lenght = 1");

    gsl_fit_linear(&x.base(), 1, &y.base(), 1, y.size(), &c, &m,
		   &cov00, &cov01, &cov11, &sumsq);
  }

  //    y,    error
  pair<double, double> predict(double x) const noexcept
  {
    double y = 0, y_err = 0;
    gsl_fit_linear_est(x, c, m, cov00, cov01, cov11, &y, &y_err);
    return make_pair(y, y_err);
  }
};



# endif
