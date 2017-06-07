# ifndef REYNOLDS_NUMBER_UNIT_H
# define REYNOLDS_NUMBER_UNIT_H

# include "units.H"


Declare_Physical_Quantity(ReynoldsNumber, "Re", "Re", R"DESC(The Reynolds Number, the non-dimensional velocity, can be defined as the ratio of the inertia force, and the viscous or friction force. It is denoted by Re. The Reynolds Number can be used to determine if the flow is laminar (when Re < 2300), transient (when 2300 < Re < 4000) or turbulent (when 4000 < Re).")DESC");

Declare_Unit(ReNumber, "ReNumber", "Re", "Non-dimensional velocity", ReynoldsNumber, 5e2, 1e8);

// References:
// http://www.engineeringtoolbox.com/reynolds-number-d_237.html
// http://www.engineeringtoolbox.com/moody-diagram-d_618.html
// http://auworkshop.autodesk.com/library/fluid-dynamics-lemaster/moody-diagram

# endif // REYNOLDS_NUMBER_UNIT_H
