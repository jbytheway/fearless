#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <boost/test/test_tools.hpp>

#include <fearless/physics/spectraltypegrammar.hpp>

namespace fearless { namespace physics {

BOOST_AUTO_TEST_CASE(spectraltypegrammar_parses)
{
  const char* names[] = {
      "F5",
      "K3V",
      "B9",
      "F0V",
      "G8III",
      "M0V:",
      "G0",
      "M6e-M8.5e",
      "G5",
      "F6V",
      "A2",
      "K4III",
      "K0",
      "K2",
      "F3V",
      "K5",
      "G5",
      "G0",
      "K2",
      "G8/K0III/IV",
      "F2V",
      "G0V",
      "G3IV",
      "F7V",
      "G5V",
      "F3/F5V"
    };
  SpectralTypeGrammar<char const*> spectral_type_parser;
  BOOST_FOREACH(char const* name, names) {
    char const* start = name;
    char const* const end = name+std::strlen(name);
    namespace qi = boost::spirit::qi;
    SpectralType type;
    BOOST_CHECK_MESSAGE(
        qi::parse(start, end, spectral_type_parser, type),
        "Trying to parse "+std::string(name)
      );
    BOOST_CHECK_MESSAGE(
        start == end,
        "Failed to parse to end of "+std::string(name)
      );
  }
}

}}

