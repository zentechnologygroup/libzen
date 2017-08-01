# ifndef GEOTERMAL_GRADIENT_UNIT_H
# define GEOTERMAL_GRADIENT_UNIT_H

# include "units.H"


Declare_Physical_Quantity(GeothermalGradient, "gg", "g_g", "The rate of increase in temperature per unit depth in the Earth.");

Declare_Unit(DegF_Ft, "degF/Ft", "\\degree{F}/ft", "Geothermal gradient measured in Fahrenheit per feet",
		GeothermalGradient, 0.008235, 0.030195);

Declare_Unit(DegC_Km, "degC/Km", "\\degree{C}/km", "Geothermal gradient measured in Celsius per kilometers", 
		GeothermalGradient, 15, 55);

Declare_Conversion(DegC_Km, DegF_Ft, val) { return 0.549e-3 * val; } 
Declare_Conversion(DegF_Ft, DegC_Km, val) { return 1.82e3 * val; }     


// Notes:

// (degC / 100 m) = (degC / 0.1 km) = 0.549 (degF / 100 ft)


// References:

// http://www.glossary.oilfield.slb.com/Terms/g/geothermal_gradient.aspx
// https://pubs.usgs.gov/dds/dds-069/dds-069-d/REPORTS/69_D_CH_27.pdf

# endif
