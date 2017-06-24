# ifndef FRICTION_FACTOR_UNIT_H
# define FRICTION_FACTOR_UNIT_H

# include "units.H"

Declare_Physical_Quantity(FrictionFactor, "friction_factor", "frictionfactor",
R"DESC(The Moody friction factor, dimensionless energy loss factor for multiphase flow, is a function of the Reynolds number and the roughness of the internal surface of the pipe. It is denoted as f.)DESC");

Declare_Unit(fFactor, "fFactor","Non-dimensional factor", "Friction factor", FrictionFactor, 0.008, 0.1);

// References:
// http://petrowiki.org/Pressure_drop_evaluation_along_pipelines
// Brown, K. (1977). The Technology of Artificial Lift Methods. ISBN: 0-87814-031-X.

# endif // FRICTION_FACTOR_UNIT_H
