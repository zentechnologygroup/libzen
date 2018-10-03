#ifndef UNITS_HPP
#define UNITS_HPP

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

/* Project headers */
#include "unititem.hpp"
#include "unititemtable.hpp"
#include "unit-exceptions.hpp"
#include "utils.hpp"

//namespace ztg {
//namespace units {

class Unit;

class PhysicalQuantity : public UnitItem
{
  friend class Unit;
  using UnitItem::UnitItem;
  static UnitItemTable tbl;
  std::vector<const Unit *> unit_list;

 public:

  static const PhysicalQuantity null_physical_quantity;
  
 protected:

  PhysicalQuantity(const std::string & name, const std::string & symbol,
                   const std::string & latex_symbol, const std::string & desc)
    : UnitItem(name, symbol, latex_symbol, desc)
  {
    tbl.register_item(this);
  }

 public:

  const std::vector<const Unit * > & units() const 
  { 
    return unit_list; 
  }

  // Return all the defined  physical magnitudes  
  //static DynList<const PhysicalQuantity * > quantities()
  //{
  //  return tbl.items().maps<const PhysicalQuantity * >([] (auto p) {
  //           return static_cast<const PhysicalQuantity * >(p);
  //          });
  //}


  static std::vector <const PhysicalQuantity * > quantities() {

    std::vector <const UnitItem *> unit_item_vector =  tbl.items();
    std::vector <const PhysicalQuantity *> quantitie_vector;

    for(auto entry: unit_item_vector) {
      quantitie_vector.push_back(static_cast<const PhysicalQuantity * >(entry));
    }

    return quantitie_vector;
  }

  static std::vector <std::string> names() 
  { 
    return tbl.names(); 
  }

  static const PhysicalQuantity * search(const std::string & name)
  {
    auto ptr = tbl.search_by_name(name);
    return static_cast<const PhysicalQuantity * >(ptr);
  }
};

/** Defines a new physical magnitude

    @param[in] name of the new physical quantity
    @param[in] symbol string used as unit symbol
    @param[in] desc description 

 */
#define Declare_Physical_Quantity(quantity_class_name , symbol, lsymbol, desc) \
  class quantity_class_name  : public PhysicalQuantity                         \
  {                                                                            \
   public:                                                                     \
                                                                               \
    static const quantity_class_name  & get_instance()                         \
    {                                                                          \
      static quantity_class_name  instance;                                    \
      return instance;                                                         \
    }                                                                          \
                                                                               \
   private:                                                                    \
                                                                               \
    quantity_class_name () : PhysicalQuantity(#quantity_class_name , symbol,   \
                                              lsymbol, desc) {}                \
                                                                               \
  public:                                                                      \
                                                                               \
    quantity_class_name (const quantity_class_name &) = delete;                \
    void operator = (const quantity_class_name &) = delete;                    \
  };

class VtlQuantity; // forward declaration

/** Unit base class

 */
class Unit : public UnitItem
{
  double epsilon = 1e-6;

 public:

  static void validate_ratio(const double ratio)
  {
    if (not (ratio <= 0 or ratio > 0.3)) return;

    std::ostringstream s;
    s << "epsilon ratio " << ratio << " is not inside (0, " << ratio << ")";
    ZENTHROW(WrongUnitRatio, s.str());
  }

  static const Unit null_unit;
  static const double Invalid_Value;

  double get_epsilon() const 
  { 
    return epsilon; 
  }

  void set_epsilon(double ratio = 0.01) const
  {
    validate_ratio(ratio);
    const_cast<Unit*>(this)->epsilon = ratio * (max_val - min_val);
  }

  const PhysicalQuantity & physical_quantity;
  const double min_val = 0;
  const double max_val = 0;
  inline VtlQuantity min() const noexcept;
  inline VtlQuantity max() const noexcept;

  std::string to_string(size_t left_margin = 0) const
  {
    const std::string margin(left_margin, ' ');
    std::ostringstream s;
    s << margin << "Unit name         = " << name << "\n"
      << margin << "symbol            = " << symbol << "\n"
      << margin << "latex symbol      = " << latex_symbol << "\n"
      << margin << "description       = " << description << "\n"
      << margin << "physical quantity = " << physical_quantity.name << "\n"
      << margin << "min               = " << min_val << "\n"
      << margin << "max               = " << max_val << "\n"
      << margin << "epsilon           = " << epsilon
      << "( " << 100*epsilon << " %)";
    return s.str();
  }

  friend std::ostream & operator << (std::ostream & out, const Unit & unit)
  {
    return out << unit.to_string();
  }

private:

  static UnitItemTable tbl;
  static std::set<const Unit *> unit_tbl;

public:

  /// return the number of units
  static size_t size() 
  { 
    return Unit::unit_tbl.size(); 
  }

  /// Return a list of all declared and used units
  static std::vector<const Unit*> units() 
  {
    return GetSetKeys(Unit::unit_tbl); 
  }

