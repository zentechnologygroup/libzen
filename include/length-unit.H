#ifndef LENGTH_UNIT_H
#define LENGTH_UNIT_H

# include "units.H"

Declare_Physical_Quantity(Length, "L", "L", R"DESC(The length is the measurement or extent of something. It may represent reservoir thickness, 				  drainage radius, well radius, etc.)DESC");


Declare_Unit(foot, "ft", "ft", "The length measured in feet", Length, 0, 5000);
Declare_Unit(inch, "in", "in", "The length measured in inches", Length, 0, 60000); 
Declare_Unit(meter, "m", "m", "The length measured in meters", Length, 0, 1524); 
Declare_Unit(yard, "yd", "yd", "The length measured in yards", Length, 0, 1666.66666666667); 

// To foot 
Declare_Conversion(inch, foot, V) { return 8.3333333333333333e-2 * V; }
Declare_Conversion(meter, foot, V) { return 3.28083989501 * V; }
Declare_Conversion(yard, foot, V) { return  3 * V; }

// To inch
Declare_Conversion(foot, inch, V) { return 12 * V; }
Declare_Conversion(meter, inch, V) { return 39.3700787402 * V; }
Declare_Conversion(yard, inch, V) { return  36 * V; }

// To meter
Declare_Conversion(foot, meter, V) { return 0.3048 * V; }
Declare_Conversion(inch, meter, V) { return 0.0254 * V; }
Declare_Conversion(yard, meter, V) { return 0.9144 * V; }

// To yard
Declare_Conversion(foot, yard, V) { return 0.33333333333333337 * V; }
Declare_Conversion(inch, yard, V) { return 0.027777777777777776 * V; }
Declare_Conversion(meter, yard, V) { return 1.0936132983377078 * V; }

#endif // LENGTH_UNIT_H
