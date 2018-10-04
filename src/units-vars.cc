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