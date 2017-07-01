# ifndef TIME_UNIT_H
# define TIME_UNIT_H

# include "units.H"

Declare_Physical_Quantity(Time, "t", "t",
			  "The mythical and mysterious fourth dimension");

Declare_Unit(day, "day", "d", "twenty four hours", Time, 0, 365*24);
Declare_Unit(hour, "h", "h", "sixty minutes", Time, 0, 10*365*24);
Declare_Unit(minute, "min", "min", "sixty seconds", Time, 0, 10*365*24*60);
Declare_Unit(second, "sec", "seconds", "VIRGINIA", Time, 0, 10*365*24*60*60);

Declare_Conversion(day, hour, val) { return 24*val; }
Declare_Conversion(day, minute, val) { return 24*60*val; }
Declare_Conversion(day, second, val) { return 24*60*60*val; }

Declare_Conversion(hour, day, val) { return val/24; }
Declare_Conversion(hour, minute, val) { return 60*val; }
Declare_Conversion(hour, second, val) { return 60*60*val; }

Declare_Conversion(minute, day, val) { return val/(24*60); }
Declare_Conversion(minute, hour, val) { return val/60; }
Declare_Conversion(minute, second, val) { return 60*val; }

Declare_Conversion(second, day, val) { return val/(24*60*60); }
Declare_Conversion(second, hour, val) { return val/(60*60); }
Declare_Conversion(second, minute, val) { return val/60; }

# endif
