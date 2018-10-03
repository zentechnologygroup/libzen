#ifndef UTILS_HPP
#define UTILS_HPP

/* C++ System Headers */
#include <algorithm>    // Collection of functions
#include <typeinfo>     // Operators typeid and dynamic_cast 
#include <cstdlib>      // Standard general utilities library
#include <sstream>      // String stream classes
#include <numeric>      // Generalized numeric operations
#include <memory>       // Utilities to manage dynamic memory
#include <string>       // String class
#include <vector>       // Container class
#include <map>          // Container class
#include <cxxabi.h>       // CHECK: UNUSED

//namespace ztg {
//namespace utils {

inline std::string demangle(const char* name)
{
  int status = -4; // some arbitrary value to eliminate the compiler warning
  // enable c++11 by passing the flag -std=c++11 to g++
  std::unique_ptr<char, void(*)(void*)> res
  { abi::__cxa_demangle(name, NULL, NULL, &status), std::free };
  return (status==0) ? res.get() : name ;
}

#define CLASSNAME_TO_STRING(class_ptr) demangle(typeid(*class_ptr).name())

inline std::vector<std::vector<std::string>> FormatTable(
    const std::vector<std::size_t> & lens,
    const std::vector<std::vector<std::string>> & matrix)
{  
  std::vector<std::vector<std::string>> result(matrix);

  for (auto & row : result) {
    std::transform(row.begin(), row.end(), lens.begin(), row.begin(),
                   [] (const std::string & str, const std::size_t & len)
                   {
                      std::string blanks(len - str.size(), ' ');
                      return (str + blanks + " ");
                   });
  }
  return result;
}

inline std::vector<std::vector<std::string>> FormatTable(
    const std::vector<std::vector<std::string>> & matrix)
{
  if (matrix.empty()) {
    return matrix;
  }

  auto fold_operation =
    [] (const std::vector<std::size_t> & acum,
        const std::vector<std::string> & list)
    {
      std::vector<std::size_t> result(acum.size());

      for (int i = 0; i < acum.size() and i < list.size(); i++) {
        result[i] = std::max(acum[i], list[i].size());
      }

      return result;
    };

  std::vector<std::size_t> ilens(matrix[0].size(), 0);
  std::vector<std::size_t> maxs = std::accumulate(matrix.begin(), matrix.end(),
                                                  ilens, fold_operation);
  return FormatTable(maxs, matrix);
}

inline std::vector<std::vector<std::string>> format_csv(
    const std::vector<std::vector<std::string>> & matrix)
{
  std::vector<std::vector<std::string>> result(matrix);
  for (auto & row : result) {
    std::transform(row.begin(), std::prev(row.end()), row.begin(),
                   [] (const std::string & str)
                   {
                      return (str + ",");
                   });
  }
  return result;
}

inline std::string to_string(
    const std::vector<std::vector<std::string>> & matrix)
{
  std::ostringstream stream;

  for (const auto & row : matrix) {
    for (const auto & item : row) {
      stream << item;
    }
    stream << "\n";
  }
  return stream.str();
}

template<class T1, class T2> 
inline std::vector<T2> GetMapValues(const std::map <T1, T2> & map_instance) 
{
  std::vector <T2> vector_map_values;
  for(auto entry: map_instance) {
    vector_map_values.push_back(entry.second);
  }
  return vector_map_values;
}

template<class T1, class T2>
inline std::vector<T1> GetMapKeys(const std::map <T1, T2> & map_instance) 
{
  std::vector <T1> vector_map_keys;
  for(auto entry: map_instance) {
    vector_map_keys.push_back(entry.first);
  }
  return vector_map_keys;
}

template<class T1>
inline std::vector<T1> GetSetKeys(const std::set <T1> & set_instance) {
  std::vector <T1> vector_set_keys;
  for(auto entry: set_instance) {
    vector_set_keys.push_back(entry);
  }
  return vector_set_keys;
}

//} // namespace utils
//} // namespace ztg

# endif // UTILS_HPP
