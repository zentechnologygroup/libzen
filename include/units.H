/** Units definitions and their conversion library.

    Aleph-w Leandro Rabindranath Leon    
 */

# ifndef UNITS_H
# define UNITS_H

# include <memory>
# include <typeinfo>
# include <type_traits>
# include <string>
# include <sstream>
# include <limits>

# include <tpl_dynSetHash.H>
# include <tpl_dynMapTree.H>

# include "unititem.H"
# include "unit-exceptions.H"

using namespace std;

# define UNIT_INVALID_VALUE (-1000)

class Unit;

/** Instantiate the units system

    @ingroup Units
    @author Leandro Rabindranath Leon
 */
class UnitsInstancer
{
  UnitsInstancer();
public:
  static const UnitsInstancer & init()
  {
    static UnitsInstancer instance;
    return instance;
  }

  UnitsInstancer(const UnitsInstancer&) = delete;
  void operator = (const UnitsInstancer&) = delete;
};

/**
   Initiates unit system.
   
   This function assures that the unit system is adequately instantiated. 

   All the unit system requires some bookkeeping which must be
   previously initialized. An uninitialized unit system could cause
   crash when objects refer to units. In order to avoid that, one
   should be sure that before any unit operation the unit system is
   initialized.

   The best way for assuring initialization is to put the following
   code snippet at the beginning of main program

    # include <units.H>

    auto units_init_ref = init_units();

   You must guarantee that this code is executed before the first
   usage to anything referring units

   @author Leandro Rabindranath Leon
   @ingroup Units
 */
inline const UnitsInstancer & init_units()
{
  return UnitsInstancer::init();
}

/** Physical magnitude

    @author Leandro Rabindranath Leon
    @ingroup Units
 */
class PhysicalQuantity : public UnitItem
{
  friend class Unit;
  friend class UnitsInstancer;

  using UnitItem::UnitItem;

  static UnitItemTable * tbl; // each physical quantity is stored here

  DynList<const Unit *> unit_list; // all the units related to this
				   // are stored here

  PhysicalQuantity() {}

public:

  /// null physical quantity
  static const PhysicalQuantity null_physical_quantity;
  
protected:

  /** Construct a new physical magnitude

      @param[in] name of the physical magnitude
      @param[in] symbol test defining magnitude symbol
      @param[in] latex_symbol the symbol in LaTeX math model
      @param[in] desc test describing the magnitude
 */
  PhysicalQuantity(const string & name,
		   const string & symbol,
		   const string & latex_symbol,
		   const string & desc)
    : UnitItem(name, symbol, latex_symbol, desc)
  {
    assert(tbl != nullptr);
    tbl->register_item(this);
  }

public:

  /// Return a list of pointer to units associated to this physical magnitude
  const DynList<const Unit *> & units() const { return unit_list; }

  /// Return a list of pointer to all defined physical magnitudes  
  static DynList<const PhysicalQuantity*> quantities()
  {
    return tbl->items().maps<const PhysicalQuantity*>([] (auto p)
      {
	return static_cast<const PhysicalQuantity*>(p);
      });
  }

  /// Return a list of names of the all defined physical magnitudes
  static DynList<string> names() { return tbl->names(); }

  static const PhysicalQuantity * search(const string & name)
  {
    assert(tbl != nullptr);
    auto ptr = tbl->search_by_name(name);
    return static_cast<const PhysicalQuantity * const>(ptr);
  }
};

