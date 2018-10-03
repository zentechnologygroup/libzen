#ifndef KINEMATIC_VISCOSITY_UNIT_H
#define KINEMATIC_VISCOSITY_UNIT_H

/* Project headers */
#include "units.hpp"

Declare_Physical_Quantity(KinematicViscosity, "V", "\\nu",
			  "Dynamic viscosity divided between its density");

Declare_Unit(CentiStoke, "cSt", "cSt",
	     "Kinematic viscosity measured is centi stokes",
	     KinematicViscosity, 0, 1319.98);

Declare_Unit(SayboltUniversalViscosisty, "SSU", "SSU", 
	     "Kinematic viscosity measured in SSU",
	     KinematicViscosity, 0, 6000)

Declare_Conversion(CentiStoke, SayboltUniversalViscosisty, v)
{
  return 2.273*(v + sqrt(v*v + 158.4));
}

// taken from http://www.eng-tips.com/viewthread.cfm?qid=143939
Declare_Conversion(SayboltUniversalViscosisty, CentiStoke, s)
{
  if (s < 100)
    return 0.266*s - 195.0/s;

  return 0.22*s - 135.0/s;
}

#endif
