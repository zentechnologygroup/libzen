# ifndef KINETIC_COMPONENT_UNIT_H
# define KINETIC_COMPONENT_UNIT_H

# include <units.H>

Declare_Physical_Quantity(KineticComponent, "Ek", "E_k", "Acceleration or kinetic component of the pressure gradient equation.");

Declare_Unit(DmnlKineticComponent, "Dmnl_kc", "Dmnl",
	     "Dimensionless kinetic component", KineticComponent, 0, 0.9);

# endif
