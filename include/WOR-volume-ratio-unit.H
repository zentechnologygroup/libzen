# ifndef WOR_GLR_VOLUME_RATIO_UNIT_H
# define WOR_GLR_VOLUME_RATIO_UNIT_H

# include "units.H"

Declare_Physical_Quantity(WORVolumeRatio, "WOR_V_V","Undefined", "TODO");
    
Declare_Unit(STBPD_STBPD, "STBPD_STBPD","STBPD/STBPD", "TODO",
	     WORVolumeRatio, 0, 1000000000);

# endif //  WOR_GLR_VOLUME_RATIO_UNIT_H
