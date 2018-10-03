#ifndef LIQUID_SPECIFIC_GRAVITY_UNIT_H
#define LIQUID_SPECIFIC_GRAVITY_UNIT_H

/* Project headers */
#include "units.hpp"

Declare_Physical_Quantity(LiquidGravity, "G", "G", "G");

Declare_Unit(SpecificGravity, "g", "g",
	     "Liquid specific gravity", LiquidGravity, 0, 1000);

#endif