  /// return all the units associated to this (including this)
  const std::vector<const Unit*> & family_units() const
  {
    return physical_quantity.units();
  }

  /// return all the units associated to this (not including this)
  //TODOO
  /*
  DynList<const Unit*> sibling_units() const
  {
    return physical_quantity.units().filter([this] (auto ptru)
              {
                return ptru != this;
              });
  }
  */

  bool is_sibling(const Unit & unit) const noexcept
  {
    return &physical_quantity == &unit.physical_quantity;
  }

  /** Search the unit associated to a name
      
      @param[in] name string containing the unit name
      @return constant pointer to the symbol. If the name is not
      found, then `nullptr` is returned
  */
  static const Unit * search_by_name(const std::string & symbol)
  {
    const UnitItem * ptr = Unit::tbl.search_by_name(symbol);
    const Unit * unit_ptr = static_cast<const Unit*>(ptr);
    return unit_ptr;
  }

  /** Search the unit associated to a symbol
      
      @param[in] symbol string containing the unit symbol
      @return constant pointer to the symbol. If the symbol is not
      found, then `nullptr` is returned
  */
  static const Unit * search_by_symbol(const std::string & symbol)
  {
    auto ptr = Unit::tbl.search_by_symbol(symbol);
    const Unit * unit_ptr = static_cast<const Unit*>(ptr);
    return unit_ptr;
  }

  static const Unit * search(const std::string & str)
  {
    auto ptr = search_by_name(str);
    if (ptr == nullptr) {
      return search_by_symbol(str);
    }
    
    return ptr;
  }

  static const std::vector<const Unit * > & units(const PhysicalQuantity & pq)
  {
    return pq.units();
  }

protected:

  Unit(const std::string & name, const std::string & symbol,
       const std::string & latex_symbol, const std::string & desc,
       const PhysicalQuantity & phy_q, const double min, const double max,
       const double epsilon_ratio = 0.05)
    : UnitItem(name, symbol, latex_symbol, desc), physical_quantity(phy_q),
      min_val(min), max_val(max)
  {
    if (min_val > max_val) {
      std::ostringstream s;
      s << "Unit constructor: minimum value " << min_val
        << " is greater than maximum value " << max_val;
      ZENTHROW(MinMaxReversed, s.str());
    }

    set_epsilon(epsilon_ratio);
    tbl.register_item(this);
    unit_tbl.insert(this);
    const_cast<PhysicalQuantity&>(physical_quantity).unit_list.push_back(this);
  }

  double default_value() const noexcept { return (min_val + max_val)/2; }
};

extern std::string units_json();
using Unit_Convert_Fct_Ptr = double (*)(double);

struct UnitPairEqual
{
  bool operator ()
  (const std::pair<const Unit*, const Unit*> & p1,
   const std::pair<const Unit*, const Unit*> & p2) const noexcept
  {
    return p1 == p2;
  }
};

struct PairHash
{
  template <typename T, typename U>
  std::size_t operator()(const std::pair<T, U> & p) const
  {
    std::size_t seed = 0;
    this->hash_combine(seed, p.first);
    this->hash_combine(seed, p.second);
    return seed;
  }

  template <class T>
  inline void hash_combine(std::size_t & seed, const T & v) const 
  {
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
  }
};


using UnitHashTable = std::unordered_map<std::pair<std::string, std::string>, 
                                         Unit_Convert_Fct_Ptr, PairHash>;

using UnitMap = std::unordered_map<std::pair<const Unit*, const Unit*>, 
                                             Unit_Convert_Fct_Ptr, PairHash>;


#include "compoundunittbl.hpp"

extern UnitMap __unit_map;
extern UnitHashTable __unit_name_name_tbl;
extern UnitHashTable __unit_name_symbol_tbl;
extern UnitHashTable __unit_symbol_name_tbl;
extern UnitHashTable __unit_symbol_symbol_tbl;
extern CompoundUnitTbl __compound_unit_tbl;

template <typename...> struct __always_false : std::false_type {};

inline const Unit * search_compound_unit(const std::string & uname1,
           const std::string & uname2)
{
  return __compound_unit_tbl.search({uname1, uname2});
}

/* Default compound unit meta function */
template <typename ...Units> struct Combine_Units
{
  Combine_Units()
  {
    static_assert(__always_false<Units...>::value,
      "Compound unit not specified");
  } 
};

// this template performs the conversion. In absence of definition the
// compiler falls here and emits an error due to the static_assert
template <class SrcUnit, class TgtUnit> inline
double unit_convert(double /* val */)
{
  static_assert(__always_false<SrcUnit, TgtUnit>::value,
    "No specialization exists!");
  return 0;
}

