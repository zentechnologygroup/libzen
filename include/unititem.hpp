#ifndef UNIT_ITEM_HPP
#define UNIT_ITEM_HPP

/* C++ System Headers */
#include <sstream>			// String stream classes
#include <string>				// String class
#include <ostream>			// Output stream class

/* Project headers */
#include "utils.hpp"

//namespace ztg {
//namespace units {

struct UnitItem
{
  const std::string name = "Undefined";
  const std::string symbol = "Undefined";
  const std::string description = "Undefined";
  const std::string latex_symbol = "Undefined";

  UnitItem(const std::string & __name, const std::string & __symbol,
  				 const std::string & desc) noexcept
  	: name(__name), symbol(__symbol), description(desc) {}

  UnitItem(const std::string & name, const std::string & symbol,
	   			 const std::string & latex_symbol, const std::string & desc) noexcept
  	: name(name), symbol(symbol), description(desc), 
  		latex_symbol(latex_symbol) {}

  std::string to_string(size_t left_margin = 0) const
  {
  	const std::string margin(left_margin, ' ');
    std::ostringstream s;
    s << margin << "UnitItem name = " << name << std::endl
      << margin << "Symbol        = " << symbol << std::endl
      << margin << "Description   = " << description << std::endl;
    return s.str();
  }

  friend std::ostream & operator << (std::ostream & out, const UnitItem & ui)
  {
    return out << ui.to_string();
  }
};

//} // namespace units
//} // namespace ztg

# endif // UNIT_ITEM_HPP
