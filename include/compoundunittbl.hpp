#ifndef COMPOUND_UNIT_TBL_HPP
#define COMPOUND_UNIT_TBL_HPP

/* C++ System Headers */
#include <algorithm>			// Collection of functions
#include <map>						// Container class
#include <vector>					// Container class

class Unit;

//namespace ztg {
//namespace units {

class CompoundUnitTbl
{
	struct Cmp
  {
    bool operator () (const std::vector<std::string> & l1,
		      						const std::vector<std::string> & l2) const noexcept 
    {
    	std::vector<std::string> tmp_l1(l1), tmp_l2(l2);
    	std::sort(tmp_l1.begin(), tmp_l1.end());
    	std::sort(tmp_l2.begin(), tmp_l2.end());
      return (tmp_l1 < tmp_l2);
    }
  };
	
	std::map<std::vector<std::string>, const Unit * const, Cmp> tbl;

 public:
	
	const Unit * search(const std::vector<std::string> & names) 
	{
  	auto p = tbl.find(names);
    return p == tbl.end() ? nullptr : p->second;
  }

  bool insert(const std::vector<std::string> & l, const Unit & unit) 
  {
  	return tbl.insert(std::make_pair(l, &unit)).second;
  }

	std::vector<std::pair<std::vector<std::string>, std::string>> items() 
	{
  	using T = std::pair<std::vector<std::string>, std::string>;
    std::vector<T> items_vector;
    for (auto entry : tbl) {
    	items_vector.push_back(std::make_pair(entry.first, entry.second->name));
    }
    return items_vector;
  }
};

//} // namespace units
//} // namespace ztg


#endif // COMPOUND_UNIT_TBL_HPP