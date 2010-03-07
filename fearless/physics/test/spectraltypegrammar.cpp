#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <boost/test/test_tools.hpp>

#include <fearless/physics/spectraltypegrammar.hpp>

namespace fearless { namespace physics {

// Test that the given name parses to the given type
struct SpectralTypeTest {
  const char* name;
  SpectralType type;
};

BOOST_AUTO_TEST_CASE(spectraltypegrammar_parses)
{
  boost::optional<SpectralSubclass> subclassUnknown;
  SpectralTypeTest tests[] = {
    // The first few from stars.txt
#define T(name, spectral, subclass, luminosity) \
    { name, SpectralType(                       \
        SpectralClass::spectral, subclass, LuminosityClass::luminosity) }
    T("F5", F, 5, Unknown),
    T("K3V", K, 3, V),
    T("B9", B, 9, Unknown),
    T("F0V", F, SpectralSubclass(0), V),
    T("G8III", G, 8, III),
    T("M0V:", M, SpectralSubclass(0), V),
    T("G0", G, SpectralSubclass(0), Unknown),
    T("M6e-M8.5e", M, 6, Unknown),
    T("G5", G, 5, Unknown),
    T("F6V", F, 6, V),
    T("A2", A, 2, Unknown),
    T("K4III", K, 4, III),
    T("K0", K, SpectralSubclass(0), Unknown),
    T("K2", K, 2, Unknown),
    T("F3V", F, 3, V),
    T("K5", K, 5, Unknown),
    T("G5", G, 5, Unknown),
    T("G0", G, SpectralSubclass(0), Unknown),
    T("K2", K, 2, Unknown),
    /** \bug Should get lum class here */
    T("G8/K0III/IV", G, 8, Unknown),
    T("F2V", F, 2, V),
    T("G0V", G, SpectralSubclass(0), V),
    T("G3IV", G, 3, IV),
    T("F7V", F, 7, V),
    T("G5V", G, 5, V),
    /** \bug Should get lum class here */
    T("F3/F5V", F, 3, Unknown),
    // Some other oddities
    T("M:", M, subclassUnknown, Unknown),
    T("B9p", B, 9, Unknown),
    T("C5p", C, 5, Unknown),
    T("CNIV", C, subclassUnknown, IV),
    T("CNIVK1III", C, subclassUnknown, IV),
    T("Am...", A, subclassUnknown, Unknown),
    T("R...", R, subclassUnknown, Unknown),
    T("B2IVne+...", B, 2, IV),
    T("K4IIIb", K, 4, III),
    T("B8MNp", B, 8, Unknown),
    T("A1Vs", A, 1, V),
    T("F2+...", F, 2, Unknown),
    T("F4IVws", F, 4, IV),
    T("A", A, subclassUnknown, Unknown),
    /** \bug Should get lum class here */
    T("G:III/IV+..", G, subclassUnknown, Unknown),
    T("A9Iab:", A, 9, Ia),
    T("F6Vawvar", F, 6, V),
    T("sdG8", G, 8, VI),
    T("Beq", B, subclassUnknown, Unknown),
    T("B9.5IIIMNp.", B, 9, III),
    T("DG", DZ, subclassUnknown, Unknown),
    T("M2.5IIIa", M, 2, III),
    T("WN2", WN, 2, Unknown),
    T("M2S", M, 2, Unknown),
    T("Mb", M, subclassUnknown, Unknown),
    T("A3II/III(m)", A, 3, II),
    T("DAs", DA, subclassUnknown, Unknown),
    /** \bug Should get lum class here */
    T("F7/8V(p)", F, 7, Unknown),
    T("M2Ia0-a...", M, 2, Ia0),
    T("A-F", A, subclassUnknown, Unknown),
    T("DF", D, subclassUnknown, Unknown),
    T("A2psh", A, 2, Unknown),
    T("K3I-II", K, 3, Ib),
    T("S4,2v", S, 4, Unknown),
    T("K3Ve-M0Ve(T)", K, 3, V),
    T("M2e(S)-M6e", M, 2, Unknown),
    /** \bug Should get lum class here */
    T("F8/G0V(w)", F, 8, Unknown),
    T("Md", M, subclassUnknown, V),
    T("B5:(ne)", B, 5, Unknown),
    T("B3V(n)", B, 3, V),
    T("B2V(e)", B, 2, V),
    T("O7f", O, 7, Unknown),
    T("F5II(R)", F, 5, II),
    T("WC8", WC, 8, Unknown),
    T("CH", C, subclassUnknown, Unknown),
    T("A7Vni", A, 7, V),
    T("DC", DC, subclassUnknown, Unknown),
    T("B/Ape", B, subclassUnknown, Unknown),
    /** \bug Should get lum class here */
    T("B9.5/A0III/", B, 9, Unknown),
    T("M5E-M7e", M, 5, Unknown),
    T("K0(V)", K, SpectralSubclass(0), V),
    T("K(1)V", K, 1, V),
    T("G3pe-K0(M3)", G, 3, Unknown),
    T("Mc", M, subclassUnknown, Unknown),
    T("sdB(Nova)", B, subclassUnknown, VI),
    T("K2II-IIIcomp", K, 2, II),
    T("DB:p", DB, subclassUnknown, Unknown),
    /** \bug Should get lum class here */
    T("G8/K0(V)(+G)", G, 8, Unknown),
    T("GP", G, subclassUnknown, Unknown)
#undef T
  };
  SpectralTypeGrammar<char const*> spectral_type_parser;
  BOOST_FOREACH(SpectralTypeTest const& test, tests) {
    char const* const name = test.name;
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
    BOOST_CHECK_EQUAL(type, test.type);
  }
}

}}

