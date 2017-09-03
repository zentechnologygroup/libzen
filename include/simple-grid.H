/*

 */
# ifndef SIMPLE_GRID_H
# define SIMPLE_GRID_H

# include <ah-string-utils.H>
# include <parse-csv.H>
# include <ahFunctional.H>
# include <ah-zip.H>
# include <ahSort.H>
# include <tpl_array.H>

# include <zen-exceptions.H>

/* Simple grid

   A simple grid is a matrix nx2 of x and y values characterizing a
   function y = f(x). 

   In order to instantiate a grid you a pair of containers each one
   having the x and y values respectively must be provided.

   Example

       Array<double> x = { 1, 30, 55, 83, 113 };
       Array<double> y = { 1, 345, 230, 83, 113 };
       SimpleGrid grid(x, y); 

   Obviously, the grain of vector values should be enough for
   adequately characterizing the curve.

   Once the grid is instantiated, any values ​​of x or y can be
   calculated through the `()` `compute_y()` or `inverse()` method
   respectively. For example:

       double yval = grid.compute_y(70);

   will compute the value of f(70). If the x values is inside the grid
   range, then the value of y is computed through interpolation
   between the nearest surrounding pair of known points. At the
   contrary, the value is computed by extrapolation between the first
   or last two known points, depending on x is less or greater.

   @ingroup Units
   @author Leandro Rabindranath Leon 
 */
class SimpleGrid
{ //                x,    y
  using P = pair<double, double>;

  size_t n = 0;
  Array<double> x;
  Array<double> y;

  using Pidx = pair<size_t, size_t>;

public:

  mutable double first_x; /// minimum x value 
  mutable double last_x;  /// maximum x value 
  mutable double first_y; /// minimum y value 
  mutable double last_y;  /// maximum y value 

  /// Return `true` if the grid is valid, i.e. it was correctly instantiated
  bool is_valid() const
  {
    return first_x == x.get_first() and last_x == x.get_last() and
      first_y == y.get_first() and last_y == y.get_last() and first_x < last_x;
  }

protected:

  /// Return the pair of nearest surrounding values to x 
  static Pidx search_inteval(const Array<double> & a, const double x)
  {
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

    first_x = x.get_first();
    last_x = x.get_last();
    first_y = y.get_first();
    last_y = y.get_last();
  }

public:

  void swap(SimpleGrid & grid)
  {
    std::swap(n, grid.n);
    std::swap(x, grid.x);
    std::swap(y, grid.y);
    std::swap(first_x, grid.first_x);
    std::swap(last_x, grid.last_x);
    std::swap(first_y, grid.first_y);
    std::swap(last_y, grid.last_y);
  }

  /// Copy constructor
  SimpleGrid(const SimpleGrid & grid)
    : n(grid.n), x(grid.x), y(grid.y)
  {
    init_grid();
    assert(is_valid());
  }

  /// Rvalue copy constructor
  SimpleGrid(SimpleGrid && grid)
    : n(grid.n), x(move(grid.x)), y(move(grid.y))
  {
    init_grid();
    assert(is_valid());
  }

  /// Rvalue assignment
  SimpleGrid & operator = (SimpleGrid && grid)
  {
    swap(grid);
    assert(is_valid());
    return *this;
  }

  /* Create a new grid copying the x and y values

     @param[in] x container having the x values
     @param[in] y container having the y values
     @exception bad_alloc if there is no memory
     @exception SizeMismatch if x and y have different sizes
     @exception InvalidSize if size of x or y are less than 2
     @note In debug mode it is validated that the container x is
     ascendingly sorted
   */
  template <class C>
  SimpleGrid(const C & x, const C & y) : x(x), y(y)
  {
    init_grid();
    assert(is_valid());
  }

  /* Create a new grid directly moving the x and y values

     @param[in] x container having the x values
     @param[in] y container having the y values
     @exception bad_alloc if there is no memory
     @exception SizeMismatch if x and y have different sizes
     @exception InvalidSize if size of x or y are less than 2
     @note In debug mode it is validated that the container x is
     ascendingly sorted
   */
  template <class C>
  SimpleGrid(C && x, C && y) : x(forward<C>(x)), y(forward<C>(y))
  {
    init_grid();
    assert(is_valid());
  }

  /// Instantiate a new grid from a text stream in csv format
  /// separated by ','
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
    init_grid();
    assert(is_valid());
  }

  /// Create an empty, but invalid, grid
  SimpleGrid() {}

  /// Set the x and y values by copy
  template <class C> void set_vals(const C & x, const C & y) 
  {
    new (this) SimpleGrid(x, y);
  }

    /// Set the x and y values by moving
  template <class C> void set_vals(C && x, C && y) 
  {
    new (this) SimpleGrid(forward<C>(x), forward<C>(y));
  }

  /// Return `true` if the grid is empty (and invalid)
  bool is_empty() const noexcept { return x.is_empty(); }

  /* Compute f(x)

     If x is less than `first_x` then y is computed by extrapolation
     with the two first known points.

     If x is greater than `last_x` then y is computed by extrapolation
     with the two last known points.

     Otherwise, y is computed by interpolation between the two nearest
     surrounding points to x
 */
  double compute_y(const double x) const
  {
    if (x < first_x)
      return extrapolate_left(this->x(0), this->x(1), y(0), y(1), x);
    
    if (x > last_x)
      {
	const size_t & n = this->x.size();
	return extrapolate_right(this->x(n-2), this->x(n-1), y(n-2), y(n-1), x);
      }
    
    auto pidx = search_inteval(this->x, x);
    if (pidx.first == pidx.second)
      return y(pidx.first);
    
    const size_t & i1 = pidx.first;
    const size_t & i2 = pidx.second;
    
    return interpolate(this->x(i1), this->x(i2), y(i1), y(i2), x);
  }

  /// @overload compute_y
  double operator () (const double x) const
  {
    return compute_y(x);
  }

  /// Computes f(y)^-1 in the same way than f(x)
  double inverse(const double y) const
  {
    if (y < first_y)
      return extrapolate_left(x(0), x(1), this->y(0), this->y(1), y);
    
    if (y > last_y)
      {
	const size_t & n = this->y.size();
	return extrapolate_right(x(n-2), x(n-1), this->y(n-2), this->y(n-1), y);
      }
        auto pidx = search_inteval(this->y, y);
    if (pidx.first == pidx.second)
      return x(pidx.first);
    
    const size_t & i1 = pidx.first;
    const size_t & i2 = pidx.second;
    
    return interpolate(this->y(i1), this->y(i2), x(i1), x(i2), y);
  }

  /// Return a constant reference to x array
  const Array<double> & get_x() const noexcept { return x; };

  /// Return a constant reference to y array
  const Array<double> & get_y() const noexcept { return y; };
};

# endif
