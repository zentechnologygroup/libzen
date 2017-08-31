/** 
			 Zen Units management
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

class Unit;

/** Instantiate the units system

    @author Leandro Rabindranath Leon
    @ingroup Units
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

   @ingroup Units
   @author Leandro Rabindranath Leon
 */
inline const UnitsInstancer & init_units() { return UnitsInstancer::init(); }

/** Physical magnitude

    @ingroup Units
    @author Leandro Rabindranath Leon
 */
class PhysicalQuantity : public UnitItem
{
  friend class Unit;
  friend class UnitsInstancer;

  using UnitItem::UnitItem;

  static UnitItemTable * tbl;

  DynList<const Unit * const> unit_list;

  PhysicalQuantity() {}

public:

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
    tbl->register_item(this);
  }

public:

  /// Return a list of pointer to units associated to this physical magnitude
  const DynList<const Unit * const> & units() const { return unit_list; }

  /// Return a list of pointer to all defined physical magnitudes  
  static DynList<const PhysicalQuantity * const> quantities()
  {
    return tbl->items().maps<const PhysicalQuantity * const>([] (auto p)
      {
	return static_cast<const PhysicalQuantity * const>(p);
      });
  }

  /// Return a list of names of the all defined physical magnitudes
  static DynList<string> names() { return tbl->names(); }

  static const PhysicalQuantity * search(const string & name)
  {
    auto ptr = tbl->search_by_name(name);
    return static_cast<const PhysicalQuantity * const>(ptr);
  }
};

/** Defines a new physical magnitude

    @param[in] name of the new physical quantity
    @param[in] symbol string used as unit symbol
    @param[in] desc description 

    @ingroup Units
    @author Leandro Rabindranath Leon
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

    @ingroup Units
    @author Leandro Rabindranath Leon
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

  inline VtlQuantity min() const noexcept; /// minimum allowed value
  inline VtlQuantity max() const noexcept; /// maximum allowed value

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

  static UnitItemTable * tbl;
  static DynSetTree<const Unit*> * unit_tbl;

public:

  /// return the number of units
  static size_t size() { return unit_tbl->size(); }

  /// Return a list of all declared and used units
  static DynList<const Unit*> units() { return unit_tbl->keys(); }

  /// return all the units associated to this (including this)
  const DynList<const Unit* const> & family_units() const
  {
    return physical_quantity.units();
  }

  /// return all the units associated to this (not including this)
  DynList<const Unit* const> sibling_units() const
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
  static const DynList<const Unit * const> & units(const PhysicalQuantity & pq)
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

    tbl->register_item(this);
    unit_tbl->insert(this);
    const_cast<PhysicalQuantity&>(physical_quantity).unit_list.append(this);
  }

  double default_value() const noexcept { return (min_val + max_val)/2; }
};

extern string units_json();

using Unit_Convert_Fct_Ptr = double (*)(double);

/** Functor for comparing pair of units. It is used for the hash
    tables containing conversion functions
    
    @ingroup Units
    @author Leandro Rabindranath Leon
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

using UnitHashTbl = DynMapHash<pair<string, string>, Unit_Convert_Fct_Ptr>;
using UnitMap = ODhashTable<pair<pair<const Unit*, const Unit*>,
				 Unit_Convert_Fct_Ptr>, UnitPairEqual>;

# include "multiunitmap.H"

/** Hash table mapping pair of unit references to conversion functions.

    @ingroup Units
 */
extern UnitMap * __unit_map;

extern CompoundUnitTbl * __compound_unit_tbl;

template <typename...> struct __always_false : std::false_type {};

