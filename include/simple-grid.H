# ifndef SIMPLE_GRID_H
# define SIMPLE_GRID_H

# include <ahFunctional.H>
# include <ah-zip.H>
# include <ahSort.H>
# include <tpl_array.H>

# include <zen-exceptions.H>

class SimpleGrid
{ //                x,    y
  using P = pair<double, double>;

  size_t n = 0;
  Array<P> vals;

  using Pidx = pair<size_t, size_t>;

  Pidx search_inteval(double x) const
  {
    const double & first_x = vals(0).first;
    const double & last_x = vals(n - 1).first;
    if (x < first_x or x > last_x)
      ZENTHROW(OutOfRange, to_string(x) + " is not inside [" +
	       to_string(first_x) + ", " + to_string(last_x) + "]");

    P p; p.first = x;
    long i = Aleph::binary_search(vals, p, [] (const P & p1, const P & p2)
				  { return p1.first < p2.first; });
    assert(i >= 0);
    const double & found_x = vals(i).first;
    if (x < found_x)
      {
	assert(i > 0);
	return Pidx(i - 1, i);
      }
    else if (x > found_x)
      {
	assert(size_t(i + 1) < n);
	return Pidx(i, i + 1);
      }
    else
      return Pidx(i, i);
  }

public:

  template <class C>
  SimpleGrid(const C & x, const C & y)
  {
    assert(is_sorted(x) or is_inversely_sorted(x));
    for (auto it = zip_it(x, y); it.has_curr(); it.next())
      {
	auto curr = it.get_curr();
	vals.append(P(get<0>(curr), get<1>(curr)));
      }
    n = vals.size();
    if (n <= 1)
      ZENTHROW(InvalidSize, "size of x and y are less than 2");
  }

  double operator () (const double x) const
  {
    auto pidx = search_inteval(x);
    if (pidx.first == pidx.second)
      return vals(pidx.first).second;
    
    const auto & p1 = vals(pidx.first);
    const auto & p2 = vals(pidx.second);
    
    return interpolate(p1.first, p2.first, p1.second, p2.second, x);
  }

  DynList<double> get_x() const
  {
    return vals.maps<double>([] (auto &p) { return p.first; });
  }

  DynList<double> get_y() const
  {
    return vals.maps<double>([] (auto &p) { return p.second; });
  }

  double first_x() const noexcept { return vals.get_first().first; }

  double first_y() const noexcept { return vals.get_first().second; }

  double last_x() const noexcept { return vals.get_last().first; }

  double last_y() const noexcept { return vals.get_last().second; }
};

# endif