inline Unit_Convert_Fct_Ptr
search_conversion(const Unit & src, const Unit & tgt)
{
  using UP = std::pair<const Unit*, const Unit*>;
  auto ptr = __unit_map.find(UP(&src, &tgt));
  return ptr == __unit_map.end() ? nullptr : ptr->second;
}

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
    const std::string & src_name = src_instance.name;
    const std::string & tgt_name = tgt_instance.name;
    
    if (search_conversion(src_instance, tgt_instance)) {
      std::ostringstream s;
      s << "Conversion from " << src_name << " to " << tgt_name
        << " does not share the same physical quantities ("
        << src_instance.physical_quantity.name << ", "
        << tgt_instance.physical_quantity.name << ")";
        ZENTHROW(WrongSiblingUnit, s.str());
    }

    if (&src_instance.physical_quantity != &tgt_instance.physical_quantity) {
      std::ostringstream s;
      s << "Conversion from " << src_name << " to " << tgt_name
        << " does not shae the same physical quantities ("
        << src_instance.physical_quantity.name << ", "
        << tgt_instance.physical_quantity.name << ")";
      ZENTHROW(WrongSiblingUnit, s.str());
    }
    
    const std::string & src_symbol = src_instance.symbol;
    const std::string & tgt_symbol = tgt_instance.symbol;


    if (__unit_name_name_tbl.find(std::make_pair(src_name, tgt_name)) != 
          __unit_name_name_tbl.end()) {
      
      std::ostringstream s;
      s << "Conversion from unit name " << src_name << " to unit name "
        << tgt_name << " has already been registered";
      ZENTHROW(UnitConversionNotFound, s.str());
    }

    if (__unit_name_symbol_tbl.find(std::make_pair(src_name, tgt_symbol)) != 
          __unit_name_symbol_tbl.end()) {

      std::ostringstream s;
      s << "Conversion from unit name " << src_name << " to symbol name "
        << tgt_symbol << " has already been registered";
      ZENTHROW(DuplicatedUnitConversion, s.str());
    }

    if (__unit_symbol_name_tbl.find(std::make_pair(src_symbol, tgt_name)) != 
          __unit_symbol_name_tbl.end()) {
 
      std::ostringstream s;
      s << "Conversion from symbol name " << src_symbol << " to unit name "
        << tgt_name << " has already been registered";
      ZENTHROW(DuplicatedUnitConversion, s.str());
    }

    if (__unit_symbol_symbol_tbl.find(std::make_pair(src_symbol, tgt_symbol)) != 
          __unit_symbol_symbol_tbl.end()) {
      std::ostringstream s;
      s << "Conversion from symbol name " << src_symbol << " to symbol name "
        << tgt_symbol << " has already been registered";
      ZENTHROW(DuplicatedUnitConversion, s.str());
    }

    fct_ptr = &UnitConverter::convert;

    __unit_map.insert(std::make_pair(
      std::make_pair(&src_instance, &tgt_instance),fct_ptr));
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

inline bool exist_conversion(const Unit & src, const Unit & tgt)
{
  return search_conversion(src, tgt) != nullptr;
}

inline bool exist_conversion(const std::string & src_symbol,
                             const std::string & tgt_symbol)
{
  const Unit * src_unit = Unit::search_by_symbol(src_symbol);
  if (src_unit == nullptr) {
    return false;
  }

  const Unit * tgt_unit = Unit::search_by_symbol(tgt_symbol);
  if (tgt_unit == nullptr) {
    return false;
  }
  
  return exist_conversion(*src_unit, *tgt_unit);
}

extern bool conversion_exist(const char * src_symbol, const char * tgt_symbol);

inline Unit_Convert_Fct_Ptr search_conversion_fct(const std::string & src_symbol,
              const std::string & tgt_symbol)
{
  const Unit * src_unit = Unit::search_by_symbol(src_symbol);
  if (src_unit == nullptr) return nullptr;

  const Unit * tgt_unit = Unit::search_by_symbol(tgt_symbol);
  if (tgt_unit == nullptr) return nullptr;

  return search_conversion(*src_unit, *tgt_unit);
}

inline double unit_convert(const Unit & src_unit,
         double val,
         const Unit & tgt_unit)
{
  auto fct = search_conversion(src_unit, tgt_unit);
  if (fct == nullptr) {
    std::ostringstream s;
    s << "Conversion from unit name " << src_unit.name << " to unit name "
      << tgt_unit.name << " has not been registered";
    ZENTHROW(UnitConversionNotFound, s.str());
  }
  return (*fct)(val);
}

inline double unit_convert_name_to_name(const std::string & src_name,
                                        double val,
                                        const std::string & tgt_name)
{
  auto p = __unit_name_name_tbl.find(make_pair(src_name, tgt_name));
  if (p == __unit_name_name_tbl.end()) {
    std::ostringstream s;
    s << "Conversion from unit name " << src_name << " to unit name "
      << tgt_name << " has not been registered";
    ZENTHROW(UnitConversionNotFound, s.str());
  }

  auto fct = p->second;
  return (*fct)(val);
}