/** Defines a new physical magnitude

    @param[in] name of the new physical quantity
    @param[in] symbol string used as unit symbol
    @param[in] desc description 

    @author Leandro Rabindranath Leon
    @ingroup Units
*/
# define Declare_Physical_Quantity(__name, symbol, lsymbol, desc)	\
  struct __name : public PhysicalQuantity				\
  {									\
									\
    static const __name & get_instance()				\
    {									\
      static __name instance;						\
      return instance;							\
    }									\
									\
  private:								\
									\
    __name() : PhysicalQuantity(#__name, symbol, lsymbol, desc) {}	\
									\
  public:								\
									\
    __name(const __name&) = delete;					\
    void operator = (const __name&) = delete;				\
  };

class VtlQuantity; // forward declaration


/** Unit base class

    This is the base class for the units. Except some static data
    members and methods, it must not be publicly used.

    @author Leandro Rabindranath Leon
    @ingroup Units
 */
class Unit : public UnitItem
{
  friend class UnitsInstancer;

  double epsilon = 1e-6;

public:

  static void validate_ratio(const double ratio)
  {
    if (not (ratio <= 0 or ratio > 0.3))
      return;

    ostringstream s;
    s << "epsilon ratio " << ratio << " is not inside (0, " << ratio << ")";
    ZENTHROW(WrongUnitRatio, s.str());
  }

  static const Unit null_unit; /// Indicates the null unit
  static const double Invalid_Value; /// null unit contains this value

  /// return the epsilon used for tolerance respect min and max limits
  double get_epsilon() const noexcept { return epsilon; }

  /// set the epsilon used for tolerance respect min and max limits
  void set_epsilon(double ratio = 0.01) const
  {
    validate_ratio(ratio);
    const_cast<Unit*>(this)->epsilon = ratio*(max_val - min_val);
  }

  const PhysicalQuantity & physical_quantity; /// the physical magnitude
  const double min_val = 0; /// minimum value as double (without unit)
  const double max_val = 0; /// maximum value as double (without unit)

  inline VtlQuantity min() const noexcept; /// Return minimum allowed value
  inline VtlQuantity max() const noexcept; /// Return maximum allowed value

  /// string representation of the quantity
  string to_string() const
  {
    ostringstream s;
    s << "Unit name         = " << name << endl
      << "symbol            = " << symbol << endl
      << "latex symbol      = " << latex_symbol << endl
      << "physical quantity = " << physical_quantity.name << endl
      << "min               = " << min_val << endl
      << "max               = " << max_val << endl
      << "epsilon           = " << epsilon << "( " << 100*epsilon << " %)";
    return s.str();
  }

  /** Formatted string representation of the quantity

      @param[in] width
      @param[in] left_margin number of spaces to the left
 */
  string to_string(size_t width, size_t left_margin = 0) const
  {
    const string margin = string(left_margin, ' ');
    ostringstream s;
    s << margin << "Unit name         = " << name << endl
      << margin << "symbol            = " << symbol << endl
      << margin << "latex symbol      = " << latex_symbol << endl
      << margin << "description       = "
      << align_text_to_left_except_first(description, width, left_margin + 20)
      << endl
      << margin << "physical quantity = " << physical_quantity.name << endl
      << margin << "min               = " << min_val << endl
      << margin << "max               = " << max_val << endl
      << margin << "epsilon           = " << epsilon
      << "( " << 100*epsilon << " %)";
    return s.str();
  }

  friend ostream & operator << (ostream & out, const Unit & unit)
  {
    return out << unit.to_string();
  }

private:

  static UnitItemTable * tbl; // each unit is registered here
  static DynSetTree<const Unit*> * unit_tbl; // for fast retrieval of
					     // full unit given its pointer

public:

  /// return the number of units
  static size_t size() { return unit_tbl->size(); }

  /// Return a list of all declared and used units
  static DynList<const Unit*> units() { return unit_tbl->keys(); }

  /// return all the units associated to this (including this)
  const DynList<const Unit*> & family_units() const
  {
    return physical_quantity.units();
  }

  /// return all the units associated to this (not including this)
  DynList<const Unit*> sibling_units() const
  {
    return physical_quantity.units().filter([this] (auto ptru)
					    {
					      return ptru != this;
					    });
  }

  /// return `true` if `unit` is sibling of this
  bool is_sibling(const Unit & unit) const noexcept
  {
    return &physical_quantity == &unit.physical_quantity;
  }

  /** Search the unit associated to a name
      
      @param[in] name string containing the unit name
      @return constant pointer to the symbol. If the name is not
      found, then `nullptr` is returned
  */
  static const Unit * search_by_name(const string & symbol)
  {
    assert(tbl != nullptr);
    const UnitItem * ptr = tbl->search_by_name(symbol);
    const Unit * unit_ptr = static_cast<const Unit*>(ptr);
    return unit_ptr;
  }

  /** Search the unit associated to a symbol
      
      @param[in] symbol string containing the unit symbol
      @return constant pointer to the symbol. If the symbol is not
      found, then `nullptr` is returned
  */
  static const Unit * search_by_symbol(const string & symbol)
  {
    assert(tbl != nullptr);
    auto ptr = tbl->search_by_symbol(symbol);
    const Unit * unit_ptr = static_cast<const Unit*>(ptr);
    return unit_ptr;
  }

  /// Search by unit name o symbol
  static const Unit * search(const string & str)
  {
    auto ptr = search_by_name(str);
    return ptr ? ptr : search_by_symbol(str);
  }

  /// Return a list of all the units associated to the physical quantity `pq`
  static const DynList<const Unit*> & units(const PhysicalQuantity & pq)
  {
    return pq.units();
  }

  Unit() : physical_quantity(PhysicalQuantity::null_physical_quantity) {}

protected:

  Unit(const string & name, const string & symbol, const string & latex_symbol,
       const string & desc, const PhysicalQuantity & phy_q,
       const double min, const double max, const double epsilon_ratio = 0.05)
    : UnitItem(name, symbol, latex_symbol, desc), physical_quantity(phy_q),
      min_val(min), max_val(max)
  {
    if (min_val > max_val)
      {
	ostringstream s;
	s << "Unit constructor: minimum value " << min_val
	  << " is greater than maximum value " << max_val;
	ZENTHROW(MinMaxReversed, s.str());
      }

    set_epsilon(epsilon_ratio);

    assert(tbl != nullptr);
    assert(unit_tbl != nullptr);
    assert(not unit_tbl->contains(this));

    tbl->register_item(this);
    unit_tbl->insert(this);
    const_cast<PhysicalQuantity&>(physical_quantity).unit_list.append(this);
  }

public:

  /// Return the magnitude at the center of unit range
  double default_value() const noexcept { return (min_val + max_val)/2; }
};

/** Return a string representing a json describing all registered units

    @author Leandro Rabindranath Leon
    @ingroup Units
 */
extern string units_json();

/** Unit conversion function pointer type

    @author Leandro Rabindranath Leon
    @ingroup Units
 */
using Unit_Convert_Fct_Ptr = double (*)(double);

/** Functor for comparing pair of units. It is used for the hash
    tables containing conversion functions
    
    @author Leandro Rabindranath Leon
    @ingroup Units
 */
struct UnitPairEqual
{
  bool operator ()
  (const pair<pair<const Unit*, const Unit*>, Unit_Convert_Fct_Ptr> & p1,
   const pair<pair<const Unit*, const Unit*>, Unit_Convert_Fct_Ptr> & p2)
    const noexcept
  {
    return p1.first == p2.first;
  }
};

using UnitMap =
  ODhashTable<pair<pair<const Unit*, const Unit*>, Unit_Convert_Fct_Ptr>,
	      UnitPairEqual>;

# include "multiunitmap.H"

/** Hash table mapping pair of unit references to conversion functions.

    @author Leandro Rabindranath Leon
    @ingroup Units
 */
extern UnitMap * __unit_map;

extern CompoundUnitTbl * __compound_unit_tbl;

template <typename...> struct __always_false : std::false_type {};

/** Return a compound unit between `uname1` and `uname2`
   
    @author Leandro Rabindranath Leon
    @ingroup Units
 */
inline const Unit * search_compound_unit(const string & uname1,
					 const string & uname2)
{
  return nullptr; // TODO temporal
  assert(__compound_unit_tbl != nullptr);
  return __compound_unit_tbl->search({uname1, uname2});
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

/** search a conversion function between units

    @param[in] src source unit
    @param[in] tgt target unit
    @return a pointer to the conversion function if this one is found;
    `nullptr` otherwise.
    @author Leandro Rabindranath Leon
    @ingroup Units
 */
inline Unit_Convert_Fct_Ptr
search_conversion(const Unit & src, const Unit & tgt)
{
  assert(__unit_map != nullptr);
  using UP = pair<const Unit*, const Unit*>;
  pair<UP, Unit_Convert_Fct_Ptr> p; p.first = UP(&src, &tgt); // saves copy
  auto ptr = __unit_map->search(p);
  return ptr == nullptr ? nullptr : ptr->second;
}

/** Unit conversion helper

    This class creates a pointer to a conversion function from
    `SrcUnit` to `TgtUnit`

    @author Leandro Rabindranath Leon
    @ingroup Units
 */
template <class SrcUnit, class TgtUnit>
class UnitConverter
{
  Unit_Convert_Fct_Ptr fct_ptr = nullptr;

public:

  /// Create and register an unit conversion converter from `SrcUnit`
  /// to `TgtUnit`
  UnitConverter()
  {
    const Unit & src_instance = SrcUnit::get_instance();
    const Unit & tgt_instance = TgtUnit::get_instance();
    
    fct_ptr = &unit_convert<SrcUnit, TgtUnit>;

    using UP = pair<const Unit*, const Unit*>;
    using P = pair<UP, Unit_Convert_Fct_Ptr>;

    __unit_map->insert(P(UP(&src_instance, &tgt_instance), fct_ptr));

    assert(search_conversion(src_instance, tgt_instance));
  }

  /// return the conversion function pointer
  Unit_Convert_Fct_Ptr operator () () const noexcept { return fct_ptr; }
};

/** Return `true` if it exists conversion from `src` unit to `tgt` unit

    @ingroup Units
 */
inline bool exist_conversion(const Unit & src, const Unit & tgt)
{
  return search_conversion(src, tgt) != nullptr;
}

/** Return `true` if it exists conversion from `src_symbol` unit to
    `tgt_symbol` unit

    Both parameters are string corresponding to unit symbols

    @author Leandro Rabindranath Leon
    @ingroup Units
 */
inline bool exist_conversion(const string & src_symbol,
			     const string & tgt_symbol)
{
  const Unit * src_unit = Unit::search_by_symbol(src_symbol);
  if (src_unit == nullptr)
    return false;

  const Unit * tgt_unit = Unit::search_by_symbol(tgt_symbol);
  if (tgt_unit == nullptr)
    return false;
  
  return exist_conversion(*src_unit, *tgt_unit);
}

extern bool
conversion_exist(const char * src_symbol, const char * tgt_symbol);


/** Return a pointer to conversion function from `src_symbol` unit to
    `tgt_symbol` unit. If the conversion does not exist, then returns
    `nullptr`

    Both parameters are string corresponding to unit symbols

    @author Leandro Rabindranath Leon
    @ingroup Units
 */
inline Unit_Convert_Fct_Ptr search_conversion_fct(const string & src_symbol,
						  const string & tgt_symbol)
{
  const Unit * src_unit = Unit::search_by_symbol(src_symbol);
  if (src_unit == nullptr)
    return nullptr;

  const Unit * tgt_unit = Unit::search_by_symbol(tgt_symbol);
  if (tgt_unit == nullptr)
    return nullptr;

  return search_conversion(*src_unit, *tgt_unit);
}

/** Convert `val` expressed in `src_unit` to `tgt_unit`

    @note for performance reasons, conversion involving the same unit
    does not exist. So, this function fails if it is called using the
    same unit
    @Param[in] src_unit source unit
    @param[in] val value to be converted
    @param[in] tgt_unit target unit
    @return `val` in `tgt_unit`
    @exception UnitConversionNotFound if there conversion does not exist
    @author Leandro Rabindranath Leon
    @ingroup Units
 */
inline double unit_convert(const Unit & src_unit,
			   double val,
			   const Unit & tgt_unit)
{
  auto fct = search_conversion(src_unit, tgt_unit);
  if (fct == nullptr)
    {
      ostringstream s;
      s << "Conversion from unit name " << src_unit.name << " to unit name "
	<< tgt_unit.name << " has not been registered";
      ZENTHROW(UnitConversionNotFound, s.str());
    }

  return (*fct)(val);
}

/** Convert a container of doubles expressed in `src_unit` to their
    corresponding values expressed in `tgt_unit`.

    `c` could be any Aleph-w container type: list, array, tree. The
    result is returned in a new container whose type is the same of `c`

    Example:

        Array<double> temp_values = // some values in Fahrenheit
	Array<double> temp_celsius = unit_convert(Fahrenheit::get_instance, 
                                                  temp_values,
                                                  Celsius::get_instance());
						  
    @author Leandro Rabindranath Leon
    @ingroup Units
*/
template <class C> inline C
unit_convert(const Unit & src_unit, const C & c, const Unit & tgt_unit)
{
  if (&src_unit == &tgt_unit)
    return c;

  auto fct = search_conversion(src_unit, tgt_unit);
  if (fct == nullptr)
    {
      ostringstream s;
      s << "Conversion from unit name " << src_unit.name << " to unit name "
	<< tgt_unit.name << " has not been registered";
      ZENTHROW(UnitConversionNotFound, s.str());
    }
  
  C ret;
  for (auto it = c.get_it(); it.has_curr(); it.next())
    ret.append((*fct)(it.get_curr()));
  return ret;
}

/** Transform the doubles stored in container `c` and expressed in
    `src_unit` to their corresponding values expressed in `tgt_unit`.

    `c` could be any Aleph-w container type: list, array, tree. The
    result is returned in a new container whose type is the same of `c`

    Example:

        Array<double> temp_values = // some values in Fahrenheit
	Array<double> temp_celsius = unit_convert(Fahrenheit::get_instance, 
                                                  temp_values,
                                                  Celsius::get_instance());

    @author Leandro Rabindranath Leon
    @ingroup Units
*/
template <class C> inline void
mutable_unit_convert(const Unit & src_unit, C & c, const Unit & tgt_unit)
{
  if (&src_unit == &tgt_unit)
    return;

  auto fct = search_conversion(src_unit, tgt_unit);
  if (fct == nullptr)
    {
      ostringstream s;
      s << "Conversion from unit name " << src_unit.name << " to unit name "
	<< tgt_unit.name << " has not been registered";
      ZENTHROW(UnitConversionNotFound, s.str());
    }
  
  c.mutable_for_each([fct] (double & v) { v = (*fct)(v); });
}

/** Convert the double `val` represented in the unit with name
    `src_name` to the unit with name `tgt_name'.

    Since this function requires three searches to three different
    hash tables, it is considerably slower than `unit_convert()`

    @author Leandro Rabindranath Leon
    @ingroup Units
 */
inline double unit_convert_name_to_name(const string & src_name,
					double val,
					const string & tgt_name)
{
  auto src_unit_ptr = Unit::search_by_name(src_name);
  if (src_unit_ptr == nullptr)
    ZENTHROW(UnitNotFound, "unit name " + src_name + " not found");
  
  auto tgt_unit_ptr = Unit::search_by_name(tgt_name);
  if (tgt_unit_ptr == nullptr)
    ZENTHROW(UnitNotFound, "unit name " + tgt_name + " not found");
  
  auto fct = search_conversion(*src_unit_ptr, *tgt_unit_ptr);
  if (fct == nullptr)
    {
      ostringstream s;
      s << "Conversion from unit name " << src_name << " to unit name "
	<< tgt_name << " has not been registered";
      ZENTHROW(UnitConversionNotFound, s.str());
    }

  return (*fct)(val);
}

/** Convert the double `val` represented in the unit whose symbol is
    `src_symbol` to the unit whose symbol is `tgt_symbol'.

    Since this function requires three searches to three different
    hash tables, it is considerably slower than `unit_convert()`

    @author Leandro Rabindranath Leon
    @ingroup Units
 */
inline double unit_convert_symbol_to_symbol(const string & src_symbol,
					    double val,
					    const string & tgt_symbol)
{
  auto src_unit_ptr = Unit::search_by_symbol(src_symbol);
  if (src_unit_ptr == nullptr)
    ZENTHROW(UnitNotFound, "unit symbol " + src_symbol + " not found");
  
  auto tgt_unit_ptr = Unit::search_by_symbol(tgt_symbol);
  if (tgt_unit_ptr == nullptr)
    ZENTHROW(UnitNotFound, "unit symbol " + tgt_symbol + " not found");
  
  auto fct = search_conversion(*src_unit_ptr, *tgt_unit_ptr);
  if (fct == nullptr)
    {
      ostringstream s;
      s << "Conversion from unit symbol " << src_symbol << " to unit symbol "
	<< tgt_symbol << " has not been registered";
      ZENTHROW(UnitConversionNotFound, s.str());
    }

  return (*fct)(val);
}

extern double unit_convert(const char * src_symbol, const char * tgt_symbol,
			   double val);

/** Declare a new unit

    This macro should be the ideal way for declaring a new unit. It
    creates the unit and prepares all the terrain for conversions
    specific cations. 

    @param[in] __name of unit
    @param[in] symbol of unit
    @param[in] desc description
    @param[in] physical_quantity reference to a previusly defined
    `Physical_Quantity` object associated to the unit
    @param[in] min minimum value of the unit
    @param[in] max maximum value of the unit

    @author Leandro Rabindranath Leon
    @ingroup Units
*/
# define Declare_Unit(__name, symbol, lsymbol, desc, physical_quantity, \
		      min, max)						\
  class __name : public Unit						\
  {									\
    __name() : Unit(#__name, symbol, lsymbol, desc,			\
		    physical_quantity::get_instance(), min, max) {}	\
									\
  public:								\
									\
    static const __name & get_instance()				\
    {									\
      static __name instance;						\
      return instance;							\
    }									\
									\
    __name(const __name&) = delete;					\
    void operator = (const __name&) = delete;				\
  };									\
									\
  extern UnitConverter<__name, __name> __uc__##__name##__to__##__name;	\
  template <> inline double unit_convert<__name, __name>(double val)	\
  { return val; }

/** Define a conversion from `Unit1` to `Unit2`

    This macro is a partial declaration. The invoker must imperatively
    provide the implementation between {}.

    Example: conversion from Celsius to Fahrenheit could be done as
    follows:

        Declare_Conversion(Celsius, Fahrenheit, t) { return 1.8 * t + 32; }

    @param[in] Unit1 class name of source unit
    @param[in] Unit2 class name of target unit
    @param[in] val name of a double parameter containing the value to
    be converted

    @author Leandro Rabindranath Leon
    @ingroup Units
 */
# define Declare_Conversion(Unit1, Unit2, val)		    \
  extern UnitConverter<Unit1, Unit2> __uc__##Unit1##__to__##Unit2;	\
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

    @author Leandro Rabindranath Leon
    @ingroup Units
*/
# define Declare_Compound_Unit(__name, symbol, desc, physical_quantity_name, \
			       min, max, Unit1, Unit2)			\
  Declare_Unit(__name, symbol, desc, physical_quantity_name, min, max);	\
  template <> struct Combine_Units<Unit1, Unit2>			\
  {									\
    using type = __name;						\
    Combine_Units()							\
      {									\
	__compound_unit_tbl->insert({Unit1::get_instance().name,	\
	      Unit2::get_instance().name}, __name::get_instance());	\
      }									\
    static const Combine_Units<Unit1, Unit2> __cu_trigger;		\
  };									\
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

    @author Leandro Rabindranath Leon
    @ingroup Units
