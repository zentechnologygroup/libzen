#ifndef UNIT_EXCEPTIONS_H
#define UNIT_EXCEPTIONS_H

# include <aleph-exceptions.H>

DEFINE_ALEPH_EXCEPTION(InvalidPhysicalQuantity, "Invalid physical quantity")

DEFINE_ALEPH_EXCEPTION(WrongSiblingUnit,
		     "Sibling unit is not physically related");

DEFINE_ALEPH_EXCEPTION(WrongUnitRatio, "wrong unit ratio");

DEFINE_ALEPH_EXCEPTION(UnitConversionNotFound, "Unit conversion not found");

DEFINE_ALEPH_EXCEPTION(DuplicatedUnitConversion, "duplicated unit conversion")

DEFINE_ALEPH_EXCEPTION(OutOfUnitRange, "Value is out of unit range");

DEFINE_ALEPH_EXCEPTION(DifferentUnits,
		     "Binary Operation between involves different units");

DEFINE_ALEPH_EXCEPTION(UnitNotFound, "unit not found");

DEFINE_ALEPH_EXCEPTION(CompoundUnitNotFound, "compound unit not found");

DEFINE_ALEPH_EXCEPTION(UnitException, "unit exception");

#endif