inline double unit_convert_name_to_symbol(const std::string & src_name,
                                          double val,
                                          const std::string & tgt_symbol)
{
  auto p = __unit_name_symbol_tbl.find(std::make_pair(src_name, tgt_symbol));
  if (p == __unit_name_symbol_tbl.end()) {
    std::ostringstream s;
    s << "Conversion from unit name " << src_name << " to unit symbol "
      << tgt_symbol << " has not been registered";
    ZENTHROW(UnitConversionNotFound, s.str());
  }
  auto fct = p->second;
  return (*fct)(val);
}

inline double unit_convert_symbol_to_name(const std::string & src_symbol,
                                          double val,
                                          const std::string & tgt_name) 
{
  auto p = __unit_symbol_name_tbl.find(make_pair(src_symbol, tgt_name));
  if (p == __unit_symbol_name_tbl.end()) {
    std::ostringstream s;
    s << "Conversion from symbol name " << src_symbol << " to unit name "
      << tgt_name << " has not been registered";
    ZENTHROW(UnitConversionNotFound, s.str());
  }

  auto fct = p->second;
  return (*fct)(val);
}

inline double unit_convert_symbol_to_symbol(const std::string & src_symbol,
                                            double val,
                                            const std::string & tgt_symbol) 
{
  auto p = __unit_symbol_symbol_tbl.find(make_pair(src_symbol, tgt_symbol));
  if (p == __unit_symbol_symbol_tbl.end()) {
    std::ostringstream s;
    s << "Conversion from symbol name " << src_symbol << " to symbool name "
      << tgt_symbol << " has not been registered";
    ZENTHROW(UnitConversionNotFound, s.str());
  }

  auto fct = p->second;
  return (*fct)(val);
}

extern double unit_convert(const char * src_symbol, const char * tgt_symbol,
                           double val);

/** Declare a new unit

    @param[in] __name of unit
    @param[in] symbol of unit
    @param[in] desc description
    @param[in] physical_quantity reference to a previusly defined
    `Physical_Quantity` object associated to the unit
    @param[in] min minimum value of the unit
    @param[in] max maximum value of the unit
*/
#define Declare_Unit(__name, symbol, lsymbol, desc, physical_quantity, min,    \
                     max)                                                      \
  class __name : public Unit                                                   \
  {                                                                            \
    __name()                                                                   \
      : Unit(#__name, symbol, lsymbol, desc,                                   \
             physical_quantity::get_instance(), min, max) {}                   \
                                                                               \
  public:                                                                      \
                                                                               \
    static const __name & get_instance()                                       \
    {                                                                          \
      static __name instance;                                                  \
      return instance;                                                         \
    }                                                                          \
                                                                               \
    __name(const __name&) = delete;                                            \
    void operator = (const __name&) = delete;                                  \
  };                                                                           \
                                                                               \
  extern UnitConverter<__name, __name> __uc__##__name##__to__##__name;         \
  template <> inline double unit_convert<__name, __name>(double val)           \
  { return val; }

#define Declare_Conversion(Unit1, Unit2, val)                                  \
  extern UnitConverter<Unit1, Unit2> __uc__##Unit1##__to__##Unit2;             \
  template <> inline double unit_convert<Unit1, Unit2>(double val)

/** Declare a compound unit; that is a unit composed by two units

    @param[in] __name of compound unit
    @param[in] symbol of unit
    @param[in] desc description
    @param[in] physical_quantity_name reference to the physical
    quantity associated to the new unit
    @param[in] min minimum value of the unit
    @param[in] max maximum value of the unit
    @param[in] Unit1 first unit from left to right 
    @param[in] Unit2 second unit from left to right 
*/
#define Declare_Compound_Unit(__name, symbol, desc, physical_quantity_name,    \
                              min, max, Unit1, Unit2)                          \
  Declare_Unit(__name, symbol, desc, physical_quantity_name, min, max);        \
  template <> struct Combine_Units<Unit1, Unit2>                               \
  {                                                                            \
    using type = __name;                                                       \
                                                                               \
    Combine_Units()                                                            \
    {                                                                          \
      __compound_unit_tbl.insert(                                              \
        {Unit1::get_instance().name, Unit2::get_instance().name},              \
        __name::get_instance());                                               \
    }                                                                          \
                                                                               \
    static const Combine_Units<Unit1, Unit2> __cu_trigger;                     \
  };                                                                           \
  const Combine_Units<Unit1, Unit2> Combine_Units<Unit1, Unit2>::__cu_trigger;

/** Declare a compound unit; that is a unit composed by three units

    @param[in] name of compound unit
    @param[in] symbol of unit
    @param[in] desc description
    @param[in] physical_quantity_name reference to the physical
    quantity associated to the new unit
    @param[in] min minimum value of the unit
    @param[in] max maximum value of the unit
    @param[in] Unit1 first unit from left to right 
    @param[in] Unit2 second unit from left to right 
    @param[in] Unit3 second unit from left to right 
*/
#define Declare_Compound_Unit3(__name, symbol, desc, physical_quantity_name,   \
                               min, max, Unit1, Unit2, Unit3)                  \
  Declare_Unit(__name, symbol, desc, physical_quantity_name, min, max);        \
  template <> struct Combine_Units<Unit1, Unit2, Unit3>                        \
  {                                                                            \
    using type = __name;                                                       \
                                                                               \
    Combine_Units()                                                            \
    {                                                                          \
      __compound_unit_tbl.insert({Unit1::get_instance().name,                  \
                                  Unit2::get_instance().name,                  \
                                  Unit3::get_instance()},                      \
                                 __name::get_instance());                      \
    }                                                                          \
  };

