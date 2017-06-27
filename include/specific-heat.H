# ifndef SPECIFIC_HEAT_H
# define SPECIFIC_HEAT_H

# include "units.H"

Declare_Physical_Quantity(SpecificHeat, "C", "C", "Virginia");

Declare_Unit(Kjoule_Kg_degK, "kilojoule/kilogram/K", "kilojoule/kilogram/K",
	     "Virginia", SpecificHeat, 0.128, 14.3);

Declare_Unit(Btuth_Lb_degF, "Btu (th)/pound/°F", "Btu (th)/pound/degF",
	     "Virginia", SpecificHeat, 0.0305927342208, 3.41778202623);

Declare_Conversion(Kjoule_Kg_degK, Btuth_Lb_degF, v) { return 0.2390057361*v; }
Declare_Conversion(Btuth_Lb_degF, Kjoule_Kg_degK, v) { return 4.184*v; }

# endif
