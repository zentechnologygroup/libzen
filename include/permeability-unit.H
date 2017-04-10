#ifndef PERMEABILITY_UNIT_H
#define PERMEABILITY_UNIT_H

# include "units.H"

Declare_Physical_Quantity(Permeability, "k","k", R"DESC(The permeability is the capability of a rock to allow passage of fluids through it. The term was basically defined by Henry Darcy, who showed that the common mathematics of heat transfer could be modified to adequately describe fluid flow in porous media. The symbol k is commonly used to express the permeability. It is typically measured in darcies or millidarcies.)DESC");


Declare_Unit(mDarcy, "mD","mD", "Unit of permeability miliDarcy.", Permeability, 0, 2000);
Declare_Unit(Darcy, "D","D", "Unit of permeability Darcy.", Permeability, 0, 2);
Declare_Unit(DarcyAPI, "D-API","D-API", "Unit of permeability Darcy-API.", Permeability, 0, 1.973846533432026);
Declare_Unit(TDarcyAPI, "TD-API","TD-API", "Unit of permeability TeraDarcy-API.", Permeability, 0, 1.973846533432026e-12);


// To mDarcy
Declare_Conversion(Darcy, mDarcy, V) { return 1000 * V; }
Declare_Conversion(DarcyAPI, mDarcy, V) { return 1013.2499999999999 * V; }
Declare_Conversion(TDarcyAPI, mDarcy, V) { return 1013249999999999.9 * V; }

// To Darcy
Declare_Conversion(mDarcy, Darcy, V) { return V / 1000; }
Declare_Conversion(DarcyAPI, Darcy, V) { return 1.01325 * V; }
Declare_Conversion(TDarcyAPI, Darcy, V) { return  1013250000000 * V; }

// To DarcyAPI
Declare_Conversion(mDarcy, DarcyAPI, V) { return 0.000986923266716013 * V; }
Declare_Conversion(Darcy, DarcyAPI, V) { return 0.9869232667160128 * V; }
Declare_Conversion(TDarcyAPI, DarcyAPI, V) { return  1000000000000 * V; }

// To TDarcyAPI
Declare_Conversion(mDarcy, TDarcyAPI, V) { return 9.86923266716013e-16 * V; }
Declare_Conversion(Darcy, TDarcyAPI, V) { return 9.869232667160128e-13 * V; }
Declare_Conversion(DarcyAPI, TDarcyAPI, V) { return 1e-12 * V; }


// References:
// http://www.glossary.oilfield.slb.com/Terms/p/permeability.aspx
// http://www.unitconverterapp.com/quantity/permeability%20rock
// http://petrowiki.org/Rock_type_influence_on_permeability


#endif // PERMEABILITY_UNIT_H