*/
# define Declare_Compound_Unit3(__name, symbol, desc, physical_quantity_name, \
				min, max, Unit1, Unit2, Unit3)		\
  Declare_Unit(__name, symbol, desc, physical_quantity_name, min, max);	\
  template <> struct Combine_Units<Unit1, Unit2, Unit3>			\
  {									\
    using type = __name;						\
    Combine_Units()							\
      {									\
	__compound_unit_tbl->insert({Unit1::get_instance().name,	\
	      Unit2::get_instance().name, Unit3::get_instance()},	\
	  __name::get_instance());					\
      }									\
  };

/** Base class for quantities.

    A quantity con be seen as a pair composed by a numerical value and
    its unit.

    Excepting for some helper static and instance methods, this class
    must not be used. 

    @author Leandro Rabindranath Leon
    @see Quntity, VtlQuantity
    @ingroup Units
 */
class BaseQuantity
{
public:

  const Unit & unit; /// the unit; always visible from any quantity
  
protected:

  double value;

  BaseQuantity(const Unit & __unit) noexcept
    : unit(__unit), value(unit.default_value()) {}
  
  BaseQuantity(const Unit & __unit, double val) noexcept
    : unit(__unit), value(val) {}

public:

  /// helper function which returns `true` if `value` is inside of
  /// `unit` range; `false` otherwise
  static bool is_valid(double value, const Unit & unit) noexcept
  {
    const double & vmin = unit.min_val, & vmax = unit.max_val;
    if (value >= vmin and value <= vmax)
      return true;

    if (value <= UNIT_INVALID_VALUE)
      return false;

    const double & epsilon = unit.get_epsilon();
    if (value < vmin - epsilon or value > vmax + epsilon)
      return false;

    if (value >= vmin - epsilon and value <= vmax + epsilon)
      return true;

    if (&unit == &Unit::null_unit)
      return true;

    return false;
  }

protected:
  
