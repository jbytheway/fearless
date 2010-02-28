#ifndef FEARLESS__DEBUG_HPP
#define FEARLESS__DEBUG_HPP

#include <ostream>

namespace fearless {

extern std::ostream& debug_stream;

}

#define FEARLESS_DEBUG(msg) \
  do { \
    fearless::debug_stream << __FILE__ << ":" << __LINE__ << ":" << \
      __PRETTY_FUNCTION__ <<  ": " << msg << std::endl; \
  } while(false)

#endif // FEARLESS__DEBUG_HPP

