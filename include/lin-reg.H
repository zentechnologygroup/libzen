# ifndef LIN_REG_H
# define LIN_REG_H

# include <zen-exceptions.H>
# include <array-ops.H>

class LinearRegression
{
  Array<double> x;
  Array<double> y;

  pair<double, double> theta;

  static double h(double x, const pair<double, double> & theta)
  {
    return theta.first + theta.second*x;
  }

  static Array<double> compute_predictions(const Array<double> & x,
					   const pair<double, double> & theta)
  {
    const size_t & m = x.size();
    Array<double> predictions;
    predictions.reserve(m);
    predictions.putn(m);

    for (size_t i = 0; i < m; ++i) // calculate h for each training sample
      predictions(i) = h(x(i), theta);

    return predictions;
  }

  static double cost(const Array<double> & x, const Array<double> & y,
		     const pair<double, double> & theta)
  {
    Array<double> predictions = compute_predictions(x, theta);
    Array<double> diff = array_diff(predictions, y);
    Array<double> sq_errors = array_pow(diff, 2);
    return (1.0 / (2 * x.size())) * array_sum(sq_errors);
  }

  static pair<double, double>
  gradient_descent(const Array<double> & x, const Array<double> & y,
		   double alpha, int iters, const Array<double> & J)
  {
    pair<double, double> theta(1, 1);
    double & theta0 = theta.first;
    double & theta1 = theta.second;

    const size_t & m = x.size();

    for (int i = 0; i < iters; ++i)
      {
        Array<double> preds = compute_predictions(x, theta);
        Array<double> diff = array_diff(preds, y);

	Array<double> errors_x1 = diff;
	Array<double> errors_x2 = array_mult(diff, x);

        theta0 = theta0 - alpha * (1.0 / m) * array_sum(errors_x1);
        theta1 = theta1 - alpha * (1.0 / m) * array_sum(errors_x2);

        J[i] = cost(x, y, theta);
    }

    return theta;
}

public:

  template <template <typename> class C>
  LinearRegression(const C<double> & x, const C<double> & y)
  {
    this->x = x;
    this->y = y;

    if (this->x.size() != this->y.size())
      ZENTHROW(SizeMismatch, "x size = " + to_string(this->x.size()) +
	       " != y size = " + to_string(this->y.size()));
  }

  void train(double alpha, size_t num_iters)
  {
    Array<double> J;
    J.reserve(num_iters);
    J.putn(num_iters);
    theta = gradient_descent(x, y, alpha, num_iters, J);
  }

  double predict(double x) const { return h(x, theta); }  
};



# endif