  /// helper for validating that value is in [min_val, max_val]. It
  /// throws range_error if value is not in the interval
  void check_value()
  {
    if (is_valid(value, unit))
      return;

    ostringstream s;
    s << "Value (" << value << " " << unit.name
      << ") is not inside in [" << unit.min_val << ", "
      << unit.max_val << "] epsilon = " << unit.get_epsilon()
      << " defined for the unit";
    ZENTHROW(OutOfUnitRange, s.str());
  }

  /// throw exception if the unit does not share the same physical quantity
  void check_physical_units(const BaseQuantity & q) const
  {
    if ((void*) &unit.physical_quantity == (void*) &(q.unit.physical_quantity))
      return;

    ostringstream s;
    s << "Unit does not refer to the same physical quantity" << endl
      << "Source physical quantity = " << unit.physical_quantity.name << endl
      << "target physical quantity = " << q.unit.physical_quantity.name;
    ZENTHROW(WrongSiblingUnit, s.str());
  }

  void verify_same_unit(const Unit & __unit) const
  {
    if (&this->unit == &__unit)
      return;

    ostringstream s;
    s << "Different units: " << unit.name << " != " << __unit.name;
    ZENTHROW(DifferentUnits, s.str());
  }

public:

  /// Increase the value corresponding to the next representable value
  inline void increase();

  /// Decrease the value corresponding to the previous representable value
  inline void decrease();

protected:

  /// Return the next representable value to this
  inline BaseQuantity __increase() const
  {
    auto ret = *this;
    ret.increase();
    return ret;
  }

  /// Return the previous representable value to this
  inline BaseQuantity __decrease() const
  {
    auto ret = *this;
    ret.increase();
    return ret;
  }

public:

  /// Return `true` if this corresponds to null quantity
  bool is_null() const noexcept { return value == Unit::Invalid_Value; }

  /// Return the double corresponding to the quantity
  double get_value() const noexcept { return value; }

    /// Return the double corresponding to the quantity
  double raw() const noexcept { return value; }

      /// Return the stringfied value (the unit symbol is concatenated)
  string to_string() const
  {
    ostringstream s;
    s << value << " " << unit.symbol;
    return s.str();
  }

  friend ostream & operator << (ostream & out, const BaseQuantity & q)
  {
    return out << q.to_string();
  }
};

/** Force val to be inside the unit limits 

    @author Leandro Rabindranath Leon
    @ingroup Units 
 */ 
inline double bind_to_unit_limits(double val, const Unit & unit) 
{ 
  if (val < unit.min_val) 
    val = unit.min_val; 
  else if (val > unit.max_val) 
    val = unit.max_val; 
  return val; 
} 

/** Return a double corresponding to quantity `q` raised to power of double `e`

    @author Leandro Rabindranath Leon
   @ingroup Units
 */
inline double pow(const BaseQuantity & q, const double e)
{
  return pow(q.get_value(), e);
}

/** Return a double corresponding to double b raised to power of quantity `e`

    @author Leandro Rabindranath Leon
    @ingroup Units
 */
inline double pow(const long double b, const BaseQuantity & e)
{
  return pow(b, e.get_value());
}

/** Return a double corresponding to quantity b raised to two

    @author Leandro Rabindranath Leon
    @ingroup Units
 */
inline double pow2(const BaseQuantity & q)
{
  return q.raw()*q.raw();
}

/** Return a double corresponding to quantity b raised to three

    @author Leandro Rabindranath Leon
    @ingroup Units
 */
inline double pow3(const BaseQuantity & q)
{
  return q.raw()*pow2(q);
}

/** Return a double corresponding to quantity q raised to power of
    long double `e`

    @author Leandro Rabindranath Leon
    @ingroup Units
 */
inline double powl(const BaseQuantity & q, const long double e)
{
  return powl(q.get_value(), e);
}

/** Return a double corresponding to double b raised to power of quantity `e`

    @author Leandro Rabindranath Leon
    @ingroup Units
 */
inline double powl(const long double b, const BaseQuantity & e)
{
  return powl(b, e.get_value());
}

/** Return a double corresponding to e (Euler constant or number of Neper, base of
    natural logarithm) raised to quantity `q`

    @author Leandro Rabindranath Leon
    @ingroup Units
 */
inline double exp(const BaseQuantity & q)
{
  return exp(q.get_value());
}

/** Return a long double corresponding to e (Euler constant or number
    of Neper, base of natural logarithm) raised to quantity `q`

    @author Leandro Rabindranath Leon
    @ingroup Units
 */
inline long double expl(const BaseQuantity & q)
{
  return expl(q.get_value());
}

/** Return a double corresponding to the base 10 logarithm of quantity `q`

    @author Leandro Rabindranath Leon
    @ingroup Units
 */
inline double log10(const BaseQuantity & q)
{
  return log10(q.get_value());
}

/** Return a long double corresponding to the base 10 logarithm of quantity `q`

    @author Leandro Rabindranath Leon
    @ingroup Units
 */
inline long double log10l(const BaseQuantity & q)
{
  return log10l(q.get_value());
}

/** Return a double corresponding to the natural logarithm of quantity `q`

    @author Leandro Rabindranath Leon
    @ingroup Units
 */
inline double log(const BaseQuantity & q)
{
  return log(q.get_value());
}

/** Return a double corresponding to the natural logarithm of quantity `q`

    @author Leandro Rabindranath Leon
    @ingroup Units
 */
inline long double logl(const BaseQuantity & q)
{
  return logl(q.get_value());
}

/** Return a double corresponding to the square root of quantity `q`

    @author Leandro Rabindranath Leon
    @ingroup Units
 */
inline double sqrt(const BaseQuantity & q)
{
  return sqrt(q.get_value());
}

/** Return a long double corresponding to the square root of quantity `q`

    @author Leandro Rabindranath Leon
    @ingroup Units
 */
inline double sqrtl(const BaseQuantity & q)
{
  return sqrtl(q.get_value());
}

/** Return a long double corresponding to the cosine of quantity `q`

    @author Leandro Rabindranath Leon
    @ingroup Units
 */
inline double sin(const BaseQuantity & q)
{
  return sin(q.raw());
}

/** Return a long double corresponding to the cosine of quantity `q`

    @author Leandro Rabindranath Leon
    @ingroup Units
 */
inline double cos(const BaseQuantity & q)
{
  return cos(q.raw());
}

/** Return a double corresponding to the cubic root of quantity `q` 

    @author Leandro Rabindranath Leon
    @ingroup Units
 */
inline double cbrt(const BaseQuantity & q)
{
  return cbrt(q.get_value());
}

/** Return a long double corresponding to the cubic root of quantity `q` 

    @author Leandro Rabindranath Leon
    @ingroup Units
 */
