//#include <mutex>

#include "unitslist.hpp"

// the following data is declared in units.H
UnitItemTable PhysicalQuantity::tbl;

UnitItemTable Unit::tbl;

std::set<const Unit *> Unit::unit_tbl;

UnitHashTable __unit_name_name_tbl;
UnitHashTable __unit_name_symbol_tbl;
UnitHashTable __unit_symbol_name_tbl;
UnitHashTable __unit_symbol_symbol_tbl;

UnitMap __unit_map;

CompoundUnitTbl __compound_unit_tbl;

//static std::mutex unit_mutex;

const PhysicalQuantity
PhysicalQuantity::null_physical_quantity("NullPhysicalQuantity", "NullPQ",
					 					 "Null" "Null Physical Quantity");

const Unit Unit::null_unit("NullUnit", "Null Unit", "Null unit", "Null",
						   PhysicalQuantity::null_physical_quantity,
						   std::numeric_limits<double>::min(),
						   std::numeric_limits<double>::max());

const double Unit::Invalid_Value = std::numeric_limits<double>::max();

static const double val_null_quantity = std::numeric_limits<double>::max();

const VtlQuantity VtlQuantity::null_quantity(Unit::null_unit, val_null_quantity);

bool conversion_exist(const char * src_symbol, const char * tgt_symbol)
{
  //std::lock_guard<std::mutex> critical_section(unit_mutex);
  return exist_conversion(src_symbol, tgt_symbol);
}

double unit_convert(const char * src_symbol, const char * tgt_symbol,
		    double val)
{
  //std::lock_guard<std::mutex> critical_section(unit_mutex);
  return unit_convert_symbol_to_symbol(src_symbol, val, tgt_symbol);
}

