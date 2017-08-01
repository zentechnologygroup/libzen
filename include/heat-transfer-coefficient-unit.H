# ifndef HEAT_TRANSFER_COEFFICIENT_UNIT_H
# define HEAT_TRANSFER_COEFFICIENT_UNIT_H

# include "units.H"

Declare_Physical_Quantity(HeatTransferCoefficient, "U", "U", "Coefficient describing the total resistance to heat loss from a producing pipe to its surroundings.");

Declare_Unit(Btuth_day_ft2_degF, "Btu (th)/d/ft2/degF",
	     "Btu (th)/d/ft^{2}/^{\\circ}F", "Heat transfer coefficient measured as Btu (th) per day per square foot per degrees Fahrenheit", HeatTransferCoefficient,
	     24, 4920);


// Note: The Engineering ToolBox expresses the range as 1 - 205 (Btu/(ft2 * hr * F)).

// References:

// http://petrowiki.org/Glossary:Heat_transfer_coefficient
// http://www.engineeringtoolbox.com/overall-heat-transfer-coefficients-d_284.html

# endif
