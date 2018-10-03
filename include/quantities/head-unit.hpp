#ifndef HEAD_UNIT_H
#define HEAD_UNIT_H

/* Project headers */
#include "units.hpp"

Declare_Physical_Quantity(Head, "H", "H",
			  "The static head of a pump is the maximum height" 
			  " (pressure) it can deliver. The capability of the pump"
			  " at a certain RPM can be read from its Q-H curve "
			  "(flow vs. height)");

Declare_Unit(headFeet, "Hft", "Hft",
	     "The static head of a pump measured in feet", Head, 0, 16000); 

Declare_Unit(headInch, "Hin", "Hin",
	     "The static head of a pump measured in inches", Head, 0, 192000); 

Declare_Unit(headMeter, "Hmts", "Hmts",
	     "The static head of a pump measured in meters",
	     Head, 0, 4876.8); 

// To headFoot 
Declare_Conversion(headInch, headFeet, H) { return 8.3333333333333333e-2 * H; }
Declare_Conversion(headMeter, headFeet, H) { return 3.28083989501 * H; }

// To headInch
Declare_Conversion(headMeter, headInch, H) { return 39.3700787402 * H; }
Declare_Conversion(headFeet, headInch, H) { return 12 * H; }

// To headMeter
Declare_Conversion(headFeet, headMeter, H) { return 0.3048 * H; }
Declare_Conversion(headInch, headMeter, H) { return 0.0254 * H; }


#endif // HEAD_UNIT_H

