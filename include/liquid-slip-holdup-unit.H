# ifndef LIQUID_SLIP_HOLDUP_UNIT_H
# define LIQUID_SLIP_HOLDUP_UNIT_H

# include "units.H"


Declare_Physical_Quantity(LiquidSlipHoldup, "HL", "H_L",
			  R"DESC(The liquid holdup is defined as the fraction of liquid present in an interval of pipe. 
              When two or more phases are present in a pipe, they tend to flow at different in-situ velocities. 
              Typically the phase that is less dense flows faster than the other. This causes a "slip" effect 
              between the phases.)DESC");

Declare_Unit(SlipHoldup, "Slip Holdup", "Dmnl", "Liquid holdup considering slip effect",
	     LiquidSlipHoldUp, 0, 1);


// References:

// http://www.fekete.com/SAN/TheoryAndEquations/HarmonyTheoryEquations/Content/HTML_Files/Reference_Material/Calculations_and_Correlations/Pressure_Loss_Calculations.htm

// http://www.glossary.oilfield.slb.com/Terms/h/holdup.aspx

# endif // LIQUID_SLIP_HOLDUP_UNIT_H
