#ifndef PHYSICAL_QUANTITY_HPP
#define PHYSICAL_QUANTITY_HPP

#include "unititem.hpp"
#include "unit.hpp"

//namespace ztg {
//namespace units {

class PhysicalQuantity : public UnitItem
{
  friend class Unit;
  using UnitItem::UnitItem;
  static UnitItemTable tbl;
  std::vector<const Unit *> unit_list;

 public:

  static const PhysicalQuantity null_physical_quantity;
  
 protected:

  PhysicalQuantity(const string & name, const string & symbol,
  	               const string & latex_symbol, const string & desc)
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

  static std::vector <const PhysicalQuantity * > quantities() 
  {
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
  
  static const PhysicalQuantity * search(const string & name)
  {
    auto ptr = tbl.search_by_name(name);
    return static_cast<const PhysicalQuantity * >(ptr);
  }
};

//} // namespace units
//} // namespace ztg

#endif // PHYSICAL_QUANTITY_HPP