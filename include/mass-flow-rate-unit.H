# ifndef MASS_FLOW_RATE_UNIT_H
# define MASS_FLOW_RATE_UNIT_H

# include "units.H"

Declare_Physical_Quantity(MassFlowRate, "m-dot", "\\dot{m}", "Mass flow rate is defined as the mass of fluid passing a point in the system per unit of time.");

Declare_Unit(lb_sec, "lb/s", "lb/s", "Mass flow rate measured as pounds per second", MassFlowRate, 0, 40567938.3084);
Declare_Unit(lb_day, "lb/d", "lb/d", "Mass flow rate measured as pounds per day", MassFlowRate, 0, 3.5050699e12);

Declare_Conversion(lb_sec, lb_day, V) { return 86400 * V; }

Declare_Conversion(lb_day, lb_sec, V) { return V / 86400; }


// Notes:

// Maximum Mass Flow Rate = Highest density (pure water) * Maximum Flow Rate
// Highest density        = 1000 kg/m3
// Maximum Flow Rate      = 1589872949.28 m3/d (1e10 BPD)
// Maximum Mass Flow Rate = 1589872949.28e3 kg/d 
//                        = 1589872949.28e3 * 2.20462262184878 lb/d = 3.5050699e12 lb/d 
//                        = 40567938.3084 lb/sec


// References:

// http://www.engineersedge.com/fluid_flow/mass_flow_rate.htm

# endif
