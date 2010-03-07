#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <boost/test/test_tools.hpp>

#include <fearless/physics/spectraltypegrammar.hpp>

namespace fearless { namespace physics {

BOOST_AUTO_TEST_CASE(spectraltypegrammar_parses)
{
  const char* names[] = {
    // The first few from stars.txt
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
    "F3/F5V",
    // Some other oddities
    "M:",
    "B9p",
    "C5p",
    "CNIV",
    "CNIVK1III",
    "Am...",
    "R...",
    "B2IVne+...",
    "K4IIIb",
    "B8MNp",
    "A1Vs",
    "F2+...",
    "F4IVws",
    "A",
    "G:III/IV+..",
    "A9Iab:",
    "F6Vawvar",
    "sdG8",
    "Beq",
    "B9.5IIIMNp.",
    "DG",
    "M2.5IIIa",
    "WN2",
    "M2S",
    "Mb",
    "A3II/III(m)",
    "DAs",
    "F7/8V(p)",
    "M2Ia0-a...",
    "A-F",
    "DF",
    "A2psh",
    "K3I-II",
    "S4,2v",
    "K3Ve-M0Ve(T)",
    "M2e(S)-M6e",
    "F8/G0V(w)",
    "Md",
    "B5:(ne)",
    "B3V(n)",
    "B2V(e)",
    "O7f",
    "F5II(R)",
    "WC8",
    "CH",
    "A7Vni",
    "DC",
    "B/Ape",
    "B9.5/A0III/",
    "M5E-M7e",
    "K0(V)",
    "K(1)V",
    "G3pe-K0(M3)",
    "Mc",
    "sdB(Nova)",
    "K2II-IIIcomp",
    "DB:p",
    "G8/K0(V)(+G)",
    "GP"
  };
  SpectralTypeGrammar<char const*> spectral_type_parser;
  BOOST_FOREACH(char const* name, names) {
    char const* start = name;
    char const* const end = name+std::strlen(name);
    namespace qi = boost::spirit::qi;
    SpectralType type;
    BOOST_REQUIRE_MESSAGE(
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