inline const Unit * search_compound_unit(const string & uname1,
					 const string & uname2)
{
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
    @ingroup Units
    @author Leandro Rabindranath Leon
 */
inline Unit_Convert_Fct_Ptr
search_conversion(const Unit & src, const Unit & tgt)
{
  using UP = pair<const Unit*, const Unit*>;
  pair<UP, Unit_Convert_Fct_Ptr> p; p.first = UP(&src, &tgt); // saves copy
  auto ptr = __unit_map->search(p);
  return ptr == nullptr ? nullptr : ptr->second;
}

/** Unit conversion helper

    This class creates a pointer to a conversion function from
    `SrcUnit` to `TgtUnit`

    @ingroup Units
    @author Leandro Rabindranath Leon
 */
template <class SrcUnit, class TgtUnit>
class UnitConverter
{
  static double convert(double val)
  {
    return unit_convert<SrcUnit, TgtUnit>(val);
  }

  Unit_Convert_Fct_Ptr fct_ptr = nullptr;

public:

  /// Create and register an unit conversion converter from `SrcUnit`
  /// to `TgtUnit`
  UnitConverter()
  {
    const Unit & src_instance = SrcUnit::get_instance();
    const Unit & tgt_instance = TgtUnit::get_instance();
    
    fct_ptr = &UnitConverter::convert;

    __unit_map->insert(make_pair(make_pair(&src_instance, &tgt_instance),
				fct_ptr));

    assert(search_conversion(src_instance, tgt_instance));
  }

  /// return the conversio function pointer
  Unit_Convert_Fct_Ptr operator () () const noexcept { return fct_ptr; }
};

/** Return `true` if it exists conversion rom `src` unit to `tgt` unit

    @ingroup Units
    @author Leandro Rabindranath Leon
 */
inline bool exist_conversion(const Unit & src, const Unit & tgt)
{
  return search_conversion(src, tgt) != nullptr;
}

/** Return `true` if it exists conversion from `src_symbol` unit to
    `tgt_symbol` unit

    Both parameters are string corresponding to unit symbols

    @ingroup Units
    @author Leandro Rabindranath Leon
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

    @ingroup Units
    @author Leandro Rabindranath Leon
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
    @ingroup Units
    @author Leandro Rabindranath Leon
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
						  
    @ingroup Units
    @author Leandro Rabindranath Leon
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

/** Transform a container of doubles expressed in `src_unit` to their
    corresponding values expressed in `tgt_unit`.

    `c` could be any Aleph-w container type: list, array, tree. 

    Example:

        Array<double> temp_values = // some values in Fahrenheit
	mutable_unit_convert(Fahrenheit::get_instance, temp_values,
                             Celsius::get_instance());
	// At this point temp_values are in Celsius
						  
    @ingroup Units
    @author Leandro Rabindranath Leon
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

    @param[in] __name of unit
    @param[in] symbol of unit
    @param[in] desc description
    @param[in] physical_quantity reference to a previusly defined
    `Physical_Quantity` object associated to the unit
    @param[in] min minimum value of the unit
    @param[in] max maximum value of the unit
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
    if (value >= unit.min_val and value <= unit.max_val)
      return true;

    if (fabs(value - unit.min_val) <= unit.get_epsilon() or
	fabs(value - unit.max_val) <= unit.get_epsilon())
      return true;

    if (&unit == &Unit::null_unit)
      return true;

    return false;
  }

protected:
  
  // helper for validating that value is in [min_val, max_val]. It
  // throws range_error if value is not in the interval
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

  // throw exception if the units do not share the same physical quantity
  void check_physical_units(const BaseQuantity & q) const
  {
    if ((void*) &unit.physical_quantity == (void*) &(q.unit.physical_quantity))
      return;

    ostringstream s;
    s << "Units do not refer to the same physical quantities" << endl
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

  bool is_null() const noexcept { return value == Unit::Invalid_Value; }

  double get_value() const noexcept { return value; }

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

inline double pow3(const BaseQuantity & q)
{
  return q.raw()*pow2(q);
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

inline double sin(const BaseQuantity & q)
{
  return sin(q.raw());
}

inline double cos(const BaseQuantity & q)
{
  return cos(q.raw());
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

  void assign_converted(const Quantity<UnitName> &) {}

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
    if (&q == this)
      return *this;

    value = q.get_value();

    return *this;
  }

  /// Inter unit constructor. Perform the conversion
  template <class SrcUnit>
  Quantity(const Quantity<SrcUnit> & q)
    : BaseQuantity(UnitName::get_instance())
  {
    assign_converted(q);
  }

  Quantity next() const { return Quantity(this->__increase()); }

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

  inline Quantity & operator += (const VtlQuantity & rhs) const;
  inline Quantity & operator -= (const VtlQuantity & rhs) const;
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
    if (unit_ptr != nullptr)
      return *unit_ptr;
    ostringstream s;
    s << "There is no compund unit between " << unit1.name << " and "
      << unit2.name;
    ZENTHROW(CompoundUnitNotFound, s.str());
  }

private:

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

public:

  static const VtlQuantity null_quantity;

  void set(const BaseQuantity & q)
  {
    new (this) VtlQuantity(q.unit, q.raw());
  }

  void set(double val, const Unit * unit_ptr)
  {
    new (this) VtlQuantity(*unit_ptr, val);
  }

  VtlQuantity() : BaseQuantity(Unit::null_unit, Unit::Invalid_Value) {}

  VtlQuantity(const string & unit_name, double val = 0)
    : BaseQuantity(unit_given_name(unit_name), val)
  {
    check_value();
  }

  VtlQuantity(double val, const string & symbol)
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

  VtlQuantity(const VtlQuantity & q) noexcept
    : BaseQuantity(q.unit, q.value) {}

  VtlQuantity next() const { return VtlQuantity(unit, this->__increase()); }

  VtlQuantity prev() const { return VtlQuantity(unit, this->__decrease()); }

  VtlQuantity(const string & unit_name, const BaseQuantity & q)
    : BaseQuantity(unit_given_name(unit_name), q.get_value())
  {
    if (&unit == &q.unit)
      value = q.raw();
    else
      value = unit_convert(q.unit, q.get_value(), unit);
    check_value();
  }

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

  VtlQuantity & operator = (double val)
  {
    if (this->is_null())
      ZENTHROW(UnitNotFound, "Assign of " + ::to_string(val) +
	       " to a null unit");
    value = val;
    check_value();

    return *this;
  }

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

  template <class U>
  VtlQuantity(const Quantity<U> & q) : BaseQuantity(q.unit, q.get_value()) {}

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
		       value*rhs.get_value());
  }

  VtlQuantity operator / (const VtlQuantity & rhs) const
  {
    return VtlQuantity(verify_compound(unit, rhs.unit).name,
		       value/rhs.get_value());
  }

  template <class U> VtlQuantity
  operator * (const Quantity<U> & rhs) const
  {
    return VtlQuantity(verify_compound(unit, rhs.unit).name,
		       value*rhs.get_value());
  }

  template <class U> VtlQuantity
  operator / (const Quantity<U> & rhs) const
  {
    return VtlQuantity(verify_compound(unit, rhs.unit).name,
		       value/rhs.get_value());
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
    if (&unit == &rhs.unit)
      return value < rhs.value;
    return value < build_tmp(rhs).get_value();
  }    

  bool operator <= (const VtlQuantity & rhs) const noexcept
  {
    if (&unit == &rhs.unit)
      return value <= rhs.value;
    return value <= build_tmp(rhs).get_value();
  }

  bool operator > (const VtlQuantity & rhs) const noexcept
  {
    if (&unit == &rhs.unit)
      return value > rhs.value;
    return value > build_tmp(rhs).get_value();
  }    

  bool operator >= (const VtlQuantity & rhs) const noexcept
  {
    if (&unit == &rhs.unit)
      return value >= rhs.value;
    return value >= build_tmp(rhs).get_value();
  }    

  bool operator == (const VtlQuantity & rhs) const noexcept
  {
    if (&unit == &rhs.unit)
      return value == rhs.value;
    return value == build_tmp(rhs).get_value();
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

// TODO: revisar
inline VtlQuantity operator + (double lhs, const VtlQuantity & rhs)
{
  return VtlQuantity(rhs.unit, lhs + rhs.get_value());
}

inline VtlQuantity operator + (const VtlQuantity & lhs, double rhs)
{
  return VtlQuantity(lhs.unit, lhs.get_value() + rhs);
}

inline VtlQuantity operator - (double lhs, const VtlQuantity & rhs)
{
  return VtlQuantity(rhs.unit, lhs - rhs.get_value());
}

inline VtlQuantity operator - (const VtlQuantity & lhs, double rhs)
{
  return VtlQuantity(lhs.unit, lhs.get_value() - rhs);
}

inline VtlQuantity operator * (double lhs, const VtlQuantity & rhs)
{
  return VtlQuantity(rhs.unit, lhs*rhs.get_value());
}

inline VtlQuantity operator * (const VtlQuantity & lhs, double rhs)
{
  return VtlQuantity(lhs.unit, lhs.get_value()*rhs);
}

inline VtlQuantity operator / (double lhs, const VtlQuantity & rhs)
{
  return VtlQuantity(rhs.unit, lhs / rhs.get_value());
}

inline VtlQuantity operator / (const VtlQuantity & lhs, double rhs)
{
  return VtlQuantity(lhs.unit, lhs.get_value() / rhs);
}

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

inline pair<bool, DynList<string>> check_conversions(const PhysicalQuantity & pq)
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

inline VtlQuantity next_value(const VtlQuantity & val)
{
  return VtlQuantity(val.unit, next_value(val.raw()));
}

inline VtlQuantity prev_value(const VtlQuantity & val)
{
  return VtlQuantity(val.unit, prev_value(val.raw()));
}

# endif // UNITS_H

