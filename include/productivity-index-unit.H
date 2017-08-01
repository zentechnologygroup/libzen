#ifndef PRODUCTIVITY_INDEX_UNIT_H
#define PRODUCTIVITY_INDEX_UNIT_H

# include "units.H"

Declare_Physical_Quantity(ProductivityIndex, "J","J", R"DESC(The Productivity Index is defined as the flow rate per unit pressure drop and serves as an indication of the production potential of a well. The symbol J is commonly used to express the productivity index. The units typically are in field units (STB/D/psi).)DESC");


Declare_Unit(BPD_psi, "bpd/psi","RB/(psi \\\\cdot d)", "Volume rate (in barrels per day) per pressure (in psi)", ProductivityIndex, 0, 10);
Declare_Unit(CMD_kPascal, "cmd/kPa","m^{3}/(kPa \\\\cdot d)", "Volume rate (in cubic meter per day) per pressure (in kPa)", ProductivityIndex, 0, 0.23059157584202686);
Declare_Unit(CMS_Pascal, "cms/Pa","m^{3}/(Pa \\\\cdot s)", "Volume rate (in cubic meter per second) per pressure (in Pa)", ProductivityIndex, 0, 2.668883979653089e-9);
Declare_Unit(GPM_psi, "gpm/psi","gal/(psi \\\\cdot min)", "Volume rate (U.S. Gallons per minute) per pressure (in psi)", ProductivityIndex, 0, 0.2916666666666667);

// To BPD_psi 
Declare_Conversion(CMD_kPascal, BPD_psi, V) { return V / 2.3059157584202686e-2; }
Declare_Conversion(CMS_Pascal, BPD_psi, V) { return 3746884494.132201 * V; }
Declare_Conversion(GPM_psi, BPD_psi, V) { return 34.28571428571428 * V; }

// To CMD_kPascal
Declare_Conversion(BPD_psi, CMD_kPascal, V) { return 2.3059157584202686e-2 * V; }
Declare_Conversion(CMS_Pascal, CMD_kPascal, V) { return 86400000 * V; }
Declare_Conversion(GPM_psi, CMD_kPascal, V) { return  5.4509929689600005 * V / 6.89475729316836; }

// To CMS_Pascal 
Declare_Conversion(BPD_psi, CMS_Pascal, V) { return 2.668883979653089e-10 * V; }
Declare_Conversion(CMD_kPascal, CMS_Pascal, V) { return 1.1574074074074074e-8 * V; }
Declare_Conversion(GPM_psi, CMS_Pascal, V) { return  0.0000630901964 * V / 6894.75729316836; }

// To GPM_psi
Declare_Conversion(BPD_psi, GPM_psi, V) { return V / 34.28571428571428; }
Declare_Conversion(CMD_kPascal, GPM_psi, V) { return 6.89475729316836 * V / 5.4509929689600005; }
Declare_Conversion(CMS_Pascal, GPM_psi, V) { return 6894.75729316836 * V / 0.0000630901964; }


// References:
// http://fekete.com/SAN/TheoryAndEquations/WellTestTheoryEquations/Productivity_Index.htm
// http://petrowiki.org/Productivity_index_(J)
// http://petrowiki.org/Recommended_SI_units_and_conversion_factors#Flow_rate
// http://www.unitconverterapp.com/quantity/%28volume%20per%20time%29%20per%20pressure

#endif // PRODUCTIVITY_INDEX_UNIT_H
