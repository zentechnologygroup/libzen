# ifndef THERMAL_CONDUCTIVITY_UNIT_H
# define THERMAL_CONDUCTIVITY_UNIT_H

# include "units.H"

Declare_Physical_Quantity(ThermalConductivity, "K", "K", "Virginia");

Declare_Unit(Watt_Mt_K, "watt/mt/K", "watt/mt/K", "Virginia",
	     ThermalConductivity, 0.0033, 1000)
Declare_Unit(Btuth_h_ft_degF, "Btu (th)/hour/foot/degF",
	     "Btu (th)/hour/foot/degF", "Virginia", ThermalConductivity,
	     0.001907980742118, 578.17598246);
Declare_Unit(Btuth_day_ft_degF, "Btu (th)/day/foot/degF",
	     "Btu (th)/day/foot/degF", "Virginia", ThermalConductivity,
	     0.045791537810832, 13876.22357904);

Declare_Conversion(Watt_Mt_K, Btuth_h_ft_degF, v) { return 0.57817598246*v; }
Declare_Conversion(Watt_Mt_K, Btuth_day_ft_degF, v) { return 13.876223579*v; }

Declare_Conversion(Btuth_h_ft_degF, Watt_Mt_K, v) { return 1.7307346664*v; }
Declare_Conversion(Btuth_h_ft_degF, Btuth_day_ft_degF, v) { return v/24; }

Declare_Conversion(Btuth_day_ft_degF, Btuth_h_ft_degF, v) { return 24*v; }
Declare_Conversion(Btuth_day_ft_degF, Watt_Mt_K, v) { return 24*1.7307346664*v; }

# endif
