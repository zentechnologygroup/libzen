# ifndef DUMMY_UNIT_H
# define DUMMY_UNIT_H

# include "units.H"

Declare_Physical_Quantity(DummyUnit, "Dummy", "Dummy", "Only for testing");

Declare_Unit(TestUnit, "TU", "TU", "Only for testing", DummyUnit,
	     numeric_limits<double>::min(), numeric_limits<double>::::max());

# endif
