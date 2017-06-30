#ifndef FLOWRATE_UNIT_H
#define FLOWRATE_UNIT_H

# include "units.H"

Declare_Physical_Quantity(FlowRate, "Q", "Q",
			  "Volume rate of some fluid flow that is transported "
			  "through a given cross-sectional area");

Declare_Unit(BPD, "bpd", "bpd",
	     "Volume rate measured in barrels per day", FlowRate, 0, 1e10);

Declare_Unit(GPM, "gpm", "gpm",
	     "Volume rate measured in U.S. Gallon Per Minute",
	     FlowRate, 0, 1e10);

Declare_Unit(CMD, "cmd", "cmd",
	     "Volume rate measured in cubic meter per day", FlowRate, 0, 1e10);

Declare_Unit(CMS, "cms", "cms",
	     "Volume rate measured in cubic meter per second",
	     FlowRate, 0, 1e10);

Declare_Unit(MFTD, "mftd", "mftd", "Volume rate measured in cubic meter per day",
	     FlowRate, 0, 1e100)

Declare_Conversion(MFTD, CMD, val) { return 28316.847*val; }
Declare_Conversion(CMD, MFTD, val) { return 0.000035314666213*val; }

// to BPD 
Declare_Conversion(GPM, BPD, V) { return 34.2857142857 * V; }
Declare_Conversion(CMD, BPD, V) { return 6.28981077043 * V; }
Declare_Conversion(CMS, BPD, V) { return 543439.650565* V; }

// to GPM 
Declare_Conversion(BPD, GPM, V) { return 2.91666666667e-2 * V; }
Declare_Conversion(CMD, GPM, V) { return 0.183452814138 * V; }
Declare_Conversion(CMS, GPM, V) { return 15850.3231415 * V; }

// to CMD
Declare_Conversion(BPD, CMD, V) { return 0.158987294928 * V; }
Declare_Conversion(GPM, CMD, V) { return 5.45099296896 * V; }
Declare_Conversion(CMS, CMD, V) { return 86400 * V; }

// to CMS 
Declare_Conversion(BPD, CMS, V) { return 1.84013072833e-6 * V; }
Declare_Conversion(CMD, CMS, V) { return 1.15740740741e-5  * V; }
Declare_Conversion(GPM, CMS, V) { return 0.0000630901964 * V; }

Declare_Conversion(MFTD, BPD, v)
{
  return unit_convert<CMD, BPD>(unit_convert<MFTD, CMD>(v));
}

Declare_Conversion(BPD, MFTD, v)
{
  return unit_convert<CMD, MFTD>(unit_convert<BPD, CMD>(v));
}

Declare_Conversion(MFTD, GPM, v)
{
  return unit_convert<CMD, GPM>(unit_convert<MFTD, CMD>(v));
}

Declare_Conversion(GPM, MFTD, v)
{
  return unit_convert<CMD, MFTD>(unit_convert<GPM, CMD>(v));
}

Declare_Conversion(MFTD, CMS, v)
{
  return unit_convert<CMD, CMS>(unit_convert<MFTD, CMD>(v));
}

Declare_Conversion(CMS, MFTD, v)
{
  return unit_convert<CMD, MFTD>(unit_convert<CMS, CMD>(v));
}


#endif
