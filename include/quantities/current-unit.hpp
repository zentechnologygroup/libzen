#ifndef CURRENT_UNIT_H
#define CURRENT_UNIT_H

/* Project headers */
#include "units.hpp"

Declare_Physical_Quantity(Current, "I", "I", "Flow of electrical charge");

Declare_Unit(Ampere, "amp", "amp", "One coulomb per second", Current, 0, 1000);

#endif
