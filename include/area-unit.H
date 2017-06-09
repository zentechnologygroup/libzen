# ifndef AREA_UNIT_H
# define AREA_UNIT_H

# include <units.H>

Declare_Physical_Quantity(Area, "A", "A",
			  "extent of a two-dimensional figure or shape")

Declare_Unit(Feet2, "ft2", "ft2", "feet square", Area, 0, 1e7);

Declare_Unit(Inch2, "in2", "in2", "inch square", Area, 0, 12*1e7);

Declare_Conversion(Feet2, Inch2, a) { return a/12; }
Declare_Conversion(Inch2, Feet2, a) { return 12*a; }


# endif