class BaseQuantity
{
 public:

  const Unit & unit;
  
 protected:

  double value;
  BaseQuantity(const Unit & __unit) noexcept 
    : unit(__unit), value(unit.min_val) {}
  
  BaseQuantity(const Unit & __unit, double val) noexcept
    : unit(__unit), value(val) {}

 public:

  static bool is_valid(double value, const Unit & unit) noexcept
  {
    return ((value >= unit.min_val and value <= unit.max_val) or
            fabs(value - unit.min_val) <= unit.get_epsilon()  or
            fabs(value - unit.max_val) <= unit.get_epsilon()  or
            &unit == &Unit::null_unit);
  }

 protected:
  
  // helper for validating that value is in [min_val, max_val]. It
  // throws range_error if value is not in the interval
  void check_value()
  {
    if (is_valid(value, unit)) return;

    std::stringstream s;
    s << "Value (" << value << " " << unit.name
      << ") is not inside in [" << unit.min_val << ", "
      << unit.max_val << "] epsilon = " << unit.get_epsilon()
      << " defined for the unit";
    ZENTHROW(OutOfUnitRange, s.str());
  }

  // throw exception if the units do not share the same physical quantity
  void check_physical_units(const BaseQuantity & q) const
  {
    if ((void*) &unit.physical_quantity == 
          (void*) &(q.unit.physical_quantity)) return;

    std::ostringstream s;
    s << "Units do not refer to the same physical quantities\n"
      << "Source physical quantity = " << unit.physical_quantity.name << "\n"
      << "target physical quantity = " << q.unit.physical_quantity.name;
    ZENTHROW(WrongSiblingUnit, s.str());
  }

  void verify_same_unit(const Unit & __unit) const
  {
    if (&this->unit == &__unit) return;

    std::ostringstream s;
    s << "Different units: " << unit.name << " != " << __unit.name;
    ZENTHROW(DifferentUnits, s.str());
  }

 public:

  inline void increase();
  inline void decrease();

 protected:

  inline BaseQuantity __increase() const
  {
    auto ret = *this;
    ret.increase();
    return ret;
  }

  inline BaseQuantity __decrease() const
  {
    auto ret = *this;
    ret.increase();
    return ret;
  }

public:

  double get_value() const noexcept { return value; }
  double raw() const noexcept { return value; }

      /// Return the stringfied value (the unit symbol is concatenated)
  std::string to_string() const
  {
    std::ostringstream s;
    s << value << " " << unit.symbol;
    return s.str();
  }

  friend std::ostream & operator << (std::ostream & out, const BaseQuantity & q)
  {
    return out << q.to_string();
  }
};

inline double pow(const BaseQuantity & q, const double e)
{
  return pow(q.get_value(), e);
}

inline double pow(const long double b, const BaseQuantity & e)
{
  return pow(b, e.get_value());
}

inline double pow2(const BaseQuantity & q)
{
  return q.raw()*q.raw();
}

inline double powl(const BaseQuantity & q, const long double e)
{
  return powl(q.get_value(), e);
}

inline double powl(const double b, const BaseQuantity & e)
{
  return powl(b, e.get_value());
}

inline double exp(const BaseQuantity & q)
{
  return exp(q.get_value());
}

inline double expl(const BaseQuantity & q)
{
  return expl(q.get_value());
}

inline double log10(const BaseQuantity & q)
{
  return log10(q.get_value());
}

inline double log10l(const BaseQuantity & q)
{
  return log10l(q.get_value());
}

inline double log(const BaseQuantity & q)
{
  return log(q.get_value());
}

inline double logl(const BaseQuantity & q)
{
  return logl(q.get_value());
}

inline double sqrt(const BaseQuantity & q)
{
  return sqrt(q.get_value());
}

inline double sqrtl(const BaseQuantity & q)
{
  return sqrtl(q.get_value());
}

inline double cbrt(const BaseQuantity & q)
{
  return cbrt(q.get_value());
}

inline double cbrtl(const BaseQuantity & q)
{
  return cbrtl(q.get_value());
}

