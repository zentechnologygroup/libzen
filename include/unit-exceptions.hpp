#ifndef UNIT_EXCEPTIONS_HPP
#define UNIT_EXCEPTIONS_HPP

/* Project headers */
#include "zen-exceptions.hpp"

//namespace ztg {
//namespace exception {

DEFINE_ZEN_EXCEPTION(InvalidPhysicalQuantity, "Invalid physical quantity")
DEFINE_ZEN_EXCEPTION(WrongSiblingUnit,
				 	 "Sibling unit is not physically related");
DEFINE_ZEN_EXCEPTION(WrongUnitRatio, "wrong unit ratio");
DEFINE_ZEN_EXCEPTION(UnitConversionNotFound, "Unit conversion not found");
DEFINE_ZEN_EXCEPTION(DuplicatedUnitConversion, "duplicated unit conversion")
DEFINE_ZEN_EXCEPTION(OutOfUnitRange, "Value is out of unit range");
DEFINE_ZEN_EXCEPTION(DifferentUnits,
				     "Binary Operation between involves different units");
DEFINE_ZEN_EXCEPTION(UnitNotFound, "unit not found");
DEFINE_ZEN_EXCEPTION(CompoundUnitNotFound, "compound unit not found");
DEFINE_ZEN_EXCEPTION(UnitException, "unit exception");

//} // namespace exception
//} // namespace ztg

#endif // UNIT_EXCEPTIONS_HPP