#ifndef GAS_FLOW_RATE_UNIT_H
#define GAS_FLOW_RATE_UNIT_H

# include "units.H"

Declare_Physical_Quantity(GasFlowRate, "Qg", "Q_g",
			  "Volume rate of gas that is transported "
			  "through a given cross-sectional area");


Declare_Unit(SCFD, "scf/d", "scf/d", "Gas flow rate measured in standard cubic feet per day",
	     GasFlowRate, 0, 56145833333.3334)

Declare_Unit(MMSCFD, "MMscf/d", "MMscf/d", "Gas flow rate measured in million standard cubic feet per day",
	     GasFlowRate, 0, 56145.8333333333)



Declare_Conversion(SCFD, MMSCFD, V) { return 1e-6 * V; }

Declare_Conversion(MMSCFD, SCFD, V) { return 1e6 * V; }

// Note: The maximum values were assigned as the equivalents to 1e10 BPD.

#endif