inline double cbrtl(const BaseQuantity & q)
{
  return cbrtl(q.get_value());
}

/** Quantity class

    A Quantity object is a double value whose unit type is defined as
    template parameter in compiling time.

    The operations on Quantity object automatically perform the
    conversion when different units are involved.

    @author Leandro Rabindranath Leon
    @ingroup Units
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

  void assign_converted(const Quantity<UnitName> &) {}

public:

  /// Return a VtlQuantity equivalent to this
  VtlQuantity to_VtlQuantity() const;

  /// Construct a quantity with value `val`
  Quantity(double val) : BaseQuantity(UnitName::get_instance(), val)
  {
    check_value(); // value must be inside the specified range
  }

  /// Construct a quantity set to the middle value of unit range
  Quantity() : BaseQuantity(UnitName::get_instance())
  {
    check_value(); // value must be inside the specified range
  }

  /// direct copy constructor
  Quantity(const Quantity & q) noexcept : BaseQuantity(q.unit, q.get_value()) {}

  /// direct copy assignment 
  Quantity & operator = (const Quantity & q) noexcept
  {
    if (&q == this)
      return *this;

    value = q.get_value();

    return *this;
  }

  /// Inter unit constructor. Perform the conversion
  template <class SrcUnit>
  Quantity(const Quantity<SrcUnit> & q) : BaseQuantity(UnitName::get_instance())
  {
    assign_converted(q);
  }

  /// Return a new quantity with the next representable value
  Quantity next() const { return Quantity(this->__increase()); }

  /// Return a new quantity with previous representable value
  Quantity prev() const { return Quantity(this->__decrease()); }

  /// Inter unit assignment. Perform the conversion
  template <class SrcUnit>
  Quantity & operator = (const Quantity<SrcUnit> & q)
  {
    if ((void*) &q == (void*) this)
      return *this;

    assign_converted(q);

    return *this;
  }

  /** Construct a Quantity object from a VtlQuantity `q`. 

      @param[in] q the VtlQuantity object from the new object will be build
      @exception UnitNotfound if there is no conversion 
   */
  inline Quantity(const VtlQuantity & q);

  /** Assign to this a VtlQuantity `q`. 

      @param[in] q the VtlQuantity object from the new object will be build
       @exception UnitNotfound if there is no conversion 
   */
  inline Quantity & operator = (const VtlQuantity & q);

  /// Sum `rhs` to this. Conversion could be performed and result is validated
  Quantity & operator += (const Quantity & rhs) 
  {
    value += rhs.get_value();
    check_value();
    return *this;
  }

  /// Return this plus `rhs`. Conversion could be performed and result is validated
  Quantity operator + (const Quantity & rhs) const
  {
    Quantity ret(*this);
    ret += rhs;
    return ret;
  }

  /// Subtract `rhs` to this. Conversion could be performed and result is validated
  Quantity & operator -= (const Quantity & rhs)
  {
    value -= rhs.get_value();
    check_value();
    return *this;
  }

  /// Return this minus `rhs`. Conversion could be performed and result is validated
  Quantity operator - (const Quantity & rhs) const
  {
    Quantity ret(*this);
    ret -= rhs;
    return ret;
  }

  /** Return this times `rhs`. Conversion could be performed and
      result is validated and converted to corresponding compound
      unit. 

      @exception UnitNotfound if the compound unit does not exist
  */
  template <class U>
  Quantity<typename Combine_Units<UnitName, U>::type>
  operator * (const Quantity<U> & rhs) const
  {
    using T = typename Combine_Units<UnitName, U>::type;
    return Quantity<T>(value * rhs.get_value());
  }

  /** Return this divided by `rhs`. Conversion could be performed and
      result is validated and converted to corresponding compound
      unit. 

      @exception UnitNotfound if the compound unit does not exist
  */
  template <class U>
  Quantity<typename Combine_Units<UnitName, U>::type>
  operator / (const Quantity<U> & rhs) const
  {
    using T = typename Combine_Units<UnitName, U>::type;
    return Quantity<T>(value / rhs.get_value());
  }

  /** Less than comparison between this and `rhs`.

      The right operand is converted to this' unit then the comparison
      is done.

      @exception UnitNotfound if there is no conversion from
      `rhs.unit` to `this->unit`
 */
  template <class U>
  bool operator < (const Quantity<U> & rhs) const
  {
    Quantity r = { rhs }; // here the conversion is done
    return value < r.get_value();
  }

  /** Less or equal than comparison between this and `rhs`.

      The right operand is converted to this' unit then the comparison
      is done.

      @exception UnitNotfound if there is no conversion from
      `rhs.unit` to `this->unit`
 */
  template <class U>
  bool operator <= (const Quantity<U> & rhs) const
  {
    Quantity r = { rhs }; // here the conversion is done
    return value <= r.get_value();
  }

  /** Greater than comparison between this and `rhs`.

      The right operand is converted to this' unit then the comparison
      is done.

      @exception UnitNotfound if there is no conversion from
      `rhs.unit` to `this->unit`
 */
  template <class U>
  bool operator > (const Quantity<U> & rhs) const
  {
    Quantity r = { rhs }; // here the conversion is done
    return value > r.get_value();
  }

  /** Greater or equal than comparison between this and `rhs`.

      The right operand is converted to this' unit then the comparison
      is done.

      @exception UnitNotfound if there is no conversion from
      `rhs.unit` to `this->unit`
  */
  template <class U>
  bool operator >= (const Quantity<U> & rhs) const
  {
    Quantity r = { rhs }; // here the conversion is done
    return value >= r.get_value();
  }

  /** Equal than comparison between this and `rhs`.

      The right operand is converted to this' unit then the comparison
      is done.

      @exception UnitNotfound if there is no conversion from
      `rhs.unit` to `this->unit`
  */
  template <class U>
  bool operator == (const Quantity<U> & rhs) const
  {
    Quantity r = { rhs }; // here the conversion is done
    return value == r.get_value();
  }

   /** Near than comparison between this and `rhs`.

      The right operand is converted to this' unit then the comparison
      is done.

      @exception UnitNotfound if there is no conversion from
      `rhs.unit` to `this->unit`
  */
  template <class U>
  bool is_near(const Quantity<U> & rhs, double e) const
  {
    Quantity r = { rhs }; // here the conversion is done
    return fabs(value - r.get_value()) <= e;
  }

  bool is_near(double rhs, double e) const 
  { 
    return fabs(value - rhs) <= e; 
  } 

  /** Not equal than comparison between this and `rhs`.

      The right operand is converted to this' unit then the comparison
      is done.

      @exception UnitNotfound if there is no conversion from
      `rhs.unit` to `this->unit`
  */
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

  /// Sum VtlQuantity `rhs` to `this`. Conversion could be performed and
  /// result is validated
  inline Quantity & operator += (const VtlQuantity & rhs) const;

  /// Subtract VtlQuantity `rhs` to `this`. Conversion could be
  /// performed and result is validated
  inline Quantity & operator -= (const VtlQuantity & rhs) const;

  /// Return this plus the Vtlquantity `rhs`. Conversion could be
  /// performed and result is validated and converted to a VtlQuantity
  inline VtlQuantity operator + (const VtlQuantity & rhs) const;

  /// Return this minus the Vtlquantity `rhs`. Conversion could be
  /// performed and result is validated and converted to a VtlQuantity
  inline VtlQuantity operator - (const VtlQuantity & rhs) const;

  /// Return this times the Vtlquantity `rhs`. Conversion could be
  /// performed and result is validated and converted to a VtlQuantity
  inline VtlQuantity  operator * (const VtlQuantity &) const;
  
  /// Return this divided by the Vtlquantity `rhs`. Conversion could
  /// be performed and result is validated and converted to a
  /// VtlQuantity
  inline VtlQuantity  operator / (const VtlQuantity &) const;
};

/* Return the sum of a double plus a quantity `rhs`. The result is a
   Quantity with the same unit than `rhs.unit`

   @author Leandro Rabindranath Leon
   @ingroup Units
 */
