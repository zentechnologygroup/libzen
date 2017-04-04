# ifndef S_UNIT_H
# define S_UNIT_H

# include "units.H"

Declare_Physical_Quantity(SkinFactor, "S", "S", R"DESC(The Skin Factor (S) is a numerical value used to analytically model the difference from 				  the pressure drop predicted by Darcy's law due to skin. Typical values for the skin factor range from -6 for an 				  infinite-conductivity massive hydraulic fracture to more than 100 for a poorly executed gravel pack.)DESC");

Declare_Unit(Sfactor, "sFactor","Dmnl", "Skin factor", SkinFactor, -7, 230);

/* Note: The total skin can be as high as 100 or even more in a poorly completed well. Skin factor due to damage can be as low as -7 and as high as 200. Skin factor due to partial penetration typically ranges from 0 to 30. 
*/

// References:
// http://www.glossary.oilfield.slb.com/Terms/s/skin_factor.aspx
// http://www.fekete.com/san/webhelp/welltest/webhelp/Content/HTML_Files/Reference_Materials/Skin.htm
// Schlumberger - Well Performance Manual.

# endif // S_UNIT_H
