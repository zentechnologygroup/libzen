# ifndef TRANSIENT_HEAT_CONDUCTION_UNIT_H
# define TRANSIENT_HEAT_CONDUCTION_UNIT_H

# include "units.H"

Declare_Physical_Quantity(TransientHeatConduction, "Heat conduction f(t)", "Heat conduction f(t)", "A quantitative description of heat transfer to or from the wellbore, when there is a difference in temperature between the surrounding formation and the injected (or produced) fluid. Transient conduction occurs when the temperature changes as a function of time.");

Declare_Unit(DmnlHeatConduction, "DmnlHeatConduction", "Dmnl", "Dimensionless transient time heat conduction", TransientHeatConduction, 0.01, 100);


// References:

// Wu, Y.-S., & Pruess, K. (1990, November 1). An Analytical Solution for Wellbore Heat Transmission in Layered Formations. Society of Petroleum Engineers. doi:10.2118/17497-PA

# endif