template <class UnitName> inline
Quantity<UnitName> operator + (double lhs, const Quantity<UnitName> & rhs)
{
  return Quantity<UnitName>(lhs + rhs.get_value());
}

/* Return the subtraction of a double minus a quantity `rhs`. The
   result is a Quantity with the same unit than `rhs.unit`
   
   @author Leandro Rabindranath Leon
   @ingroup Units
 */
template <class UnitName> inline
Quantity<UnitName> operator - (double lhs, const Quantity<UnitName> & rhs)
{
  return Quantity<UnitName>(lhs - rhs.get_value());
}

/* Return the product of a double times a quantity `rhs`. The result is a
   Quantity with the same unit than `rhs.unit`

   @author Leandro Rabindranath Leon
   @ingroup Units
 */
template <class UnitName> inline
Quantity<UnitName> operator * (double lhs, const Quantity<UnitName> & rhs)
{
  return Quantity<UnitName>(lhs*rhs.get_value());
}

/* Return the product of a quantity times a double `rhs`. The result is a
   Quantity with the same unit than `rhs.unit`

   @author Leandro Rabindranath Leon
   @ingroup Units
 */
template <class UnitName> inline					
Quantity<UnitName> operator * (const Quantity<UnitName> & lhs, double rhs)
{
  return Quantity<UnitName>(lhs.get_value()*rhs);
}

/* Return the division of a double by a quantity `rhs`. The result is a
   Quantity with the same unit than `rhs.unit`

   @author Leandro Rabindranath Leon
   @ingroup Units
 */
template <class UnitName> inline
Quantity<UnitName> operator / (double lhs, const Quantity<UnitName> & rhs)
{
  return Quantity<UnitName>(lhs / rhs.get_value());
}

/* Return the division of a quantity by a double `rhs`. The result is a
   Quantity with the same unit than `rhs.unit`

   @author Leandro Rabindranath Leon
   @ingroup Units
 */
template <class UnitName> inline
Quantity<UnitName> operator / (const Quantity<UnitName> & lhs, double rhs)
{
  return Quantity<UnitName>(lhs.get_value() / rhs);
}

/* Less than comparison between a double and a quantity

   @author Leandro Rabindranath Leon
   @ingroup Units
 */
template <class U> inline
bool operator < (double lhs, const Quantity<U> & rhs)
{
  return Quantity<U>(lhs) < rhs;
}

/* Less than comparison between a quantity and a double

   @author Leandro Rabindranath Leon
   @ingroup Units
 */
template <class U> inline
bool operator < (const Quantity<U> & lhs, double rhs)
{
  return lhs < Quantity<U>(rhs);
}

/* Less or equal than comparison between a double and a quantity

   @author Leandro Rabindranath Leon
   @ingroup Units
 */
template <class U> inline
bool operator <= (const Quantity<U> & lhs, double rhs)
{
  return lhs <= Quantity<U>(rhs);
}

/* Less or equal than comparison between a quantity and a double

   @author Leandro Rabindranath Leon
   @ingroup Units
 */
template <class U> inline
bool operator <= (double lhs, const Quantity<U> & rhs)
{
  return Quantity<U>(lhs) <= rhs;
}

/* Greater than comparison between a double and a quantity

   @author Leandro Rabindranath Leon
   @ingroup Units
 */
template <class U> inline
bool operator > (const Quantity<U> & lhs, double rhs)
{
  return lhs > Quantity<U>(rhs);
}

/* Greater than comparison between a quantity and a double

   @author Leandro Rabindranath Leon
   @ingroup Units
 */
template <class U> inline
bool operator > (double lhs, const Quantity<U> & rhs)
{
  return Quantity<U>(lhs) > rhs;
}

/* Greater or equal than comparison between a double and a quantity
   
   @author Leandro Rabindranath Leon
   @ingroup Units
 */
template <class U> inline
bool operator >= (const Quantity<U> & lhs, double rhs)
{
  return lhs >= Quantity<U>(rhs);
}

/* Greater or equal than comparison between a quantity and a double

   @author Leandro Rabindranath Leon
   @ingroup Units
 */
template <class U> inline				
bool operator >= (double lhs, const Quantity<U> & rhs) 
{
  return Quantity<U>(lhs) >= rhs;
}

/* Equal comparison between a quantity and a double

   @author Leandro Rabindranath Leon
   @ingroup Units
 */
template <class U> inline
bool operator == (const Quantity<U> & lhs, double rhs)
{
  return lhs == Quantity<U>(rhs);
}

/* Equal comparison between a double and a quantity

   @author Leandro Rabindranath Leon
   @ingroup Units
 */
template <class U> inline
bool operator == (double lhs, const Quantity<U> & rhs)
{
  return Quantity<U>(lhs) == rhs;
}

/* Not equal comparison between a quantity and a double

   @author Leandro Rabindranath Leon
   @ingroup Units
 */
template <class U> inline
bool operator != (const Quantity<U> & lhs, double rhs)
{
  return not (lhs == rhs);
}

/* Not equal comparison between a double and a quantity

   @author Leandro Rabindranath Leon
   @ingroup Units
 */
template <class U> inline
bool operator != (double lhs, const Quantity<U> & rhs)
{
  return not (lhs == rhs);
}

/* Virtual quantity.

   A virtual quantity is a pair compounded by a double and an
   unit. The difference with Quantity type is that a VtlQuantity knows
   its unit in run time. 

   @author Leandro Rabindranath Leon
   @ingroup Units
 */
class VtlQuantity : public BaseQuantity
{
public:
  
  /// return the compund unit corresponding to uname1 x uname2
  static const Unit & verify_compound(const Unit & unit1, const Unit & unit2) 
  {
    // auto unit_ptr = search_compound_unit(unit1.name, unit2.name);
    // if (unit_ptr != nullptr)
    //   return *unit_ptr;
    // TODO: disabled 
    ostringstream s;
    s << "There is no compund unit between " << unit1.name << " and "
      << unit2.name;
    ZENTHROW(CompoundUnitNotFound, s.str());
  }

private:

  // Helper functions for searching

  const Unit & unit_given_name(const string & name) const
  {
    auto ptr = Unit::search_by_name(name);
    if (ptr != nullptr)
      return *ptr;

    ostringstream s;
    s << "Nonexistent unit name " << name;
    ZENTHROW(UnitNotFound, s.str());
  }

  const Unit & unit_given_symbol(const string & symbol) const
  {
    auto ptr = Unit::search_by_symbol(symbol);
    if (ptr != nullptr)
      return *ptr;

    ostringstream s;
    s << "Nonexistent unit symbol " << symbol;
    ZENTHROW(UnitNotFound, s.str());
  }

  const Unit & unit_given_name_or_symbol(const string & str) const
  {
    auto ptr = Unit::search_by_name(str);
    if (ptr != nullptr)
      return *ptr;

    ptr = Unit::search_by_symbol(str);
    if (ptr != nullptr)
      return *ptr;

    ostringstream s;
    s << "Nonexistent unit name or symbol " << str;
    ZENTHROW(UnitNotFound, s.str());
  }

public:

  /// the null VtlQuantity
  static const VtlQuantity null_quantity;

  /// Set this to quantity `q`. `q` can be Quantity or VtlQuantity
  void set(const BaseQuantity & q)
  {
    new (this) VtlQuantity(q.unit, q.raw());
  }

  /// Set this to value `val` with unit `*unit_ptr`
  void set(double val, const Unit * unit_ptr)
  {
    new (this) VtlQuantity(*unit_ptr, val);
  }

  /// Default constructor. Creates an invalid quantity set to
  /// null_quantity. In this way, (bad) first use of instantiated by
  /// default VtlQuantity objects can be detected by exception
  VtlQuantity() : BaseQuantity(Unit::null_unit, Unit::Invalid_Value) {}

  /// Creates a new VtlQuantity whose unit corresponds to symbol or
  /// name `unit_str` and value `val`
  VtlQuantity(const string & unit_str, double val = 0)
    : BaseQuantity(unit_given_name_or_symbol(unit_str), val)
  {
    check_value();
  }

