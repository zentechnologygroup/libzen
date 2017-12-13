# ifndef STATS_H
# define STATS_H

# include <tpl_array.H>

struct SimpleStats
{
  mutable double mean = 0;
  mutable double variance = 0;
  mutable double sigma = 0;
  mutable size_t n = 0;
  mutable bool valid = false;

  template <class C> SimpleStats(const C & c)
  {
    const double sum = c.foldl(0.0, [this] (auto acu, auto v)
			       {
				 n++;
				 return acu + v;
			       });
    mean = sum/n;

    const double sum2 = c.foldl(0.0, [this] (auto acu, auto v)
				{
				  const double e = v - mean;
				  return acu + e*e;
				});
    variance = sum2/n;
    sigma = sqrt(variance);
    valid = true;
  }
};

# endif
