# ifndef GEOTERMAL_GRADIENT_UNIT_H
# define GEOTERMAL_GRADIENT_UNIT_H

# include "units.H"

// TODO: Virginia
Declare_Physical_Quantity(GeothermalGradient, "gg", "Undefined", "Virginia");

Declare_Unit(DegF_Ft, "degF/Ft", "Ft/degF", "Virginia",
	     GeothermalGradient, 0.8235, 3.0195);

Declare_Unit(DegC_Km, "degC/Km", "degC/Km", "Virginia", GeothermalGradient, 15, 55);

Declare_Conversion(DegC_Km, DegF_Ft, val) { return 0.549*val/10; }
Declare_Conversion(DegF_Ft, DegC_Km, val) { return 18.2*val; }

# endif
