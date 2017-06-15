# include <simple-grid.H>

DynList<double> x = { 0, 1, 2, 3, 4, 5 };
DynList<double> y = { 0, 1, 2, 3, 4, 5 };

int main()
{
  SimpleGrid grid(x, y);

  for (double x = 0; x < 5; x += 0.5)
    cout << "x = " << x << " y = " << grid(x) << endl;
}
