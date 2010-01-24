#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <fearless/system.hpp>

BOOST_AUTO_TEST_CASE(default_constructed_system_is_empty)
{
  fearless::System s;
  static_cast<void>(s);
}