  /// Creates a Vtlquantity with `unit` and value `val`
  VtlQuantity(const Unit & unit, double val) : BaseQuantity(unit, val)
  {
    check_value();
  }

  /// Create a Vtlquantity given an unit. The value is set to the
  /// center of unit range
  VtlQuantity(const Unit & unit) : BaseQuantity(unit)
  {
    check_value();
  }

  /// Creates a Vtlquantity copy of Vtlquantity `q`
  VtlQuantity(const VtlQuantity & q) noexcept
    : BaseQuantity(q.unit, q.value) {}

  /// Return A VtlQuantity corresponding to the next representable value
  VtlQuantity next() const { return VtlQuantity(unit, this->__increase()); }

  /// Return A VtlQuantity corresponding to the previous representable value
  VtlQuantity prev() const { return VtlQuantity(unit, this->__decrease()); }

  /// Create a Vtlquantity copy of quantity `q` with unit
  /// corresponding to unit name or symbol `unit_str`
  VtlQuantity(const string & unit_str, const BaseQuantity & q)
    : BaseQuantity(unit_given_name_or_symbol(unit_str), q.get_value())
  {
    if (&unit == &q.unit)
      value = q.raw();
    else
      value = unit_convert(q.unit, q.get_value(), unit);
    check_value();
  }

  /// Create a Vtlquantity copy of quantity `q` with unit `unit`
  VtlQuantity(const Unit & unit, const BaseQuantity & q)
    : BaseQuantity(unit)
  {
    if (&unit == &q.unit)
      value = q.raw();
    else
      {
	value = unit_convert(q.unit, q.get_value(), unit);
	check_value();
      }
  }

  /// Assign to `this` the double `val`
  VtlQuantity & operator = (double val)
  {
    if (this->is_null())
      ZENTHROW(UnitNotFound, "Assign of " + ::to_string(val) +
	       " to a null unit");
    value = val;
    check_value();

    return *this;
  }

  /// Assign to `this` the VtlQuantity `q`. Conversion is done
  VtlQuantity & operator = (const VtlQuantity & q)
  {
    if (this == &q)
      return *this;

    if (this->is_null())
      return * new (this) VtlQuantity(q.unit, q.value);

    if (&unit == &q.unit)	
      {
	value = q.get_value();
	return *this;
      }

    value = unit_convert(q.unit, q.get_value(), unit);
    check_value();

    return *this;
  }

  /// Create a VtlQuantity copy of Quantity `q`
  template <class U>
  VtlQuantity(const Quantity<U> & q) : BaseQuantity(q.unit, q.get_value()) {}

  /// Assign to `this` the Quantity `q`. Conversion is done
  template <class U>
  VtlQuantity & operator = (const Quantity<Unit> & q)
  {
    if (is_null())
      return * new (this) VtlQuantity(q.unit, q.raw());

    if (&unit == &q.unit)
      {
	value = q.get_value();
	return *this;
      }

    value = unit_convert(q.unit, q.get_value(), unit);
    check_value();

    return *this;
  }

  /// Sum double `rhs` to `this`
  VtlQuantity & operator += (double rhs)
  {
    value += rhs;
    check_value();
    return *this;
  }

  /// Subtract double `rhs` to `this`
  VtlQuantity & operator -= (double rhs)
  {
    value -= rhs;
    check_value();
    return *this;
  }

  /// Sum VtlQuantity `rhs` to `this`. Conversion is done if required
  VtlQuantity & operator += (const VtlQuantity & rhs)
  {
    value += rhs.get_value();
    check_value();
    return *this;
  }

  /// Return a Vtlquantity result of adding `this` plus `rhs`. Conversion
  /// is done if required to `this->unit`
  VtlQuantity operator + (const VtlQuantity & rhs) const
  {
    VtlQuantity ret(*this);
    ret += rhs;
    return ret;
  }

  /// Subtract VtlQuantity `rhs` to `this`. Conversion is done if required
  VtlQuantity & operator -= (const VtlQuantity & rhs)
  {
    value -= rhs.get_value();
    check_value();
    return *this;
  }

  /// Return a VtlQuantity result of subtracting `this` plus
  /// `rhs`. Conversion is done if required to `this->unit`
  VtlQuantity operator - (const VtlQuantity & rhs) const
  {
    VtlQuantity ret(*this);
    ret -= rhs;
    return ret;
  }

  /// Return a VtlQuantity product of `this` times VtlQuantity `rhs`. 
  VtlQuantity operator * (const VtlQuantity & rhs) const
  {
    return VtlQuantity(verify_compound(unit, rhs.unit).name,
		       value*rhs.get_value());
  }

  /// Return a VtlQuantity result of `this` divided by VtlQuantity `rhs`. 
  VtlQuantity operator / (const VtlQuantity & rhs) const
  {
    return VtlQuantity(verify_compound(unit, rhs.unit).name,
		       value/rhs.get_value());
  }

  /// Return a VtlQuantity product of `this` times Quantity `rhs`. 
  template <class U> VtlQuantity
  operator * (const Quantity<U> & rhs) const
  {
    return VtlQuantity(verify_compound(unit, rhs.unit).name,
		       value*rhs.get_value());
  }

  /// Return a VtlQuantity result of `this` divided by VtlQuantity `rhs`.
  template <class U> VtlQuantity
  operator / (const Quantity<U> & rhs) const
  {
    return VtlQuantity(verify_compound(unit, rhs.unit).name,
		       value/rhs.get_value());
  }

private:

  // Helper function that builds a temporal VtlQuantity
  VtlQuantity build_tmp(const VtlQuantity & rhs) const
  {
    check_physical_units(rhs);
    VtlQuantity q(unit, rhs); // here conversion is done
    q.check_value();
    return q;
  }

public:

  /// Less than comparison between `this` and `rhs`
  bool operator < (const VtlQuantity & rhs) const
  {
    if (&unit == &rhs.unit)
      return value < rhs.value;
    return value < build_tmp(rhs).get_value();
  }    

  /// Less or equal than comparison between `this` and `rhs`
  bool operator <= (const VtlQuantity & rhs) const
  {
    if (&unit == &rhs.unit)
      return value <= rhs.value;
    return value <= build_tmp(rhs).get_value();
  }

  /// Greater than comparison between `this` and `rhs`
  bool operator > (const VtlQuantity & rhs) const
  {
    if (&unit == &rhs.unit)
      return value > rhs.value;
    return value > build_tmp(rhs).get_value();
  }    

  /// Greater or equal than comparison between `this` and `rhs`
  bool operator >= (const VtlQuantity & rhs) const
  {
    if (&unit == &rhs.unit)
      return value >= rhs.value;
    return value >= build_tmp(rhs).get_value();
  }    

  /// Equal comparison between `this` and `rhs`
  bool operator == (const VtlQuantity & rhs) const
  {
    if (&unit == &rhs.unit)
      return value == rhs.value;
    return value == build_tmp(rhs).get_value();
  }

  bool is_near(const VtlQuantity & rhs, double e) const
  {
    if (&unit == &rhs.unit)
      return fabs(value - rhs.value) <= e;
    return fabs(value - build_tmp(rhs).get_value()) <= e;
  }

  bool is_near(double rhs, double e) const 
  { 
    return fabs(value - rhs) <= e; 
  } 

  /// Not equal comparison between `this` and `rhs`
  bool operator != (const VtlQuantity & rhs) const
  {
    return not (*this == rhs);
  }

  /// Less comparison between `this` and double `rhs`
  bool operator < (double rhs) const noexcept { return value < rhs; }

  /// Less or equal comparison between `this` and double `rhs`
  bool operator <= (double rhs) const noexcept { return value <= rhs; }

  /// Greater comparison between `this` and double `rhs`
  bool operator > (double rhs) const noexcept { return value > rhs; }

  /// Greater or equal comparison between `this` and double `rhs`
  bool operator >= (double rhs) const noexcept { return value >= rhs; }

