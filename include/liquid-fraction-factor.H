# ifndef LIQUID_FRACTION_FACTOR_UNIT_H
# define LIQUID_FRACTION_FACTOR_UNIT_H

# include <units.H>

Declare_Physical_Quantity(LiquidFractionFactor, "Fraction", "Fraction", "Fraction of water or oil in the liquid mixture, calculated by the Water-Oil Ratio (WOR).");

Declare_Unit(DmnlFraction, "Dmnl", "Dmnl", "Dimensionless fraction", LiquidFractionFactor, 0, 1);

# endif
