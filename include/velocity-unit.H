# ifndef VELOCITY_UNIT_H
# define VELOCITY_UNIT_H

# include "units.H"

Declare_Physical_Quantity(Velocity, "V", "V", "Rate of change of position");

Declare_Unit(Ft_S, "ft/s", "ft/s", "feet for second", Velocity, 0, 1e6);

Declare_Unit(Meter_S, "m/s", "m/s", "meter for second", Velocity, 0, 304800);

// To Ft_S
Declare_Conversion(Meter_S, Ft_S, V) { return 3.28083989501312 * V; }

// To Meter_S
Declare_Conversion(Ft_S, Meter_S, V) { return 0.3048 * V; }


# endif