  /// Equal comparison between `this` and double `rhs`
  bool operator == (double rhs) const noexcept { return value == rhs; }

  /// Not equal comparison between `this` and double `rhs`
  bool operator != (double rhs) const noexcept { return value != rhs; }
};

/* Return a VtlQuantity result of adding double `lhs` plus VtlQuantity `rhs`
  
   @author Leandro Rabindranath Leon
   @ingroup Units
 */
inline VtlQuantity operator + (double lhs, const VtlQuantity & rhs)
{
  return VtlQuantity(rhs.unit, lhs + rhs.get_value());
}

/* Return a VtlQuantity result of adding a VtlQuantity `lhs` plus
   double `rhs`
  
   @author Leandro Rabindranath Leon
   @ingroup Units
 */
inline VtlQuantity operator + (const VtlQuantity & lhs, double rhs)
{
  return VtlQuantity(lhs.unit, lhs.get_value() + rhs);
}

/* Return a VtlQuantity result of subtracting double `lhs` minus
   VtlQuantity `rhs`
  
   @author Leandro Rabindranath Leon
   @ingroup Units
 */
inline VtlQuantity operator - (double lhs, const VtlQuantity & rhs)
{
  return VtlQuantity(rhs.unit, lhs - rhs.get_value());
}

/* Return a VtlQuantity result of subtracting a VtlQuantity `lhs` minus
   double `rhs`

   @author Leandro Rabindranath Leon
   @ingroup Units
 */
inline VtlQuantity operator - (const VtlQuantity & lhs, double rhs)
{
  return VtlQuantity(lhs.unit, lhs.get_value() - rhs);
}

/* Return the product of double `lhs` times the VtlQuantity `rhs`. 
  
   @author Leandro Rabindranath Leon
   @ingroup Units
*/
inline VtlQuantity operator * (double lhs, const VtlQuantity & rhs)
{
  return VtlQuantity(rhs.unit, lhs*rhs.get_value());
}

/* Return the product of VtlQuantity `lhs` times the double `rhs`. 
  
   @author Leandro Rabindranath Leon
  @ingroup Units
 */
inline VtlQuantity operator * (const VtlQuantity & lhs, double rhs)
{
  return VtlQuantity(lhs.unit, lhs.get_value()*rhs);
}

/* Return the double `lhs` divided by the VtlQuantity `rhs`. 
  
   @author Leandro Rabindranath Leon
  @ingroup Units
*/
inline VtlQuantity operator / (double lhs, const VtlQuantity & rhs)
{
  return VtlQuantity(rhs.unit, lhs / rhs.get_value());
}

/* Return the double `lhs` divided by the VtlQuantity `rhs`. 
  
   @author Leandro Rabindranath Leon
   @ingroup Units
*/
inline VtlQuantity operator / (const VtlQuantity & lhs, double rhs)
{
  return VtlQuantity(lhs.unit, lhs.get_value() / rhs);
}

/** Return the maximum allowed value for the unit

    @author Leandro Rabindranath Leon
    @ingroup Units
 */
inline VtlQuantity Unit::max() const noexcept
{
  return VtlQuantity(*this, max_val);
}

/** Return the minimum allowed value for the unit
   
    @author Leandro Rabindranath Leon
    @ingroup Units
 */
inline VtlQuantity Unit::min() const noexcept
{
  return VtlQuantity(*this, min_val);
}

/** Increase the value to the immediately superior according to the
    floating point representation
   
    @ingroup Units
    @author Leandro Rabindranath Leon
 */
inline void BaseQuantity::increase()
{
  value = nextafter(value, unit.max().raw());
  check_value();
}

/** Decrease the value to the immediately inferior according to the
    floating point representation
   
    @ingroup Units
    @author Leandro Rabindranath Leon
 */
inline void BaseQuantity::decrease()
{
  value = nextafter(value, unit.min().raw());
  check_value();
}

/* Less comparison between a double `lhs` and a VtlQuantity `rhs`

   @author Leandro Rabindranath Leon
   @ingroup Units
 */
inline bool operator < (double lhs, const VtlQuantity & rhs) noexcept
{
  return lhs < rhs.get_value();
}

/* Greater comparison between a double `lhs` and a VtlQuantity `rhs`

   @author Leandro Rabindranath Leon
   @ingroup Units
 */
inline bool operator > (double lhs, const VtlQuantity & rhs) noexcept
{
  return lhs > rhs.get_value();
}

/* Less or equal comparison between a double `lhs` and a VtlQuantity `rhs`

   @author Leandro Rabindranath Leon
   @ingroup Units
 */
inline bool operator <= (double lhs, const VtlQuantity & rhs) noexcept
{
  return lhs <= rhs.get_value();
}

/* Greater or equal comparison between a double `lhs` and a VtlQuantity `rhs`

   @author Leandro Rabindranath Leon
   @ingroup Units
 */
inline bool operator >= (double lhs, const VtlQuantity & rhs) noexcept
{
  return lhs >= rhs.get_value();
}

/* Equal comparison between a double `lhs` and a VtlQuantity `rhs`

   @author Leandro Rabindranath Leon
   @ingroup Units
 */
inline bool operator == (double lhs, const VtlQuantity & rhs) noexcept
{
  return lhs == rhs.get_value();
}

/* Not equal comparison between a double `lhs` and a VtlQuantity `rhs`

   @author Leandro Rabindranath Leon
   @ingroup Units
 */
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
  assert(&UnitName::get_instance() == &unit);
  if (&unit == &(q.unit))
    {
      value = q.get_value();
      return;
    }
  value = unit_convert(q.unit, q.get_value(), unit);
  check_value();
}

template <class UnitName>
Quantity<UnitName> & Quantity<UnitName>::operator = (const VtlQuantity & q)
{
  if (&unit == &q.unit)
    {
      value = q.get_value();
      return *this;
    }
  
  value = unit_convert(q.unit, q.get_value(), unit);
  check_value();
  return *this;
}

template <class UnitName> Quantity<UnitName> &
Quantity<UnitName>::operator += (const VtlQuantity & rhs) const
{
  verify_same_unit(rhs.unit);
  value += rhs.get_value();
  check_value();
  return *this;
}

template <class UnitName> Quantity<UnitName> &
Quantity<UnitName>::operator -= (const VtlQuantity & rhs) const
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
		     value*rhs.get_value());
}

template <class UnitName> VtlQuantity
Quantity<UnitName>::operator / (const VtlQuantity & rhs) const
{
  return VtlQuantity(VtlQuantity::verify_compound(unit, rhs.unit).name,
		     value/rhs.get_value());
}

inline pair<bool, DynList<string>>
	 check_conversions(const PhysicalQuantity & pq)
{
  DynList<string> missing;
  auto units = Unit::units(pq);
  for (auto it1 = units.get_it(); it1.has_curr(); it1.next())
    {
      auto src_unit = it1.get_curr();
      for (auto it2 = units.get_it(); it2.has_curr(); it2.next())
	{
	  auto tgt_unit = it2.get_curr();
	  if (src_unit == tgt_unit)
	    continue;
	  if (not exist_conversion(*src_unit, *tgt_unit))
	    {
	      ostringstream s;
	      s << "Missing conversion from " << src_unit->name << "("
		<< src_unit->symbol << ") to " << tgt_unit->name << "("
		<< tgt_unit->symbol << ")";
	      missing.append(s.str());
	    }
	}
    }

  return make_pair(missing.is_empty(), move(missing));
}

/** Return the value immediately superior according to the floating
    point representation
   
    @ingroup Units
    @author Leandro Rabindranath Leon
 */
inline VtlQuantity next_value(const VtlQuantity & val)
{
  return VtlQuantity(val.unit, next_value(val.raw()));
}

/** Return the value immediately inferior according to the floating
    point representation
   
    @ingroup Units
    @author Leandro Rabindranath Leon
 */
inline VtlQuantity prev_value(const VtlQuantity & val)
{
  return VtlQuantity(val.unit, prev_value(val.raw()));
}

# endif // UNITS_H