/** Quantity 

 */
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
    if (&q == this) return *this;

    value = q.get_value();
    return *this;
  }

  /// Inter unit constructor. Perform the conversion
  template <class SrcUnit>
  Quantity(const Quantity<SrcUnit> & q)
    : BaseQuantity(UnitName::get_instance()) { assign_converted(q); }

  Quantity next() const { return Quantity(this->__increase()); }

  Quantity prev() const { return Quantity(this->__decrease()); }

  /// Inter unit assignment. Perform the conversion
  template <class SrcUnit>
  Quantity & operator = (const Quantity<SrcUnit> & q)
  {
    if ((void*) &q == (void*) this) return *this;

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

template <class UnitName> inline
Quantity<UnitName> operator + (double lhs, const Quantity<UnitName> & rhs)
{
  return Quantity<UnitName>(lhs + rhs.get_value());
}

template <class UnitName> inline
Quantity<UnitName> operator - (double lhs, const Quantity<UnitName> & rhs)
{
  return Quantity<UnitName>(lhs - rhs.get_value());
}

template <class UnitName> inline
Quantity<UnitName> operator * (double lhs, const Quantity<UnitName> & rhs)
{
  return Quantity<UnitName>(lhs*rhs.get_value());
}

template <class UnitName> inline          
Quantity<UnitName> operator * (const Quantity<UnitName> & lhs, double rhs)
{
  return Quantity<UnitName>(lhs.get_value()*rhs);
}

template <class UnitName> inline
Quantity<UnitName> operator / (double lhs, const Quantity<UnitName> & rhs)
{
  return Quantity<UnitName>(lhs / rhs.get_value());
}

template <class UnitName> inline
Quantity<UnitName> operator / (const Quantity<UnitName> & lhs, double rhs)
{
  return Quantity<UnitName>(lhs.get_value() / rhs);
}

template <class U> inline
bool operator < (double lhs, const Quantity<U> & rhs)
{
  return Quantity<U>(lhs) < rhs;
}

template <class U> inline
bool operator < (const Quantity<U> & lhs, double rhs)
{
  return lhs < Quantity<U>(rhs);
}

template <class U> inline
bool operator <= (const Quantity<U> & lhs, double rhs)
{
  return lhs <= Quantity<U>(rhs);
}

template <class U> inline
bool operator <= (double lhs, const Quantity<U> & rhs)
{
  return Quantity<U>(lhs) <= rhs;
}

template <class U> inline
bool operator > (const Quantity<U> & lhs, double rhs)
{
  return lhs > Quantity<U>(rhs);
}

template <class U> inline
bool operator > (double lhs, const Quantity<U> & rhs)
{
  return Quantity<U>(lhs) > rhs;
}

template <class U> inline
bool operator >= (const Quantity<U> & lhs, double rhs)
{
  return lhs >= Quantity<U>(rhs);
}

template <class U> inline       
bool operator >= (double lhs, const Quantity<U> & rhs) 
{
  return Quantity<U>(lhs) >= rhs;
  }

template <class U> inline
bool operator == (const Quantity<U> & lhs, double rhs)
{
  return lhs == Quantity<U>(rhs);
}

template <class U> inline
bool operator == (double lhs, const Quantity<U> & rhs)
{
  return Quantity<U>(lhs) == rhs;
}

template <class U> inline
bool operator != (const Quantity<U> & lhs, double rhs)
{
  return not (lhs == rhs);
}

template <class U> inline
bool operator != (double lhs, const Quantity<U> & rhs)
{
  return not (lhs == rhs);
}

class VtlQuantity : public BaseQuantity
{
 public:
  
  // return the compund unit corresponding to uname1 x uname2
  static const Unit & verify_compound(const Unit & unit1, const Unit & unit2) 
  {
    auto unit_ptr = search_compound_unit(unit1.name, unit2.name);
    if (unit_ptr != nullptr) return *unit_ptr;
    
    std::ostringstream s;
    s << "There is no compund unit between " << unit1.name << " and "
      << unit2.name;
    ZENTHROW(CompoundUnitNotFound, s.str());
  }

private:

  const Unit & unit_given_name(const std::string & name) const
  {
    auto ptr = Unit::search_by_name(name);
    if (ptr != nullptr) return *ptr;

    std::ostringstream s;
    s << "Nonexistent unit name " << name;
    ZENTHROW(UnitNotFound, s.str());
  }

  const Unit & unit_given_symbol(const std::string & symbol) const
  {
    auto ptr = Unit::search_by_symbol(symbol);
    if (ptr != nullptr) return *ptr;

    std::ostringstream s;
    s << "Nonexistent unit symbol " << symbol;
    ZENTHROW(UnitNotFound, s.str());
  }

public:

  static const VtlQuantity null_quantity;

  bool is_null() const noexcept { return value == Unit::Invalid_Value; }

  void set(const BaseQuantity & q)
  {
    new (this) VtlQuantity(q.unit, q.raw());
  }

  void set(double val, const Unit * unit_ptr)
  {
    new (this) VtlQuantity(*unit_ptr, val);
  }

  VtlQuantity() : BaseQuantity(Unit::null_unit, Unit::Invalid_Value) {}

  VtlQuantity(const std::string & unit_name, double val = 0)
    : BaseQuantity(unit_given_name(unit_name), val)
  {
    check_value();
  }

  VtlQuantity(double val, const std::string & symbol)
    : BaseQuantity(unit_given_symbol(symbol), val)
  {
    check_value();
  }

  VtlQuantity(const Unit & unit, double val) : BaseQuantity(unit, val)
  {
    check_value();
  }

  VtlQuantity(const Unit & unit) : BaseQuantity(unit)
  {
    check_value();
  }

  VtlQuantity(const VtlQuantity & q) noexcept : BaseQuantity(q.unit, q.value) {}

  VtlQuantity next() const { return VtlQuantity(unit, this->__increase()); }

  VtlQuantity prev() const { return VtlQuantity(unit, this->__decrease()); }

  VtlQuantity(const std::string & unit_name, const BaseQuantity & q)
    : BaseQuantity(unit_given_name(unit_name), q.get_value())
  {
    if (&unit == &q.unit) {
      value = q.raw();
    }else {
      value = unit_convert(q.unit, q.get_value(), unit);
    }
    
    check_value();
  }

  VtlQuantity(const Unit & unit, const BaseQuantity & q)
    : BaseQuantity(unit)
  {
    if (&unit == &q.unit){
      value = q.raw();
    }else{
      value = unit_convert(q.unit, q.get_value(), unit);
      check_value();
    }
  }

  VtlQuantity & operator = (const VtlQuantity & q)
  {
    if (this == &q) return *this;

    if (this->is_null()) return * new (this) VtlQuantity(q.unit, q.value);

    if (&unit == &q.unit) {
      value = q.get_value();
      return *this;
    }

    value = unit_convert(q.unit, q.get_value(), unit);
    check_value();
    return *this;
  }

  template <class U>
  VtlQuantity(const Quantity<U> & q) : BaseQuantity(q.unit, q.get_value()) {}

  template <class U>
  VtlQuantity & operator = (const Quantity<Unit> & q)
  {
    if (is_null()) return * new (this) VtlQuantity(q.unit, q.raw());

    if (&unit == &q.unit) {
      value = q.get_value();
      return *this;
    }

    value = unit_convert(q.unit, q.get_value(), unit);
    check_value();
    return *this;
  }

  VtlQuantity & operator += (double rhs)
  {
    value += rhs;
    check_value();
    return *this;
  }

  VtlQuantity & operator -= (double rhs)
  {
    value -= rhs;
    check_value();
    return *this;
  }

  VtlQuantity & operator += (const VtlQuantity & rhs)
  {
    value += rhs.get_value();
    check_value();
    return *this;
  }

  VtlQuantity operator + (const VtlQuantity & rhs) const
  {
    VtlQuantity ret(*this);
    ret += rhs;
    return ret;
  }

  VtlQuantity & operator -= (const VtlQuantity & rhs)
  {
    value -= rhs.get_value();
    check_value();
    return *this;
  }

  VtlQuantity operator - (const VtlQuantity & rhs) const
  {
    VtlQuantity ret(*this);
    ret -= rhs;
    return ret;
  }

  VtlQuantity operator * (const VtlQuantity & rhs) const
  {
    return VtlQuantity(verify_compound(unit, rhs.unit).name,
                       value * rhs.get_value());
  }

  VtlQuantity operator / (const VtlQuantity & rhs) const
  {
    return VtlQuantity(verify_compound(unit, rhs.unit).name,
                       value / rhs.get_value());
  }

  template <class U> VtlQuantity
  operator * (const Quantity<U> & rhs) const
  {
    return VtlQuantity(verify_compound(unit, rhs.unit).name,
                       value * rhs.get_value());
  }

  template <class U> VtlQuantity
  operator / (const Quantity<U> & rhs) const
  {
    return VtlQuantity(verify_compound(unit, rhs.unit).name,
                       value / rhs.get_value());
  }

private:

  VtlQuantity build_tmp(const VtlQuantity & rhs) const
  {
    check_physical_units(rhs);
    VtlQuantity q(unit, rhs); // here conversion is done
    q.check_value();
    return q;
  }

public:

  bool operator < (const VtlQuantity & rhs) const noexcept
  {
    return (&unit == &rhs.unit ?
              value < rhs.value : value < build_tmp(rhs).get_value());
  }    

  bool operator <= (const VtlQuantity & rhs) const noexcept
  {
    return (&unit == &rhs.unit ?
              value <= rhs.value : value <= build_tmp(rhs).get_value());
  }

  bool operator > (const VtlQuantity & rhs) const noexcept
  {
    return (&unit == &rhs.unit ?
              value > rhs.value : value > build_tmp(rhs).get_value());
  }    

  bool operator >= (const VtlQuantity & rhs) const noexcept
  {
    return (&unit == &rhs.unit ?
              value >= rhs.value : value >= build_tmp(rhs).get_value());
  }    

  bool operator == (const VtlQuantity & rhs) const noexcept
  {
    if (&unit == &rhs.unit)
      return value == rhs.value;
    return value == build_tmp(rhs).get_value();

    return (&unit == &rhs.unit ?
              value == rhs.value : value == build_tmp(rhs).get_value());
  }    

  bool operator != (const VtlQuantity & rhs) const noexcept
  {
    return not (*this == rhs);
  }

  bool operator < (double rhs) const noexcept { return value < rhs; }
  bool operator <= (double rhs) const noexcept { return value <= rhs; }
  bool operator > (double rhs) const noexcept { return value > rhs; }
  bool operator >= (double rhs) const noexcept { return value >= rhs; }
  bool operator == (double rhs) const noexcept { return value == rhs; }
  bool operator != (double rhs) const noexcept { return value != rhs; }
};

inline VtlQuantity Unit::max() const noexcept
{
  return VtlQuantity(*this, max_val);
}

inline VtlQuantity Unit::min() const noexcept
{
  return VtlQuantity(*this, min_val);
}

inline void BaseQuantity::increase()
{
  value = nextafter(value, unit.max().raw());
  check_value();
}

inline void BaseQuantity::decrease()
{
  value = nextafter(value, unit.min().raw());
  check_value();
}

inline bool operator < (double lhs, const VtlQuantity & rhs) noexcept
{
  return lhs < rhs.get_value();
}

inline bool operator > (double lhs, const VtlQuantity & rhs) noexcept
{
  return lhs > rhs.get_value();
}

inline bool operator <= (double lhs, const VtlQuantity & rhs) noexcept
{
  return lhs <= rhs.get_value();
}

inline bool operator >= (double lhs, const VtlQuantity & rhs) noexcept
{
  return lhs >= rhs.get_value();
}

inline bool operator == (double lhs, const VtlQuantity & rhs) noexcept
{
  return lhs == rhs.get_value();
}

inline bool operator != (double lhs, const VtlQuantity & rhs) noexcept
{
  return lhs != rhs.get_value();
}

template <class UnitName>
VtlQuantity Quantity<UnitName>::to_VtlQuantity() const
{
  return VtlQuantity(unit, value);
}

template <class UnitName>
Quantity<UnitName>::Quantity(const VtlQuantity & q)
  : BaseQuantity(UnitName::get_instance())
{
  if (&unit == &q.unit) {
    value = q.get_value();
    return;
  }

  value = unit_convert(q.unit, q.get_value(), unit);
  check_value();
}

template <class UnitName>
Quantity<UnitName> & Quantity<UnitName>::operator = (const VtlQuantity & q)
{
  if (&unit == &q.unit) {
    value = q.get_value();
    return *this;
  }
  
  value = unit_convert(q.unit, q.get_value(), unit);
  check_value();
  return *this;
}

template <class UnitName> Quantity<UnitName> &
Quantity<UnitName>::operator += (const VtlQuantity & rhs)
{
  verify_same_unit(rhs.unit);
  value += rhs.get_value();
  check_value();
  return *this;
}

template <class UnitName> Quantity<UnitName> &
Quantity<UnitName>::operator -= (const VtlQuantity & rhs)
{
  verify_same_unit(rhs.unit);
  value -= rhs.get_value();
  check_value();
  return *this;
}

template <class UnitName> VtlQuantity
Quantity<UnitName>::operator + (const VtlQuantity & rhs) const
{
  verify_same_unit(rhs.unit);
  VtlQuantity ret(*this);
  ret += rhs;
  return ret;
}

template <class UnitName> VtlQuantity
Quantity<UnitName>::operator - (const VtlQuantity & rhs) const
{
  verify_same_unit(rhs.unit);
  VtlQuantity ret(*this);
  ret -= rhs;
  return ret;
}

template <class UnitName> VtlQuantity
Quantity<UnitName>::operator * (const VtlQuantity & rhs) const
{
  return VtlQuantity(VtlQuantity::verify_compound(unit, rhs.unit).name,
                     value * rhs.get_value());
}

template <class UnitName> VtlQuantity
Quantity<UnitName>::operator / (const VtlQuantity & rhs) const
{
  return VtlQuantity(VtlQuantity::verify_compound(unit, rhs.unit).name,
                     value / rhs.get_value());
}

inline std::pair<bool, std::vector<std::string>> check_conversions(
    const PhysicalQuantity & pq)
{
  std::vector<std::string> missing;
  auto units = Unit::units(pq);
  
  for (const auto & src_unit : units) {
    for (const auto & tgt_unit : units) {
      if (src_unit == tgt_unit) continue;

      if (not exist_conversion(*src_unit, *tgt_unit)) {
        std::ostringstream s;
        s << "Missing conversion from " << src_unit->name << "("
          << src_unit->symbol << ") to " << tgt_unit->name << "("
          << tgt_unit->symbol << ")";
        missing.push_back(s.str());
      }
    }
  }

  return make_pair(missing.empty(), move(missing));
}

//} // namespace units
//} // namespace ztg

#endif // UNITS_HPP

