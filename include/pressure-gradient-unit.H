# ifndef PRESSURE_GRADIENT_UNIT_H
# define PRESSURE_GRADIENT_UNIT_H

# include "units.H"


Declare_Physical_Quantity(PressureGradient, "p Gradient", "\\nabla P", 
                          R"DESC(The change in pressure per unit of depth, 
                          typically in units of psi/ft or kPa/m.)DESC");


Declare_Unit(psi_ft, "psi/ft", "psi/ft", "Pressure gradient measured in psi per foot", PressureGradient, 0.01, 2);
Declare_Unit(kPa_m, "kPa/m", "kPa/m", "Pressure gradient measured in kPascal per meter", PressureGradient, 0.22620594793, 2*22.6205947939);

Declare_Conversion(psi_ft, kPa_m, val) { return 6.89475729316836*val/0.3048; }
Declare_Conversion(kPa_m, psi_ft, val) { return 0.3048*val/6.89475729316836; }


// References:

// http://www.glossary.oilfield.slb.com/Terms/p/pressure_gradient.aspx

# endif
