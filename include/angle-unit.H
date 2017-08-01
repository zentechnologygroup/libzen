# ifndef ANGLE_UNIT_H
# define ANGLE_UNIT_H

# include <cmath>
# include "units.H"

Declare_Physical_Quantity(Angle, "angle", "\\angle",
			  "figure formed by two rays sharing a common endpoint");

Declare_Unit(Degree, "deg", "\\degree", "Angle measured in Degrees", Angle, -90, 90);
Declare_Unit(Radian, "rad", "rad", "Angle measured in Radians", Angle, -1.5707963267948966, 1.5707963267948966);

Declare_Conversion(Degree, Radian, val) { return val*M_PI/180; }
Declare_Conversion(Radian, Degree, val) { return val*180/M_PI; }

# endif
