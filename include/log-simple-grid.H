# ifndef LOG_SIMPLE_GRID_H
# define LOG_SIMPLE_GRID_H

# include "simple-grid.H"

struct LogXYGrid : private SimpleGrid
{
  template <class C>
  LogXYGrid(C && logx, C && y) : SimpleGrid(move(logx), move(y)) {}
  
  template <class C>
  LogXYGrid(const C & logx, const C & y) : SimpleGrid(logx, y) {}

  double operator () (const double x) const
  {
    const double logx = log10(x);
    return compute_y(logx);
  }

  const Array<double> & get_logx() const noexcept { return get_x(); }

  const Array<double> & get_y() const noexcept
  {
    return SimpleGrid::get_y();
  }

  double first_logx() const noexcept { return SimpleGrid::first_x(); }

  double first_x() const noexcept { return exp10(first_logx()); }

  double last_logx() const noexcept { return SimpleGrid::last_x(); }

  double last_x() const noexcept { return exp10(last_logx()); }

  double first_y() const noexcept { return SimpleGrid::first_y(); }

  double last_y() const noexcept { return SimpleGrid::last_y(); }
};

struct LogXLogYGrid : private SimpleGrid
{
  template <class C>
  LogXLogYGrid(C && logx, C && logy) : SimpleGrid(move(logx), move(logy)) {}
  
  template <class C>
  LogXLogYGrid(const C & logx, const C & logy) : SimpleGrid(logx, logy) {}

  double operator () (const double x) const
  {
    const double logx = log10(x);
    return exp10(compute_y(logx));
  }

  const Array<double> & get_logx() const noexcept { return get_x(); }

  const Array<double> & get_logy() const noexcept { return get_y(); }

  double first_logx() const noexcept { return SimpleGrid::first_x(); }

  double first_x() const noexcept { return exp10(first_logx()); }

  double last_logx() const noexcept { return SimpleGrid::last_x(); }

  double last_x() const noexcept { return exp10(last_logx()); }

  double first_logy() const noexcept { return SimpleGrid::first_y(); }

  double first_y() const noexcept { return exp10(first_logy()); }

  double last_logy() const noexcept { return SimpleGrid::last_y(); }

  double last_y() const noexcept { return exp10(last_logy()); }
};


# endif
