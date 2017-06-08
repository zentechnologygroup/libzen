# ifndef DISTANCE_UNIT_H
# define DISTANCE_UNIT_H

# include "units.H"

Declare_Physical_Quantity(Distance, "D", "D",
			  "numerical description of how far apart objects are");

Declare_Unit(Feet, "ft", "ft", "0.3048 meters", Distance, 0, 160000); 

Declare_Unit(Inch, "in", "in",
	     "Distance unit in British and US", Distance, 0, 1920000); 

Declare_Unit(Meter, "mts", "mts", "Base unit of distance of SI",
	     Distance, 0, 48768); 

// To Foot 
Declare_Conversion(Inch, Feet, l) { return 8.3333333333333333e-2 * l; }
Declare_Conversion(Meter, Feet, l) { return 3.28083989501 * l; }

// To Inch
Declare_Conversion(Meter, Inch, l) { return 39.3700787402 * l; }
Declare_Conversion(Feet, Inch, l) { return 12 * l; }

// To Meter
Declare_Conversion(Feet, Meter, l) { return 0.3048 * l; }
Declare_Conversion(Inch, Meter, l) { return 0.0254 * l; }


#endif // DISTANCE_UNIT_H

