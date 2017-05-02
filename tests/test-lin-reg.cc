
# include <tpl_array.H>

# include <lin-reg.H>

Array<double> x = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

Array<double> y = { 1.1, 2.2, 2.9, 4.05, 4.4, 5, 6.5, 7.9, 9.1, 10.5 };

int main()
{
  LinearRegression lm(x, y);
  lm.train(.01, 20);
  x.for_each([&lm] (auto x)
	     { cout << "x(" << x << ") = " << lm.predict(x) << endl; });
  cout << "x(0) = " << lm.predict(0) << endl
       << "x(11) = " << lm.predict(11) << endl;
}
