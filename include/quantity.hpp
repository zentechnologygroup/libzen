#ifndef QUANTITY_HPP
#define QUANTITY_HPP

/* C++ System Headers */
#include <memory> 				// Utilities to manage dynamic memory
#include <typeinfo>				// Operators typeid and dynamic_cast
#include <type_traits>		// Classes to obtain type information on compile-time.
#include <string> 				// String class
#include <sstream>				// String stream classes
#include <limits> 				// Characteristics of arithmetic types
#include <cassert>				// Assert fuction
#include <cmath>					// Math Library
#include <vector> 				// Container class
#include <set>		 				// Container class
#include <unordered_map>	// Container class

#include "basequantity.hpp"

//namespace ztg {
//namespace units {

template <class UnitName>
class Quantity : public BaseQuantity
{
  // assign to value the value contained in q converted to UnitName
  // and validates that both units refer to the same physical quantity
  // and the converted value is inside the valid range
  template <class SrcUnit>
  void assign_converted(const Quantity<SrcUnit> & q)
  {
    check_physical_units(q);
    value = unit_convert<SrcUnit, UnitName>(q.get_value());
    check_value();
  }

 public:

  VtlQuantity to_VtlQuantity() const;
  Quantity(double val) : BaseQuantity(UnitName::get_instance(), val)
  {
    check_value(); // value must be inside the specified range
  }

  Quantity() : BaseQuantity(UnitName::get_instance())
  {
    check_value(); // value must be inside the specified range
  }

  /// direct copy constructor
  Quantity(const Quantity & q) noexcept : BaseQuantity(q.unit, q.get_value()) {}

  /// direct copy assignment 
  Quantity & operator = (const Quantity & q) noexcept
  {
    if (&q == this) {
      return *this;
    }
    value = q.get_value();
    return *this;
  }

  /// Inter unit constructor. Perform the conversion
  template <class SrcUnit> Quantity(const Quantity<SrcUnit> & q)
  	: BaseQuantity(UnitName::get_instance())
  {
    assign_converted(q);
  }

  Quantity next() const 
  {
   return Quantity(this->__increase()); 
 	}

  Quantity prev() const 
  { 
  	return Quantity(this->__decrease()); 
  }

  /// Inter unit assignment. Perform the conversion
  template <class SrcUnit>
  Quantity & operator = (const Quantity<SrcUnit> & q)
  {
    if ((void*) &q == (void*) this) {
      return *this;
    }
    assign_converted(q);
    return *this;
  }

  inline Quantity(const VtlQuantity & q);
  inline Quantity & operator = (const VtlQuantity & q);

  Quantity & operator += (const Quantity & rhs) 
  {
    value += rhs.get_value();
    check_value();
    return *this;
  }

  Quantity operator + (const Quantity & rhs) const
  {
    Quantity ret(*this);
    ret += rhs;
    return ret;
  }

  Quantity & operator -= (const Quantity & rhs)
  {
    value -= rhs.get_value();
    check_value();
    return *this;
  }

  Quantity operator - (const Quantity & rhs) const
  {
    Quantity ret(*this);
    ret -= rhs;
    return ret;
  }

  template <class U>
  Quantity<typename Combine_Units<UnitName, U>::type>
  operator * (const Quantity<U> & rhs) const
  {
    using T = typename Combine_Units<UnitName, U>::type;
    return Quantity<T>(value * rhs.get_value());
  }

  // division between same units remove the unit and returns double
  double operator / (const Quantity & rhs) const
  {
    return value / rhs.get_value();
  }

  template <class U>
  Quantity<typename Combine_Units<UnitName, U>::type>
  operator / (const Quantity<U> & rhs) const
  {
    using T = typename Combine_Units<UnitName, U>::type;
    return Quantity<T>(value / rhs.get_value());
  }

  template <class U>
  bool operator < (const Quantity<U> & rhs) const
  {
    Quantity r = { rhs }; // here the conversion is done
    return value < r.get_value();
  }

  template <class U>
  bool operator <= (const Quantity<U> & rhs) const
  {
    Quantity r = { rhs }; // here the conversion is done
    return value <= r.get_value();
  }

  template <class U>
  bool operator > (const Quantity<U> & rhs) const
  {
    Quantity r = { rhs }; // here the conversion is done
    return value > r.get_value();
  }

  template <class U>
  bool operator >= (const Quantity<U> & rhs) const
  {
    Quantity r = { rhs }; // here the conversion is done
    return value >= r.get_value();
  }

  template <class U>
  bool operator == (const Quantity<U> & rhs) const
  {
    Quantity r = { rhs }; // here the conversion is done
    return value == r.get_value();
  }

  template <class U>
  bool operator != (const Quantity<U> & rhs) const
  {
    return not (*this == rhs);
  }

  /// Return `this` converted to `Quantity<U>
  template <class U> Quantity convert() const
  {
    return Quantity<U>(*this);
  }

  inline Quantity & operator += (const VtlQuantity & rhs);
  inline Quantity & operator -= (const VtlQuantity & rhs);
  inline VtlQuantity operator + (const VtlQuantity & rhs) const;
  inline VtlQuantity operator - (const VtlQuantity & rhs) const;
  inline VtlQuantity  operator * (const VtlQuantity &) const;
  inline VtlQuantity  operator / (const VtlQuantity &) const;

};

//} // namespace units
//} // namespace ztg

#endif // QUANTITY_HPP