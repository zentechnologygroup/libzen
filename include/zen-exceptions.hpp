#ifndef ZEN_EXCEPTIONS_H
#define ZEN_EXCEPTIONS_H

/* C++ System Headers */
#include <exception>
#include <sstream>

/* Project headers */
#include "utils.hpp"

//namespace ztg {
//namespace exception {

struct ZenException : public std::runtime_error
{
  const size_t line_number = 0;
  const std::string file_name = "No defined";
  const std::string type = "No defined";
  const std::string msg = "No defined";

protected:

  std::string category_msg = "No defined";

private:

  static std::string make_what(const std::string & category_msg,
                               size_t line_number,
                               const std::string & file_name,
                               const std::string & type,
                               const std::string & msg)
  {
    std::ostringstream s;
    s << category_msg << "|" << file_name << "|" << line_number
      << "|" << type << "|" << msg;
    return s.str();
  }

public:

  ZenException() : runtime_error(msg) {}

  ZenException(const std::string & category_msg, const size_t line_number,
               const std::string & file_name, const std::string & type,
               const std::string & msg)
    : runtime_error(make_what(category_msg, line_number, file_name, type, msg)),
      line_number(line_number), file_name(file_name), type(type) {}
};

#define DEFINE_ZEN_EXCEPTION(name, category_msg)                               \
  struct name : public ZenException                                            \
  {                                                                            \
    name(const size_t line_number, const std::string & file_name,              \
         const std::string & type, const std::string & msg)                    \
      : ZenException(#category_msg, line_number, file_name, type, msg) {}      \
  };
    
#define ZENTHROW(type, msg) throw type(__LINE__, __FILE__, #type, msg)

DEFINE_ZEN_EXCEPTION(MinMaxReversed,
                     "minimum value is greater than maximum value");
DEFINE_ZEN_EXCEPTION(InvalidCsvHeader, "Invalid csv header");
DEFINE_ZEN_EXCEPTION(InvalidCsvRow, "Invalid csv row");
DEFINE_ZEN_EXCEPTION(InvalidValue, "Invalid value");

//} // namespace exception
//} // namespace ztg

#endif