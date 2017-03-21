# ifndef LIQUID_SPECIFIC_GRAVITY_UNIT_H
# define LIQUID_SPECIFIC_GRAVITY_UNIT_H

# include "units.H"

Declare_Physical_Quantity(LiquidGravity, "G", "G", "G");

Declare_Unit(SpecificGravity, "g", "g",
	     "Liquid specific gravity", LiquidGravity, 0, 1000);

#endif
