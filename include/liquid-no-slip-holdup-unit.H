# ifndef LIQUID_NO_SLIP_HOLDUP_UNIT_H
# define LIQUID_NO_SLIP_HOLDUP_UNIT_H

# include "units.H"


Declare_Physical_Quantity(LiquidNoSlipHoldup, "LambdaL", "\\lambda_L",
			  R"DESC(The liquid holdup is defined as the fraction of liquid present in an interval of pipe.
              In the case of no-slip holdup, the "slip" effect is neglected (gas and liquid travel at the           
              same velocity), so the in-situ liquid fraction is equal to the input liquid fraction.)DESC");

Declare_Unit(NoSlipHoldup, "No-Slip Holdup", "Dmnl", "Liquid holdup without considering slip effect",
	     LiquidNoSlipHoldUp, 0, 1);


// References:

// http://www.fekete.com/SAN/TheoryAndEquations/HarmonyTheoryEquations/Content/HTML_Files/Reference_Material/Calculations_and_Correlations/Pressure_Loss_Calculations.htm

// http://www.glossary.oilfield.slb.com/Terms/h/holdup.aspx

# endif // LIQUID_NO_SLIP_HOLDUP_UNIT_H
