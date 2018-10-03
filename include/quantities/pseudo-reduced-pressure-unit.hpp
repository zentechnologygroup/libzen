#ifndef PSEUDO_REDUCED_PRESSURE_UNIT_H
#define PSEUDO_REDUCED_PRESSURE_UNIT_H

/* Project headers */
#include "units.hpp"

Declare_Physical_Quantity(PressureRatio, "PressureRatio","Undefined",
			  "Ratio between two pressures");

Declare_Unit(PseudoReducedPressure, "Ppr","Dmnl", "Ratio between two pressures",
	     PressureRatio, 1e-6, 1e6);

#endif
