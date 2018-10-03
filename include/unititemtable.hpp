#ifndef UNIT_ITEM_TABLE_HPP
#define UNIT_ITEM_TABLE_HPP

/* C++ System Headers */
#include <string>				// String class
#include <ostream>			// Output stream class
#include <map> 					// Container class

/* Project headers */
#include "unititem.hpp"

//namespace ztg {
//namespace units {

class UnitItemTable
{
  std::map<std::string, const UnitItem *> name_table; // index by unit
  std::map<std::string, const UnitItem *> symbol_table; // index by symbol

 public:

  std::vector <const UnitItem * > items() const 
  {
    return GetMapValues(name_table);
  }

  std::vector <std::string> names() const 
  {
    return GetMapKeys(name_table);
  }

  std::vector <std::string> symbols() const 
  {
    return GetMapKeys(symbol_table);
  }

  auto get_it() 
  { 
    return name_table.begin(); 
  }

  bool exists_name(const std::string & name) const noexcept 
  {
    auto it = name_table.find(name);
    return (it != name_table.end());
  }

  bool exists_symbol(const std::string & symbol) const noexcept 
  {
    auto it = symbol_table.find(symbol);
    return (it != symbol_table.end());
  }

  const UnitItem * search_by_name(const std::string & name) const noexcept
  {
    auto it = name_table.find(name);
    if (it != name_table.end()) {
      return it->second;
    } else {
      return nullptr;
    }
  }

  const UnitItem * search_by_symbol(const std::string & symbol) const noexcept
  {
    auto it = symbol_table.find(symbol);
    if (it != symbol_table.end()) {
      return it->second;
    } else {
      return nullptr;
    }
  }

  size_t size() const noexcept 
  { 
    return name_table.size(); 
  }

  void validate(const UnitItem * ptr, const std::string & str) 
  {
    //info: double scope deleted
    const std::string & name = ptr->name;
    if (exists_name(str)) {
      std::ostringstream s;
      s << "Repeated " << str << " name " << name;
      throw std::domain_error(s.str());
    }
    
    const std::string & symbol = ptr->symbol;
    if (exists_symbol(str)) {
      std::ostringstream s;
      s << "Repeated " << str << " symbol " << symbol;
      throw std::domain_error(s.str());
    }
  }

  void register_item(const UnitItem * ptr) 
  {
    if(exists_name(ptr->name)) {
      std::ostringstream s;
      s << " name " << ptr->name << " already exist";
      throw std::domain_error(s.str());
    }

    if(exists_symbol(ptr->symbol)) {
      std::ostringstream s;
      s << "unit symbol " << ptr->symbol << " already exist";
      throw std::domain_error(s.str());
    }

    name_table.insert(std::make_pair(ptr->name, ptr));
    symbol_table.insert(std::make_pair(ptr->symbol, ptr));
  }
};

//} // namespace units
//} // namespace ztg


#endif // UNIT_ITEM_TABLE_HPP