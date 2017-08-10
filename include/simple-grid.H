# ifndef SIMPLE_GRID_H
# define SIMPLE_GRID_H

# include <ah-string-utils.H>
# include <parse-csv.H>
# include <ahFunctional.H>
# include <ah-zip.H>
# include <ahSort.H>
# include <tpl_array.H>

# include <zen-exceptions.H>

class SimpleGrid
{ //                x,    y
  using P = pair<double, double>;

  size_t n = 0;
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
  SimpleGrid(C && x, C && y) : x(forward<C>(x)), y(forward<C>(y))
  {
    init_grid();
  }

  SimpleGrid(ifstream & in)
  {
    Array<double> x, y;
    Array<string> row = csv_read_row(in); // this would be he header
    if (row.is_empty())
      ZENTHROW(InvalidCsvHeader, "cannot read csv header");
    if (row.size() < 2)
      ZENTHROW(InvalidCsvHeader, "csv header must have at least two columns");
    for (size_t line = 1; true; ++line)
      {
	row = csv_read_row(in);
	if (row.size() == 0)
	  break;
	if (row.size() < 2)
	  ZENTHROW(InvalidCsvRow, "csv row " + to_string(line) +
		   " must have at least two columns");
	string data = row(0);
	if (not is_double(data))
	  ZENTHROW(InvalidCsvRow, "first column " + data +
		   " in row " + to_string(line) + " is not a double");
	x.append(atof(data));
	data = row(1);
	if (not is_double(data))
	  ZENTHROW(InvalidCsvRow, "second column " + data +
		   " in row " + to_string(line) + " is not a double");
	y.append(atof(data));	
      }
    if (x.size() < 2)
      ZENTHROW(SizeMismatch, "number of rows is less than 2");
    set_vals(move(x), move(y));
  }

  SimpleGrid() {}

  template <class C> void set_vals(const C & x, const C & y) 
  {
    new (this) SimpleGrid(x, y);
  }

  template <class C> void set_vals(C && x, C && y) 
  {
    new (this) SimpleGrid(forward<C>(x), forward<C>(y));
  }

  bool is_empty() const noexcept { return x.is_empty(); }

  double compute_y(const double x) const
  {
    auto pidx = search_inteval(this->x, x);
    if (pidx.first == pidx.second)
      return y(pidx.first);
    
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
      return x(pidx.first);
    
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
