#ifndef UNIT_CONVERTER_HPP
#define UNIT_CONVERTER_HPP


/* C++ System Headers */
#include <memory>         // Utilities to manage dynamic memory
#include <typeinfo>       // Operators typeid and dynamic_cast
#include <type_traits>    // Classes to obtain type information on compile-time.
#include <string>         // String class
#include <sstream>        // String stream classes
#include <limits>         // Characteristics of arithmetic types
#include <cassert>        // Assert fuction
#include <cmath>          // Math Library
#include <vector>         // Container class
#include <set>            // Container class
#include <unordered_map>  // Container class

//namespace ztg {
//namespace units {

template <class SrcUnit, class TgtUnit>
class UnitConverter
{
  static double convert(double val)
  {
    return unit_convert<SrcUnit, TgtUnit>(val);
  }

  Unit_Convert_Fct_Ptr fct_ptr = nullptr;

 public:

  UnitConverter()
  {
    const Unit & src_instance = SrcUnit::get_instance();
    const Unit & tgt_instance = TgtUnit::get_instance();
    const string & src_name = src_instance.name;
    const string & tgt_name = tgt_instance.name;
    
    if (search_conversion(src_instance, tgt_instance)) {
      ostringstream s;
      s << "Conversion from " << src_name << " to " << tgt_name
        << " does not share the same physical quantities ("
        << src_instance.physical_quantity.name << ", "
        << tgt_instance.physical_quantity.name << ")";
      ZENTHROW(WrongSiblingUnit, s.str());
    }

    if (&src_instance.physical_quantity != &tgt_instance.physical_quantity) {
      ostringstream s;
      s << "Conversion from " << src_name << " to " << tgt_name
        << " does not shae the same physical quantities ("
        << src_instance.physical_quantity.name << ", "
        << tgt_instance.physical_quantity.name << ")";
      ZENTHROW(WrongSiblingUnit, s.str());
    }
    
    const string & src_symbol = src_instance.symbol;
    const string & tgt_symbol = tgt_instance.symbol;

    if (__unit_name_name_tbl.find(std::make_pair(src_name, tgt_name)) != 
          __unit_name_name_tbl.end()) {
      ostringstream s;
      s << "Conversion from unit name " << src_name << " to unit name "
        << tgt_name << " has already been registered";
      ZENTHROW(UnitConversionNotFound, s.str());
    }

    if (__unit_name_symbol_tbl.find(std::make_pair(src_name, tgt_symbol)) != 
          __unit_name_symbol_tbl.end()) {
      ostringstream s;
      s << "Conversion from unit name " << src_name << " to symbol name "
        << tgt_symbol << " has already been registered";
      ZENTHROW(DuplicatedUnitConversion, s.str());
    }

    if (__unit_symbol_name_tbl.find(std::make_pair(src_symbol, tgt_name)) != 
          __unit_symbol_name_tbl.end()) {
      ostringstream s;
      s << "Conversion from symbol name " << src_symbol << " to unit name "
        << tgt_name << " has already been registered";
      ZENTHROW(DuplicatedUnitConversion, s.str());
    }

    if (__unit_symbol_symbol_tbl.find(std::make_pair(src_symbol, tgt_symbol)) != 
          __unit_symbol_symbol_tbl.end()) {
      ostringstream s;
      s << "Conversion from symbol name " << src_symbol << " to symbol name "
        << tgt_symbol << " has already been registered";
      ZENTHROW(DuplicatedUnitConversion, s.str());
    }

    fct_ptr = &UnitConverter::convert;

    __unit_map.insert(
        std::make_pair(std::make_pair(&src_instance,&tgt_instance), fct_ptr));
    __unit_name_name_tbl.insert(
        std::make_pair(std::make_pair(src_name, tgt_name), fct_ptr));
    __unit_name_symbol_tbl.insert(
        std::make_pair(std::make_pair(src_name, tgt_symbol), fct_ptr));
    __unit_symbol_name_tbl.insert(
        std::make_pair(std::make_pair(src_symbol, tgt_name), fct_ptr));
    __unit_symbol_symbol_tbl.insert(
        std::make_pair(std::make_pair(src_symbol, tgt_symbol), fct_ptr));

    assert(search_conversion(src_instance, tgt_instance));
    assert(__unit_name_name_tbl.find(make_pair(src_name, tgt_name)) != 
             __unit_name_name_tbl.end());
    assert(__unit_name_symbol_tbl.find(make_pair(src_name, tgt_symbol)) != 
             __unit_name_symbol_tbl.end());
    assert(__unit_symbol_name_tbl.find(make_pair(src_symbol, tgt_name)) != 
             __unit_symbol_name_tbl.end());
    assert(__unit_symbol_symbol_tbl.find(make_pair(src_symbol, tgt_symbol)) != 
             __unit_symbol_symbol_tbl.end());
  }

  Unit_Convert_Fct_Ptr operator () () const noexcept 
  { 
    return fct_ptr; 
  }
  
};

//} // namespace units
//} // namespace ztg

#endif // UNIT_CONVERTER_HPP