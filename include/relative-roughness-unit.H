#ifndef RELATIVE_ROUGHNESS_UNIT_H
#define RELATIVE_ROUGHNESS_UNIT_H

# include "units.H"

Declare_Physical_Quantity(RelativeRoughness, "k", "k", R"DESC(The relative roughness is a dimensionless number, expressed as the pipe's absolute roughness divided by its internal diameter or e/D. It is denoted as k.)DESC");

Declare_Unit(relativeRoughness, "relativeRoughness","Non-dimensional roughness", "Relative Roughness", RelativeRoughness, 1e-6, 0.05);


// References:

// http://www.pipeflow.com/pipe-pressure-drop-calculations/pipe-roughness
// http://piping-designer.com/index.php/properties/dimensionless-numbers/170-relative-roughness?title=Relative_Roughness
// Brown, K. (1977). The Technology of Artificial Lift Methods. ISBN: 0-87814-031-X.

#endif // RELATIVE_ROUGHNESS_UNIT_H