// The following global singleton variables are generated by extract-cv script
UnitConverter<Kelvin, Kelvin> __uc__Kelvin__to__Kelvin;
UnitConverter<Celsius, Celsius> __uc__Celsius__to__Celsius;
UnitConverter<Fahrenheit, Fahrenheit> __uc__Fahrenheit__to__Fahrenheit;
UnitConverter<Rankine, Rankine> __uc__Rankine__to__Rankine;
UnitConverter<Kelvin, Fahrenheit> __uc__Kelvin__to__Fahrenheit;
UnitConverter<Celsius, Fahrenheit> __uc__Celsius__to__Fahrenheit;
UnitConverter<Rankine, Fahrenheit> __uc__Rankine__to__Fahrenheit;
UnitConverter<Rankine, Celsius> __uc__Rankine__to__Celsius;
UnitConverter<Kelvin, Celsius> __uc__Kelvin__to__Celsius;
UnitConverter<Fahrenheit, Celsius> __uc__Fahrenheit__to__Celsius;
UnitConverter<Fahrenheit, Rankine> __uc__Fahrenheit__to__Rankine;
UnitConverter<Celsius, Rankine> __uc__Celsius__to__Rankine;
UnitConverter<Kelvin, Rankine> __uc__Kelvin__to__Rankine;
UnitConverter<Fahrenheit, Kelvin> __uc__Fahrenheit__to__Kelvin;
UnitConverter<Rankine, Kelvin> __uc__Rankine__to__Kelvin;
UnitConverter<Celsius, Kelvin> __uc__Celsius__to__Kelvin;
UnitConverter<Bar, Bar> __uc__Bar__to__Bar;
UnitConverter<Pascal, Pascal> __uc__Pascal__to__Pascal;
UnitConverter<kPascal, kPascal> __uc__kPascal__to__kPascal;
UnitConverter<mPascal, mPascal> __uc__mPascal__to__mPascal;
UnitConverter<psia, psia> __uc__psia__to__psia;
UnitConverter<psig, psig> __uc__psig__to__psig;
UnitConverter<Atmosphere, Atmosphere> __uc__Atmosphere__to__Atmosphere;
UnitConverter<Atmosphere, Pascal> __uc__Atmosphere__to__Pascal;
UnitConverter<Bar, Pascal> __uc__Bar__to__Pascal;
UnitConverter<psia, Pascal> __uc__psia__to__Pascal;
UnitConverter<psig, Pascal> __uc__psig__to__Pascal;
UnitConverter<kPascal, Pascal> __uc__kPascal__to__Pascal;
UnitConverter<mPascal, Pascal> __uc__mPascal__to__Pascal;
UnitConverter<Bar, Atmosphere> __uc__Bar__to__Atmosphere;
UnitConverter<Pascal, Atmosphere> __uc__Pascal__to__Atmosphere;
UnitConverter<kPascal, Atmosphere> __uc__kPascal__to__Atmosphere;
UnitConverter<psia, Atmosphere> __uc__psia__to__Atmosphere;
UnitConverter<psig, Atmosphere> __uc__psig__to__Atmosphere;
UnitConverter<mPascal, Atmosphere> __uc__mPascal__to__Atmosphere;
UnitConverter<Atmosphere, Bar> __uc__Atmosphere__to__Bar;
UnitConverter<Pascal, Bar> __uc__Pascal__to__Bar;
UnitConverter<kPascal, Bar> __uc__kPascal__to__Bar;
UnitConverter<psia, Bar> __uc__psia__to__Bar;
UnitConverter<psig, Bar> __uc__psig__to__Bar;
UnitConverter<mPascal, Bar> __uc__mPascal__to__Bar;
UnitConverter<Atmosphere, kPascal> __uc__Atmosphere__to__kPascal;
UnitConverter<Bar, kPascal> __uc__Bar__to__kPascal;
UnitConverter<psia, kPascal> __uc__psia__to__kPascal;
UnitConverter<psig, kPascal> __uc__psig__to__kPascal;
UnitConverter<Pascal, kPascal> __uc__Pascal__to__kPascal;
UnitConverter<mPascal, kPascal> __uc__mPascal__to__kPascal;
UnitConverter<Atmosphere, mPascal> __uc__Atmosphere__to__mPascal;
UnitConverter<Bar, mPascal> __uc__Bar__to__mPascal;
UnitConverter<psia, mPascal> __uc__psia__to__mPascal;
UnitConverter<psig, mPascal> __uc__psig__to__mPascal;
UnitConverter<Pascal, mPascal> __uc__Pascal__to__mPascal;
UnitConverter<kPascal, mPascal> __uc__kPascal__to__mPascal;
UnitConverter<Atmosphere, psia> __uc__Atmosphere__to__psia;
UnitConverter<Bar, psia> __uc__Bar__to__psia;
UnitConverter<Pascal, psia> __uc__Pascal__to__psia;
UnitConverter<kPascal, psia> __uc__kPascal__to__psia;
UnitConverter<psig, psia> __uc__psig__to__psia;
UnitConverter<mPascal, psia> __uc__mPascal__to__psia;
UnitConverter<psia, psig> __uc__psia__to__psig;
UnitConverter<Atmosphere, psig> __uc__Atmosphere__to__psig;
UnitConverter<Bar, psig> __uc__Bar__to__psig;
UnitConverter<Pascal, psig> __uc__Pascal__to__psig;
UnitConverter<kPascal, psig> __uc__kPascal__to__psig;
UnitConverter<mPascal, psig> __uc__mPascal__to__psig;
UnitConverter<Pascal_1, Pascal_1> __uc__Pascal_1__to__Pascal_1;
UnitConverter<mPa_1, mPa_1> __uc__mPa_1__to__mPa_1;
UnitConverter<psia_1, psia_1> __uc__psia_1__to__psia_1;
UnitConverter<Bar_1, Bar_1> __uc__Bar_1__to__Bar_1;
UnitConverter<Atmosphere_1, Atmosphere_1> __uc__Atmosphere_1__to__Atmosphere_1;
UnitConverter<mPa_1, Pascal_1> __uc__mPa_1__to__Pascal_1;
UnitConverter<psia_1, Pascal_1> __uc__psia_1__to__Pascal_1;
UnitConverter<Bar_1, Pascal_1> __uc__Bar_1__to__Pascal_1;
UnitConverter<Atmosphere_1, Pascal_1> __uc__Atmosphere_1__to__Pascal_1;
UnitConverter<Pascal_1, mPa_1> __uc__Pascal_1__to__mPa_1;
UnitConverter<psia_1, mPa_1> __uc__psia_1__to__mPa_1;
UnitConverter<Bar_1, mPa_1> __uc__Bar_1__to__mPa_1;
UnitConverter<Atmosphere_1, mPa_1> __uc__Atmosphere_1__to__mPa_1;
UnitConverter<Pascal_1, psia_1> __uc__Pascal_1__to__psia_1;
UnitConverter<mPa_1, psia_1> __uc__mPa_1__to__psia_1;
UnitConverter<Bar_1, psia_1> __uc__Bar_1__to__psia_1;
UnitConverter<Atmosphere_1, psia_1> __uc__Atmosphere_1__to__psia_1;
UnitConverter<Pascal_1, Bar_1> __uc__Pascal_1__to__Bar_1;
UnitConverter<mPa_1, Bar_1> __uc__mPa_1__to__Bar_1;
UnitConverter<psia_1, Bar_1> __uc__psia_1__to__Bar_1;
UnitConverter<Atmosphere_1, Bar_1> __uc__Atmosphere_1__to__Bar_1;
UnitConverter<Pascal_1, Atmosphere_1> __uc__Pascal_1__to__Atmosphere_1;
UnitConverter<mPa_1, Atmosphere_1> __uc__mPa_1__to__Atmosphere_1;
UnitConverter<psia_1, Atmosphere_1> __uc__psia_1__to__Atmosphere_1;
UnitConverter<Bar_1, Atmosphere_1> __uc__Bar_1__to__Atmosphere_1;
UnitConverter<PseudoReducedPressure, PseudoReducedPressure> __uc__PseudoReducedPressure__to__PseudoReducedPressure;
UnitConverter<PseudoReducedTemperature, PseudoReducedTemperature> __uc__PseudoReducedTemperature__to__PseudoReducedTemperature;
UnitConverter<Gr_cm3, Gr_cm3> __uc__Gr_cm3__to__Gr_cm3;
UnitConverter<Kg_m3, Kg_m3> __uc__Kg_m3__to__Kg_m3;
UnitConverter<Kg_L, Kg_L> __uc__Kg_L__to__Kg_L;
UnitConverter<Lb_ft3, Lb_ft3> __uc__Lb_ft3__to__Lb_ft3;
UnitConverter<Lb_Gal, Lb_Gal> __uc__Lb_Gal__to__Lb_Gal;
UnitConverter<Lb_Inch3, Lb_Inch3> __uc__Lb_Inch3__to__Lb_Inch3;
UnitConverter<Sg, Sg> __uc__Sg__to__Sg;
UnitConverter<Kg_m3, Gr_cm3> __uc__Kg_m3__to__Gr_cm3;
UnitConverter<Kg_L, Gr_cm3> __uc__Kg_L__to__Gr_cm3;
UnitConverter<Lb_ft3, Gr_cm3> __uc__Lb_ft3__to__Gr_cm3;
UnitConverter<Sg, Gr_cm3> __uc__Sg__to__Gr_cm3;
UnitConverter<Lb_Gal, Gr_cm3> __uc__Lb_Gal__to__Gr_cm3;
UnitConverter<Lb_Inch3, Gr_cm3> __uc__Lb_Inch3__to__Gr_cm3;
UnitConverter<Gr_cm3, Kg_m3> __uc__Gr_cm3__to__Kg_m3;
UnitConverter<Kg_L, Kg_m3> __uc__Kg_L__to__Kg_m3;
UnitConverter<Lb_ft3, Kg_m3> __uc__Lb_ft3__to__Kg_m3;
UnitConverter<Sg, Kg_m3> __uc__Sg__to__Kg_m3;
UnitConverter<Lb_Gal, Kg_m3> __uc__Lb_Gal__to__Kg_m3;
UnitConverter<Lb_Inch3, Kg_m3> __uc__Lb_Inch3__to__Kg_m3;
UnitConverter<Gr_cm3, Kg_L> __uc__Gr_cm3__to__Kg_L;
UnitConverter<Kg_m3, Kg_L> __uc__Kg_m3__to__Kg_L;
UnitConverter<Lb_ft3, Kg_L> __uc__Lb_ft3__to__Kg_L;
UnitConverter<Sg, Kg_L> __uc__Sg__to__Kg_L;
UnitConverter<Lb_Gal, Kg_L> __uc__Lb_Gal__to__Kg_L;
UnitConverter<Lb_Inch3, Kg_L> __uc__Lb_Inch3__to__Kg_L;
UnitConverter<Gr_cm3, Sg> __uc__Gr_cm3__to__Sg;
UnitConverter<Kg_m3, Sg> __uc__Kg_m3__to__Sg;
UnitConverter<Lb_ft3, Sg> __uc__Lb_ft3__to__Sg;
UnitConverter<Kg_L, Sg> __uc__Kg_L__to__Sg;
UnitConverter<Lb_Gal, Sg> __uc__Lb_Gal__to__Sg;
UnitConverter<Lb_Inch3, Sg> __uc__Lb_Inch3__to__Sg;
UnitConverter<Gr_cm3, Lb_ft3> __uc__Gr_cm3__to__Lb_ft3;
UnitConverter<Kg_m3, Lb_ft3> __uc__Kg_m3__to__Lb_ft3;
UnitConverter<Kg_L, Lb_ft3> __uc__Kg_L__to__Lb_ft3;
UnitConverter<Sg, Lb_ft3> __uc__Sg__to__Lb_ft3;
UnitConverter<Lb_Gal, Lb_ft3> __uc__Lb_Gal__to__Lb_ft3;
UnitConverter<Lb_Inch3, Lb_ft3> __uc__Lb_Inch3__to__Lb_ft3;
UnitConverter<Kg_m3, Lb_Gal> __uc__Kg_m3__to__Lb_Gal;
UnitConverter<Gr_cm3, Lb_Gal> __uc__Gr_cm3__to__Lb_Gal;
UnitConverter<Kg_L, Lb_Gal> __uc__Kg_L__to__Lb_Gal;
UnitConverter<Lb_ft3, Lb_Gal> __uc__Lb_ft3__to__Lb_Gal;
UnitConverter<Sg, Lb_Gal> __uc__Sg__to__Lb_Gal;
UnitConverter<Lb_Inch3, Lb_Gal> __uc__Lb_Inch3__to__Lb_Gal;
UnitConverter<Kg_m3, Lb_Inch3> __uc__Kg_m3__to__Lb_Inch3;
UnitConverter<Gr_cm3, Lb_Inch3> __uc__Gr_cm3__to__Lb_Inch3;
UnitConverter<Kg_L, Lb_Inch3> __uc__Kg_L__to__Lb_Inch3;
UnitConverter<Lb_ft3, Lb_Inch3> __uc__Lb_ft3__to__Lb_Inch3;
UnitConverter<Sg, Lb_Inch3> __uc__Sg__to__Lb_Inch3;
UnitConverter<Lb_Gal, Lb_Inch3> __uc__Lb_Gal__to__Lb_Inch3;
UnitConverter<Api, Api> __uc__Api__to__Api;
UnitConverter<Sg_do, Sg_do> __uc__Sg_do__to__Sg_do;
UnitConverter<Sg_do, Api> __uc__Sg_do__to__Api;
UnitConverter<Api, Sg_do> __uc__Api__to__Sg_do;
UnitConverter<Pwl_lb_ft3, Pwl_lb_ft3> __uc__Pwl_lb_ft3__to__Pwl_lb_ft3;
UnitConverter<Dissolved_Salt_Percent, Dissolved_Salt_Percent> __uc__Dissolved_Salt_Percent__to__Dissolved_Salt_Percent;
UnitConverter<Sgw_sg, Sgw_sg> __uc__Sgw_sg__to__Sgw_sg;
UnitConverter<Dissolved_Salt_PPM, Dissolved_Salt_PPM> __uc__Dissolved_Salt_PPM__to__Dissolved_Salt_PPM;
UnitConverter<Molality_NaCl, Molality_NaCl> __uc__Molality_NaCl__to__Molality_NaCl;
UnitConverter<CgL, CgL> __uc__CgL__to__CgL;
UnitConverter<Dissolved_Salt_Fraction, Dissolved_Salt_Fraction> __uc__Dissolved_Salt_Fraction__to__Dissolved_Salt_Fraction;
UnitConverter<Dissolved_Salt_Percent, Pwl_lb_ft3> __uc__Dissolved_Salt_Percent__to__Pwl_lb_ft3;
UnitConverter<Sgw_sg, Pwl_lb_ft3> __uc__Sgw_sg__to__Pwl_lb_ft3;
UnitConverter<Dissolved_Salt_PPM, Pwl_lb_ft3> __uc__Dissolved_Salt_PPM__to__Pwl_lb_ft3;
UnitConverter<Molality_NaCl, Pwl_lb_ft3> __uc__Molality_NaCl__to__Pwl_lb_ft3;
UnitConverter<CgL, Pwl_lb_ft3> __uc__CgL__to__Pwl_lb_ft3;
UnitConverter<Dissolved_Salt_Fraction, Pwl_lb_ft3> __uc__Dissolved_Salt_Fraction__to__Pwl_lb_ft3;
UnitConverter<CgL, Dissolved_Salt_Percent> __uc__CgL__to__Dissolved_Salt_Percent;
UnitConverter<Dissolved_Salt_PPM, Dissolved_Salt_Percent> __uc__Dissolved_Salt_PPM__to__Dissolved_Salt_Percent;
UnitConverter<Pwl_lb_ft3, Dissolved_Salt_Percent> __uc__Pwl_lb_ft3__to__Dissolved_Salt_Percent;
UnitConverter<Sgw_sg, Dissolved_Salt_Percent> __uc__Sgw_sg__to__Dissolved_Salt_Percent;
UnitConverter<Molality_NaCl, Dissolved_Salt_Percent> __uc__Molality_NaCl__to__Dissolved_Salt_Percent;
UnitConverter<Dissolved_Salt_Fraction, Dissolved_Salt_Percent> __uc__Dissolved_Salt_Fraction__to__Dissolved_Salt_Percent;
UnitConverter<Dissolved_Salt_Percent, Sgw_sg> __uc__Dissolved_Salt_Percent__to__Sgw_sg;
UnitConverter<Dissolved_Salt_PPM, Sgw_sg> __uc__Dissolved_Salt_PPM__to__Sgw_sg;
UnitConverter<Pwl_lb_ft3, Sgw_sg> __uc__Pwl_lb_ft3__to__Sgw_sg;
UnitConverter<Molality_NaCl, Sgw_sg> __uc__Molality_NaCl__to__Sgw_sg;
UnitConverter<CgL, Sgw_sg> __uc__CgL__to__Sgw_sg;
UnitConverter<Dissolved_Salt_Fraction, Sgw_sg> __uc__Dissolved_Salt_Fraction__to__Sgw_sg;
UnitConverter<Pwl_lb_ft3, Dissolved_Salt_PPM> __uc__Pwl_lb_ft3__to__Dissolved_Salt_PPM;
UnitConverter<Sgw_sg, Dissolved_Salt_PPM> __uc__Sgw_sg__to__Dissolved_Salt_PPM;
UnitConverter<Dissolved_Salt_Percent, Dissolved_Salt_PPM> __uc__Dissolved_Salt_Percent__to__Dissolved_Salt_PPM;
UnitConverter<Molality_NaCl, Dissolved_Salt_PPM> __uc__Molality_NaCl__to__Dissolved_Salt_PPM;
UnitConverter<CgL, Dissolved_Salt_PPM> __uc__CgL__to__Dissolved_Salt_PPM;
UnitConverter<Dissolved_Salt_Fraction, Dissolved_Salt_PPM> __uc__Dissolved_Salt_Fraction__to__Dissolved_Salt_PPM;
UnitConverter<Dissolved_Salt_Percent, Molality_NaCl> __uc__Dissolved_Salt_Percent__to__Molality_NaCl;
UnitConverter<Dissolved_Salt_PPM, Molality_NaCl> __uc__Dissolved_Salt_PPM__to__Molality_NaCl;
UnitConverter<Pwl_lb_ft3, Molality_NaCl> __uc__Pwl_lb_ft3__to__Molality_NaCl;
UnitConverter<Sgw_sg, Molality_NaCl> __uc__Sgw_sg__to__Molality_NaCl;
UnitConverter<CgL, Molality_NaCl> __uc__CgL__to__Molality_NaCl;
UnitConverter<Dissolved_Salt_Fraction, Molality_NaCl> __uc__Dissolved_Salt_Fraction__to__Molality_NaCl;
UnitConverter<Dissolved_Salt_Percent, CgL> __uc__Dissolved_Salt_Percent__to__CgL;
UnitConverter<Molality_NaCl, CgL> __uc__Molality_NaCl__to__CgL;
UnitConverter<Sgw_sg, CgL> __uc__Sgw_sg__to__CgL;
UnitConverter<Pwl_lb_ft3, CgL> __uc__Pwl_lb_ft3__to__CgL;
UnitConverter<Dissolved_Salt_PPM, CgL> __uc__Dissolved_Salt_PPM__to__CgL;
UnitConverter<Dissolved_Salt_Fraction, CgL> __uc__Dissolved_Salt_Fraction__to__CgL;
UnitConverter<CgL, Dissolved_Salt_Fraction> __uc__CgL__to__Dissolved_Salt_Fraction;
UnitConverter<Dissolved_Salt_PPM, Dissolved_Salt_Fraction> __uc__Dissolved_Salt_PPM__to__Dissolved_Salt_Fraction;
UnitConverter<Pwl_lb_ft3, Dissolved_Salt_Fraction> __uc__Pwl_lb_ft3__to__Dissolved_Salt_Fraction;
UnitConverter<Sgw_sg, Dissolved_Salt_Fraction> __uc__Sgw_sg__to__Dissolved_Salt_Fraction;
UnitConverter<Molality_NaCl, Dissolved_Salt_Fraction> __uc__Molality_NaCl__to__Dissolved_Salt_Fraction;
UnitConverter<Dissolved_Salt_Percent, Dissolved_Salt_Fraction> __uc__Dissolved_Salt_Percent__to__Dissolved_Salt_Fraction;
UnitConverter<SCF_STB, SCF_STB> __uc__SCF_STB__to__SCF_STB;
UnitConverter<Mscf_STB, Mscf_STB> __uc__Mscf_STB__to__Mscf_STB;
UnitConverter<MMscf_STB, MMscf_STB> __uc__MMscf_STB__to__MMscf_STB;
UnitConverter<Sm3_Sm3, Sm3_Sm3> __uc__Sm3_Sm3__to__Sm3_Sm3;
UnitConverter<Mscf_STB, SCF_STB> __uc__Mscf_STB__to__SCF_STB;
UnitConverter<MMscf_STB, SCF_STB> __uc__MMscf_STB__to__SCF_STB;
UnitConverter<Sm3_Sm3, SCF_STB> __uc__Sm3_Sm3__to__SCF_STB;
UnitConverter<SCF_STB, Mscf_STB> __uc__SCF_STB__to__Mscf_STB;
UnitConverter<MMscf_STB, Mscf_STB> __uc__MMscf_STB__to__Mscf_STB;
UnitConverter<Sm3_Sm3, Mscf_STB> __uc__Sm3_Sm3__to__Mscf_STB;
UnitConverter<SCF_STB, MMscf_STB> __uc__SCF_STB__to__MMscf_STB;
UnitConverter<Mscf_STB, MMscf_STB> __uc__Mscf_STB__to__MMscf_STB;
UnitConverter<Sm3_Sm3, MMscf_STB> __uc__Sm3_Sm3__to__MMscf_STB;
UnitConverter<SCF_STB, Sm3_Sm3> __uc__SCF_STB__to__Sm3_Sm3;
UnitConverter<Mscf_STB, Sm3_Sm3> __uc__Mscf_STB__to__Sm3_Sm3;
UnitConverter<MMscf_STB, Sm3_Sm3> __uc__MMscf_STB__to__Sm3_Sm3;
UnitConverter<RB_STB, RB_STB> __uc__RB_STB__to__RB_STB;
UnitConverter<Rm3_Sm3, Rm3_Sm3> __uc__Rm3_Sm3__to__Rm3_Sm3;
UnitConverter<RB_STB, Rm3_Sm3> __uc__RB_STB__to__Rm3_Sm3;
UnitConverter<Rm3_Sm3, RB_STB> __uc__Rm3_Sm3__to__RB_STB;
UnitConverter<Sgg, Sgg> __uc__Sgg__to__Sgg;
UnitConverter<rhog_kg_m3_atStandCond, rhog_kg_m3_atStandCond> __uc__rhog_kg_m3_atStandCond__to__rhog_kg_m3_atStandCond;
UnitConverter<rhog_lb_ft3_atStandCond, rhog_lb_ft3_atStandCond> __uc__rhog_lb_ft3_atStandCond__to__rhog_lb_ft3_atStandCond;
UnitConverter<rhog_kg_m3_atStandCond, Sgg> __uc__rhog_kg_m3_atStandCond__to__Sgg;
UnitConverter<rhog_lb_ft3_atStandCond, Sgg> __uc__rhog_lb_ft3_atStandCond__to__Sgg;
UnitConverter<Sgg, rhog_kg_m3_atStandCond> __uc__Sgg__to__rhog_kg_m3_atStandCond;
UnitConverter<rhog_lb_ft3_atStandCond, rhog_kg_m3_atStandCond> __uc__rhog_lb_ft3_atStandCond__to__rhog_kg_m3_atStandCond;
UnitConverter<Sgg, rhog_lb_ft3_atStandCond> __uc__Sgg__to__rhog_lb_ft3_atStandCond;
UnitConverter<rhog_kg_m3_atStandCond, rhog_lb_ft3_atStandCond> __uc__rhog_kg_m3_atStandCond__to__rhog_lb_ft3_atStandCond;
UnitConverter<kg_mxs, kg_mxs> __uc__kg_mxs__to__kg_mxs;
UnitConverter<lb_ftxs, lb_ftxs> __uc__lb_ftxs__to__lb_ftxs;
UnitConverter<g_cmxs, g_cmxs> __uc__g_cmxs__to__g_cmxs;
UnitConverter<CP, CP> __uc__CP__to__CP;
UnitConverter<Paxs, Paxs> __uc__Paxs__to__Paxs;
UnitConverter<lb_ftxh, lb_ftxh> __uc__lb_ftxh__to__lb_ftxh;
UnitConverter<Poise, Poise> __uc__Poise__to__Poise;
UnitConverter<mP, mP> __uc__mP__to__mP;
UnitConverter<lb_ftxs, kg_mxs> __uc__lb_ftxs__to__kg_mxs;
UnitConverter<g_cmxs, kg_mxs> __uc__g_cmxs__to__kg_mxs;
UnitConverter<CP, kg_mxs> __uc__CP__to__kg_mxs;
UnitConverter<Paxs, kg_mxs> __uc__Paxs__to__kg_mxs;
UnitConverter<lb_ftxh, kg_mxs> __uc__lb_ftxh__to__kg_mxs;
UnitConverter<Poise, kg_mxs> __uc__Poise__to__kg_mxs;
UnitConverter<mP, kg_mxs> __uc__mP__to__kg_mxs;
UnitConverter<kg_mxs, Poise> __uc__kg_mxs__to__Poise;
UnitConverter<lb_ftxs, Poise> __uc__lb_ftxs__to__Poise;
UnitConverter<CP, Poise> __uc__CP__to__Poise;
UnitConverter<Paxs, Poise> __uc__Paxs__to__Poise;
UnitConverter<lb_ftxh, Poise> __uc__lb_ftxh__to__Poise;
UnitConverter<g_cmxs, Poise> __uc__g_cmxs__to__Poise;
UnitConverter<mP, Poise> __uc__mP__to__Poise;
UnitConverter<kg_mxs, g_cmxs> __uc__kg_mxs__to__g_cmxs;
UnitConverter<lb_ftxs, g_cmxs> __uc__lb_ftxs__to__g_cmxs;
UnitConverter<CP, g_cmxs> __uc__CP__to__g_cmxs;
UnitConverter<Paxs, g_cmxs> __uc__Paxs__to__g_cmxs;
UnitConverter<lb_ftxh, g_cmxs> __uc__lb_ftxh__to__g_cmxs;
UnitConverter<Poise, g_cmxs> __uc__Poise__to__g_cmxs;
UnitConverter<mP, g_cmxs> __uc__mP__to__g_cmxs;
UnitConverter<kg_mxs, CP> __uc__kg_mxs__to__CP;
UnitConverter<lb_ftxs, CP> __uc__lb_ftxs__to__CP;
UnitConverter<g_cmxs, CP> __uc__g_cmxs__to__CP;
UnitConverter<Paxs, CP> __uc__Paxs__to__CP;
UnitConverter<lb_ftxh, CP> __uc__lb_ftxh__to__CP;
UnitConverter<Poise, CP> __uc__Poise__to__CP;
UnitConverter<mP, CP> __uc__mP__to__CP;
UnitConverter<kg_mxs, Paxs> __uc__kg_mxs__to__Paxs;
UnitConverter<lb_ftxs, Paxs> __uc__lb_ftxs__to__Paxs;
UnitConverter<g_cmxs, Paxs> __uc__g_cmxs__to__Paxs;
UnitConverter<CP, Paxs> __uc__CP__to__Paxs;
UnitConverter<lb_ftxh, Paxs> __uc__lb_ftxh__to__Paxs;
UnitConverter<Poise, Paxs> __uc__Poise__to__Paxs;
UnitConverter<mP, Paxs> __uc__mP__to__Paxs;
UnitConverter<kg_mxs, lb_ftxh> __uc__kg_mxs__to__lb_ftxh;
UnitConverter<lb_ftxs, lb_ftxh> __uc__lb_ftxs__to__lb_ftxh;
UnitConverter<CP, lb_ftxh> __uc__CP__to__lb_ftxh;
UnitConverter<Paxs, lb_ftxh> __uc__Paxs__to__lb_ftxh;
UnitConverter<Poise, lb_ftxh> __uc__Poise__to__lb_ftxh;
UnitConverter<g_cmxs, lb_ftxh> __uc__g_cmxs__to__lb_ftxh;
UnitConverter<mP, lb_ftxh> __uc__mP__to__lb_ftxh;
UnitConverter<kg_mxs, lb_ftxs> __uc__kg_mxs__to__lb_ftxs;
UnitConverter<g_cmxs, lb_ftxs> __uc__g_cmxs__to__lb_ftxs;
UnitConverter<CP, lb_ftxs> __uc__CP__to__lb_ftxs;
UnitConverter<Paxs, lb_ftxs> __uc__Paxs__to__lb_ftxs;
UnitConverter<lb_ftxh, lb_ftxs> __uc__lb_ftxh__to__lb_ftxs;
UnitConverter<Poise, lb_ftxs> __uc__Poise__to__lb_ftxs;
UnitConverter<mP, lb_ftxs> __uc__mP__to__lb_ftxs;
UnitConverter<Poise, mP> __uc__Poise__to__mP;
UnitConverter<lb_ftxs, mP> __uc__lb_ftxs__to__mP;
UnitConverter<CP, mP> __uc__CP__to__mP;
UnitConverter<Paxs, mP> __uc__Paxs__to__mP;
UnitConverter<lb_ftxh, mP> __uc__lb_ftxh__to__mP;
UnitConverter<g_cmxs, mP> __uc__g_cmxs__to__mP;
UnitConverter<kg_mxs, mP> __uc__kg_mxs__to__mP;
UnitConverter<MoleFraction, MoleFraction> __uc__MoleFraction__to__MoleFraction;
UnitConverter<VolumeFraction, VolumeFraction> __uc__VolumeFraction__to__VolumeFraction;
UnitConverter<MolePercent, MolePercent> __uc__MolePercent__to__MolePercent;
UnitConverter<VolumePercent, VolumePercent> __uc__VolumePercent__to__VolumePercent;
UnitConverter<VolumeFraction, MoleFraction> __uc__VolumeFraction__to__MoleFraction;
UnitConverter<MolePercent, MoleFraction> __uc__MolePercent__to__MoleFraction;
UnitConverter<VolumePercent, MoleFraction> __uc__VolumePercent__to__MoleFraction;
UnitConverter<MoleFraction, VolumeFraction> __uc__MoleFraction__to__VolumeFraction;
UnitConverter<MolePercent, VolumeFraction> __uc__MolePercent__to__VolumeFraction;
UnitConverter<VolumePercent, VolumeFraction> __uc__VolumePercent__to__VolumeFraction;
UnitConverter<MoleFraction, MolePercent> __uc__MoleFraction__to__MolePercent;
UnitConverter<VolumeFraction, MolePercent> __uc__VolumeFraction__to__MolePercent;
UnitConverter<VolumePercent, MolePercent> __uc__VolumePercent__to__MolePercent;
UnitConverter<MoleFraction, VolumePercent> __uc__MoleFraction__to__VolumePercent;
UnitConverter<VolumeFraction, VolumePercent> __uc__VolumeFraction__to__VolumePercent;
UnitConverter<MolePercent, VolumePercent> __uc__MolePercent__to__VolumePercent;
UnitConverter<dynes_cm, dynes_cm> __uc__dynes_cm__to__dynes_cm;
UnitConverter<N_m, N_m> __uc__N_m__to__N_m;
UnitConverter<mN_m, mN_m> __uc__mN_m__to__mN_m;
UnitConverter<gram_force_cm, gram_force_cm> __uc__gram_force_cm__to__gram_force_cm;
UnitConverter<pound_force_inch, pound_force_inch> __uc__pound_force_inch__to__pound_force_inch;
UnitConverter<N_m, dynes_cm> __uc__N_m__to__dynes_cm;
UnitConverter<mN_m, dynes_cm> __uc__mN_m__to__dynes_cm;
UnitConverter<gram_force_cm, dynes_cm> __uc__gram_force_cm__to__dynes_cm;
UnitConverter<pound_force_inch, dynes_cm> __uc__pound_force_inch__to__dynes_cm;
UnitConverter<dynes_cm, N_m> __uc__dynes_cm__to__N_m;
UnitConverter<mN_m, N_m> __uc__mN_m__to__N_m;
UnitConverter<gram_force_cm, N_m> __uc__gram_force_cm__to__N_m;
UnitConverter<pound_force_inch, N_m> __uc__pound_force_inch__to__N_m;
UnitConverter<dynes_cm, mN_m> __uc__dynes_cm__to__mN_m;
UnitConverter<N_m, mN_m> __uc__N_m__to__mN_m;
UnitConverter<gram_force_cm, mN_m> __uc__gram_force_cm__to__mN_m;
UnitConverter<pound_force_inch, mN_m> __uc__pound_force_inch__to__mN_m;
UnitConverter<dynes_cm, gram_force_cm> __uc__dynes_cm__to__gram_force_cm;
UnitConverter<N_m, gram_force_cm> __uc__N_m__to__gram_force_cm;
UnitConverter<mN_m, gram_force_cm> __uc__mN_m__to__gram_force_cm;
UnitConverter<pound_force_inch, gram_force_cm> __uc__pound_force_inch__to__gram_force_cm;
UnitConverter<dynes_cm, pound_force_inch> __uc__dynes_cm__to__pound_force_inch;
UnitConverter<N_m, pound_force_inch> __uc__N_m__to__pound_force_inch;
UnitConverter<mN_m, pound_force_inch> __uc__mN_m__to__pound_force_inch;
UnitConverter<gram_force_cm, pound_force_inch> __uc__gram_force_cm__to__pound_force_inch;
UnitConverter<Zfactor, Zfactor> __uc__Zfactor__to__Zfactor;
UnitConverter<RCF_SCF, RCF_SCF> __uc__RCF_SCF__to__RCF_SCF;
UnitConverter<RM3_SM3, RM3_SM3> __uc__RM3_SM3__to__RM3_SM3;
UnitConverter<RCF_MSCF, RCF_MSCF> __uc__RCF_MSCF__to__RCF_MSCF;
UnitConverter<RB_SCF, RB_SCF> __uc__RB_SCF__to__RB_SCF;
UnitConverter<RB_MSCF, RB_MSCF> __uc__RB_MSCF__to__RB_MSCF;
UnitConverter<RM3_SM3, RCF_SCF> __uc__RM3_SM3__to__RCF_SCF;
UnitConverter<RCF_MSCF, RCF_SCF> __uc__RCF_MSCF__to__RCF_SCF;
UnitConverter<RB_SCF, RCF_SCF> __uc__RB_SCF__to__RCF_SCF;
UnitConverter<RB_MSCF, RCF_SCF> __uc__RB_MSCF__to__RCF_SCF;
UnitConverter<RCF_SCF, RM3_SM3> __uc__RCF_SCF__to__RM3_SM3;
UnitConverter<RCF_MSCF, RM3_SM3> __uc__RCF_MSCF__to__RM3_SM3;
UnitConverter<RB_SCF, RM3_SM3> __uc__RB_SCF__to__RM3_SM3;
UnitConverter<RB_MSCF, RM3_SM3> __uc__RB_MSCF__to__RM3_SM3;
UnitConverter<RCF_SCF, RCF_MSCF> __uc__RCF_SCF__to__RCF_MSCF;
UnitConverter<RM3_SM3, RCF_MSCF> __uc__RM3_SM3__to__RCF_MSCF;
UnitConverter<RB_SCF, RCF_MSCF> __uc__RB_SCF__to__RCF_MSCF;
UnitConverter<RB_MSCF, RCF_MSCF> __uc__RB_MSCF__to__RCF_MSCF;
UnitConverter<RCF_SCF, RB_SCF> __uc__RCF_SCF__to__RB_SCF;
UnitConverter<RM3_SM3, RB_SCF> __uc__RM3_SM3__to__RB_SCF;
UnitConverter<RCF_MSCF, RB_SCF> __uc__RCF_MSCF__to__RB_SCF;
UnitConverter<RB_MSCF, RB_SCF> __uc__RB_MSCF__to__RB_SCF;
UnitConverter<RCF_SCF, RB_MSCF> __uc__RCF_SCF__to__RB_MSCF;
UnitConverter<RM3_SM3, RB_MSCF> __uc__RM3_SM3__to__RB_MSCF;
UnitConverter<RCF_MSCF, RB_MSCF> __uc__RCF_MSCF__to__RB_MSCF;
UnitConverter<RB_SCF, RB_MSCF> __uc__RB_SCF__to__RB_MSCF;
UnitConverter<wc_percent, wc_percent> __uc__wc_percent__to__wc_percent;
UnitConverter<wc_fraction, wc_fraction> __uc__wc_fraction__to__wc_fraction;
UnitConverter<wc_fraction, wc_percent> __uc__wc_fraction__to__wc_percent;
UnitConverter<wc_percent, wc_fraction> __uc__wc_percent__to__wc_fraction;
UnitConverter<RCFGas_STB, RCFGas_STB> __uc__RCFGas_STB__to__RCFGas_STB;
UnitConverter<RBGas_STB, RBGas_STB> __uc__RBGas_STB__to__RBGas_STB;
UnitConverter<RCFGas_STB, RBGas_STB> __uc__RCFGas_STB__to__RBGas_STB;
UnitConverter<RBGas_STB, RCFGas_STB> __uc__RBGas_STB__to__RCFGas_STB;
UnitConverter<STB_SCF, STB_SCF> __uc__STB_SCF__to__STB_SCF;
UnitConverter<STB_Mscf, STB_Mscf> __uc__STB_Mscf__to__STB_Mscf;
UnitConverter<STB_MMscf, STB_MMscf> __uc__STB_MMscf__to__STB_MMscf;
UnitConverter<Sm3Liquid_Sm3, Sm3Liquid_Sm3> __uc__Sm3Liquid_Sm3__to__Sm3Liquid_Sm3;
UnitConverter<STB_Mscf, STB_SCF> __uc__STB_Mscf__to__STB_SCF;
UnitConverter<STB_MMscf, STB_SCF> __uc__STB_MMscf__to__STB_SCF;
UnitConverter<Sm3Liquid_Sm3, STB_SCF> __uc__Sm3Liquid_Sm3__to__STB_SCF;
UnitConverter<STB_SCF, STB_Mscf> __uc__STB_SCF__to__STB_Mscf;
UnitConverter<STB_MMscf, STB_Mscf> __uc__STB_MMscf__to__STB_Mscf;
UnitConverter<Sm3Liquid_Sm3, STB_Mscf> __uc__Sm3Liquid_Sm3__to__STB_Mscf;
UnitConverter<STB_SCF, STB_MMscf> __uc__STB_SCF__to__STB_MMscf;
UnitConverter<STB_Mscf, STB_MMscf> __uc__STB_Mscf__to__STB_MMscf;
UnitConverter<Sm3Liquid_Sm3, STB_MMscf> __uc__Sm3Liquid_Sm3__to__STB_MMscf;
UnitConverter<STB_SCF, Sm3Liquid_Sm3> __uc__STB_SCF__to__Sm3Liquid_Sm3;
UnitConverter<STB_Mscf, Sm3Liquid_Sm3> __uc__STB_Mscf__to__Sm3Liquid_Sm3;
UnitConverter<STB_MMscf, Sm3Liquid_Sm3> __uc__STB_MMscf__to__Sm3Liquid_Sm3;
UnitConverter<Hertz, Hertz> __uc__Hertz__to__Hertz;
UnitConverter<Revolution_per_minute, Revolution_per_minute> __uc__Revolution_per_minute__to__Revolution_per_minute;
UnitConverter<Hertz, Revolution_per_minute> __uc__Hertz__to__Revolution_per_minute;
UnitConverter<Revolution_per_minute, Hertz> __uc__Revolution_per_minute__to__Hertz;
UnitConverter<BPD, BPD> __uc__BPD__to__BPD;
UnitConverter<GPM, GPM> __uc__GPM__to__GPM;
UnitConverter<CMD, CMD> __uc__CMD__to__CMD;
UnitConverter<CMS, CMS> __uc__CMS__to__CMS;
UnitConverter<GPM, BPD> __uc__GPM__to__BPD;
UnitConverter<CMD, BPD> __uc__CMD__to__BPD;
UnitConverter<CMS, BPD> __uc__CMS__to__BPD;
UnitConverter<BPD, GPM> __uc__BPD__to__GPM;
UnitConverter<CMD, GPM> __uc__CMD__to__GPM;
UnitConverter<CMS, GPM> __uc__CMS__to__GPM;
UnitConverter<BPD, CMD> __uc__BPD__to__CMD;
UnitConverter<GPM, CMD> __uc__GPM__to__CMD;
UnitConverter<CMS, CMD> __uc__CMS__to__CMD;
UnitConverter<BPD, CMS> __uc__BPD__to__CMS;
UnitConverter<CMD, CMS> __uc__CMD__to__CMS;
UnitConverter<GPM, CMS> __uc__GPM__to__CMS;
UnitConverter<Ampere, Ampere> __uc__Ampere__to__Ampere;
UnitConverter<SpecificGravity, SpecificGravity> __uc__SpecificGravity__to__SpecificGravity;
UnitConverter<headFeet, headFeet> __uc__headFeet__to__headFeet;
UnitConverter<headInch, headInch> __uc__headInch__to__headInch;
UnitConverter<headMeter, headMeter> __uc__headMeter__to__headMeter;
UnitConverter<headInch, headFeet> __uc__headInch__to__headFeet;
UnitConverter<headMeter, headFeet> __uc__headMeter__to__headFeet;
UnitConverter<headMeter, headInch> __uc__headMeter__to__headInch;
UnitConverter<headFeet, headInch> __uc__headFeet__to__headInch;
UnitConverter<headFeet, headMeter> __uc__headFeet__to__headMeter;
UnitConverter<headInch, headMeter> __uc__headInch__to__headMeter;
