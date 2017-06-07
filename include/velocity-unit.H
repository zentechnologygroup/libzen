# ifndef VELOCITY_UNIT_H
# define VELOCITY_UNIT_H

# include "units.H"

Declare_Physical_Quantity(Velocity, "V", "V", "Rate of change of position");

Declare_Unit(Ft_S, "ft/s", "ft/s", "feet for second", Velocity, V0, 1e6);

# endif
