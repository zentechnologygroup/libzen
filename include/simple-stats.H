# ifndef SIMPLE_STATS_H
# define SIMPLE_STATS_H

# include <tpl_array.H>

struct SimpleStats
{
  mutable double mean = 0;
  mutable double variance = 0;
  mutable double sigma = 0;
  mutable size_t n = 0;
  mutable bool valid = false;
  mutable Array<double> samples;

  template <class C> SimpleStats(const C & c) : samples(c)
  {
    n = samples.size();
    const double sum = c.foldl(0.0, [] (auto acu, auto v) { return acu + v; });
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

  double diff_mean(const SimpleStats & s) const noexcept
  {
    const double diff = fabs(mean - s.mean);
    return diff/mean;
  }
};

# endif
