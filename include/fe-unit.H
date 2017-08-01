# ifndef FLOW_EFFICIENCY_UNIT_H
# define FLOW_EFFICIENCY_UNIT_H

# include "units.H"

Declare_Physical_Quantity(FlowEfficiency, "FE", "FE", R"DESC(Flow Efficiency (FE) is the value that results when the actual productivity index (including skin) is divided by the ideal productivity index if the skin factor were zero. It is greater than 1 in a stimulated well (skin < 0) and less than 1 for a damaged completion (skin > 0).)DESC");

Declare_Unit(FlowEff, "FlowEff", "Dmnl", "Flow efficiency", FlowEfficiency, 0.1, 10);

/* Note: Schlumberger (in the Well Performance Manual) presents a graph in which the flow efficiency oscillates between 0.5 and 1.5, nevertheless, a wider range was established for the unit (from 0.1 to 10) considering examples found in other references and the ranges set for the productivity index and the skin factor. 
*/

// References:
// http://www.glossary.oilfield.slb.com/Terms/f/flow_efficiency.aspx
// http://petrowiki.org/Fluid_flow_with_formation_damage
// Schlumberger - Well Performance Manual.

# endif // FLOW_EFFICIENCY_UNIT_H
