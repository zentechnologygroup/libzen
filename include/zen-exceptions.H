# ifndef ZEN_EXCEPTIONS_H
# define ZEN_EXCEPTIONS_H

# include <exception>
# include <sstream>

# include <utils.H>

using namespace std;

/** Zen exception class

   @author Leandro Rabindranath Leon 
   @ingroup Exceptions
   @note This class is not intended for public use. Instead use the
   macro DEFINE_ZEN_EXCEPTION 
 */
struct ZenException : public std::runtime_error
{
  /// Line number of source file where the exception was thrown
  const size_t line_number = 0;
  
  /// file name where the exception was thrown 
  const string file_name = "No defined"; 

  const string type = "No defined";   /// Type name
  const string msg = "No defined"; /// Message describing the errow

protected:

  string category_msg = "No defined";

private:

  static string make_what(const string & category_msg,
			  size_t line_number,
			  const string & file_name,
			  const string & type,
			  const string & msg)
  {
    ostringstream s;
    s << category_msg << "|" << file_name << "|" << line_number
      << "|" << type << "|" << msg;
    return s.str();
  }

public:

  ZenException() : runtime_error(msg) {}

  ZenException(const string & category_msg,
	       const size_t line_number,
	       const string & file_name,
	       const string & type,
	       const string & msg)
    : runtime_error(make_what(category_msg, line_number, file_name, type, msg)),
      line_number(line_number), file_name(file_name), type(type) {}
};

/** Define a new exception

    @param[in] name of the exception
    @param[in] category_msg

    @ingroup Exceptions
    @author Leandro Rabindranath Leon 
 */
# define DEFINE_ZEN_EXCEPTION(name, category_msg)	\
  struct name : public ZenException			\
  {							\
    name(const size_t line_number,			\
	 const string & file_name,			\
	 const string & type,				\
	 const string & msg)						\
      : ZenException(#category_msg, line_number, file_name, type, msg) {} \
  };

/** Macro for throwing a zen exception
   
   @param[in] type zen exception class name
   @param[in] msg message describing the error
   @ingroup Exceptions
 */
# define ZENTHROW(type, msg) throw type(__LINE__, __FILE__, #type, msg)

DEFINE_ZEN_EXCEPTION(MinMaxReversed,
		     "minimum value is greater than maximum value");
DEFINE_ZEN_EXCEPTION(InvalidCsvHeader, "Invalid csv header");
DEFINE_ZEN_EXCEPTION(InvalidCsvRow, "Invalid csv row");
DEFINE_ZEN_EXCEPTION(InvalidValue, "Invalid value");
DEFINE_ZEN_EXCEPTION(OutOfMemory, "No memory");
DEFINE_ZEN_EXCEPTION(OutOfRange, "Value is out of allowed range");
DEFINE_ZEN_EXCEPTION(ValueNotFound, "Value not found");
DEFINE_ZEN_EXCEPTION(CommandLineError, "error parsing command line");
DEFINE_ZEN_EXCEPTION(InvariantError, "A bug has been detected. "
		     "Please send a bug report to support@zentech.com");
DEFINE_ZEN_EXCEPTION(SizeMismatch, "Sequences have different sizes");
DEFINE_ZEN_EXCEPTION(InvalidConversion, "failure in numeric conversion");
DEFINE_ZEN_EXCEPTION(NameNotFound, "name not found");
DEFINE_ZEN_EXCEPTION(InvalidSize, "invalid size");
DEFINE_ZEN_EXCEPTION(InvalidRange, "invalid range");
DEFINE_ZEN_EXCEPTION(InvalidUnit, "invalid unit");

# endif
