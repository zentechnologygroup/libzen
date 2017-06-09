#ifndef ABSOLUTE_ROUGHNESS_UNIT_H
#define ABSOLUTE_ROUGHNESS_UNIT_H

# include "units.H"

Declare_Physical_Quantity(AbsoluteRoughness, "e", "\\epsilon", R"DESC(The absolute roughness is a measure of the wall irregularities inside of a flowing pipe. It is normally specified in either mm or inches and common values range from 0.0015 mm for PVC pipes through to 3 mm for rough concrete pipes. The absolute roughness is denoted as e or ϵ (Greek symbol epsilon).)DESC");


Declare_Unit(Foot_AR, "ft_ar", "ft_ar",
	     "The absolute roughness measured in feet",
	     AbsoluteRoughness, 4.92125984251968e-6, 0.00416666666666667);
Declare_Unit(Inch_AR, "in_ar", "in_ar",
	     "The absolute roughness measured in inches", AbsoluteRoughness,
	     5.90551181102362e-5, 0.05);  
Declare_Unit(Milimeter_AR, "mm_ar", "mm_ar",
	     "The absolute roughness measured in millimeters",
	     AbsoluteRoughness, 0.0015, 1.27);  

// To foot 
Declare_Conversion(Inch_AR, Foot_AR, v) { return 8.3333333333333333e-2 * v; }
Declare_Conversion(Milimeter_AR, Foot_AR, v) { return 3.28083989501e-3 * v; }

// To inch
Declare_Conversion(Foot_AR, Inch_AR, v) { return 12 * v; }
Declare_Conversion(Milimeter_AR, Inch_AR, v) { return 39.3700787402e-3 * v; }

// To milimeter
Declare_Conversion(Foot_AR, Milimeter_AR, v) { return 304.8 * v; }
Declare_Conversion(Inch_AR, Milimeter_AR, v) { return 25.4 * v; }


/* Note: Brown (1977) presents a graph were the minimum value of pipe diameter is 1 in, and the maximum value of relative roughness is 0.05. Therefore, the maximum value of absolute roughness is set as 0.05 in (1.27 mm). */

// References:
// http://www.pipeflow.com/pipe-pressure-drop-calculations/pipe-roughness
// http://www.piping-designer.com/index.php/properties/106-absolute-roughness
// Beggs, H. (1991). Production Optimization: Using NODAL Analysis. ISBN: 0-930972-14-7.
// Brown, K. (1977). The Technology of Artificial Lift Methods. ISBN: 0-87814-031-X.

#endif // ABSOLUTE_ROUGHNESS_UNIT_H
