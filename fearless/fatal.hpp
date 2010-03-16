#ifndef FEARLESS__FATAL_HPP
#define FEARLESS__FATAL_HPP

#include <cstdlib>
#include <ostream>

#include <fearless/api.hpp>

namespace fearless {

extern FEARLESS_API std::ostream& error_stream;

}

#define FEARLESS_FATAL(msg) \
  do { \
    fearless::error_stream << __FILE__ << ":" << __LINE__ << ":" << \
      __PRETTY_FUNCTION__ <<  ": fatal error: " << msg << std::endl; \
    std::abort(); \
  } while(false)

#endif // FEARLESS__FATAL_HPP

