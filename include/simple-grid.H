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
  Array<double> x;
  Array<double> y;

  using Pidx = pair<size_t, size_t>;

protected:

  static Pidx search_inteval(const Array<double> & a, const double x)
  {
    const double & first_x = a.get_first();
    const double & last_x = a.get_last();
    if (x < first_x or x > last_x)
      ZENTHROW(OutOfRange, to_string(x) + " is not inside [" +
	       to_string(first_x) + ", " + to_string(last_x) + "]");

    long i = Aleph::binary_search(a, x);
    assert(i >= 0);
    const double & found_x = a(i);
    if (x < found_x)
      {
	assert(i > 0);
	return Pidx(i - 1, i);
      }
    else if (x > found_x)
      {
	assert(size_t(i + 1) < a.size());
	return Pidx(i, i + 1);
      }
    else
      return Pidx(i, i);
  }

  void init_grid()
  {
    assert(is_sorted(x) or is_inversely_sorted(x));

    if (this->x.size() != this->y.size())
      ZENTHROW(SizeMismatch, "size of x = " + to_string(this->x.size()) +
	       " != size of y = " + to_string(this->y.size()));
    n = x.size();
    if (n <= 1)
      ZENTHROW(InvalidSize, "size of x and y are less than 2");
  }

public:

  template <class C>
  SimpleGrid(const C & x, const C & y) : x(x), y(y)
  {
    init_grid();
  }

  template <class C>
  SimpleGrid(C && x, C && y) : x(move(x)), y(move(y))
  {
    init_grid();
  }

  double compute_y(const double x) const
  {
    auto pidx = search_inteval(this->x, x);
    if (pidx.first == pidx.second)
      return vals(pidx.first).second;
    
    const size_t & i1 = pidx.first;
    const size_t & i2 = pidx.second;
    
    return interpolate(this->x(i1), this->x(i2), y(i1), y(i2), x);
  }

  double operator () (const double x) const
  {
    return compute_y(x);
  }

  double inverse(const double y) const
  {
    auto pidx = search_inteval(this->y, y);
    if (pidx.first == pidx.second)
      return vals(pidx.first).second;
    
    const size_t & i1 = pidx.first;
    const size_t & i2 = pidx.second;
    
    return interpolate(this->y(i1), this->y(i2), x(i1), x(i2), y);
  }

  const Array<double> & get_x() const noexcept { return x; };

  const Array<double> & get_y() const noexcept { return y; };

  double first_x() const noexcept { return x.get_first(); }

  double first_y() const noexcept { return y.get_first(); }

  double last_x() const noexcept { return x.get_last(); }

  double last_y() const noexcept { return y.get_last(); }
};

# endif
