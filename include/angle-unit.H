# ifndef ANGLE_UNIT_H
# define ANGLE_UNIT_H

# include <cmath>
# include "units.H"

Declare_Physical_Quantity(Angle, "angle", "\\angle",
			  "figure formed by two rays sharing a common endpoint");

Declare_Unit(Degree, "deg", "deg", "Virginia", Angle, 0, 180);
Declare_Unit(Radian, "rad", "ad", "Virginia", Angle, 0, M_PI);

Declare_Conversion(Degree, Radian, val) { return 180*val/M_PI; }
Declare_Conversion(Radian, Degree, val) { return val*M_PI/180; }

# endif
