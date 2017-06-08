#ifndef DIAMETER_UNIT_H
#define DIAMETER_UNIT_H

# include "units.H"

Declare_Physical_Quantity(Diameter, "D", "D", R"DESC(The diameter is the measurement of a straight line passing from side to side through the center of a body or figure, especially a circle. It is used to designate the pipe size. The diameter is denoted as D.)DESC");


Declare_Unit(foot, "ft", "ft", "The diameter measured in feet", Diameter, 8.3333333333333333e-2, 25);
Declare_Unit(inch, "in", "in", "The diameter measured in inches", Diameter, 1, 300); 
Declare_Unit(meter, "m", "m", "The diameter measured in meters", Diameter, 0.0254, 7.62); 
Declare_Unit(centimeter, "cm", "cm", "The diameter measured in centimeters", Diameter, 2.54, 762); 
Declare_Unit(milimeter, "mm", "mm", "The diameter measured in milimeters", Diameter, 25.4, 7620);  

// To foot 
Declare_Conversion(inch, foot, V) { return 8.3333333333333333e-2 * V; }
Declare_Conversion(meter, foot, V) { return 3.28083989501 * V; }
Declare_Conversion(centimeter, foot, V) { return 3.28083989501e-2 * V; }
Declare_Conversion(milimeter, foot, V) { return 3.28083989501e-3 * V; }

// To inch
Declare_Conversion(foot, inch, V) { return 12 * V; }
Declare_Conversion(meter, inch, V) { return 39.3700787402 * V; }
Declare_Conversion(centimeter, inch, V) { return 39.3700787402e-2 * V; }
Declare_Conversion(milimeter, inch, V) { return 39.3700787402e-3 * V; }

// To meter
Declare_Conversion(foot, meter, V) { return 0.3048 * V; }
Declare_Conversion(inch, meter, V) { return 0.0254 * V; }
Declare_Conversion(centimeter, meter, V) { return 1e-2 * V; }
Declare_Conversion(milimeter, meter, V) { return 1e-3 * V; }

// To centimeter
Declare_Conversion(foot, centimeter, V) { return 30.48 * V; }
Declare_Conversion(inch, centimeter, V) { return 2.54 * V; }
Declare_Conversion(meter, centimeter, V) { return 1e2 * V; }
Declare_Conversion(milimeter, centimeter, V) { return 0.1 * V; }

// To milimeter
Declare_Conversion(foot, milimeter, V) { return 304.8 * V; }
Declare_Conversion(inch, milimeter, V) { return 25.4 * V; }
Declare_Conversion(meter, milimeter, V) { return 1e3 * V; }
Declare_Conversion(centimeter, milimeter, V) { return 10 * V; }


// References:
// http://petrowiki.org/Recommended_SI_units_and_conversion_factors#Additional_Conversion_Factors
// http://petrowiki.org/Basic_symbols_in_alphabetical_order
// Brown, K. (1977). The Technology of Artificial Lift Methods. ISBN: 0-87814-031-X.

#endif // DIAMETER_UNIT_H
