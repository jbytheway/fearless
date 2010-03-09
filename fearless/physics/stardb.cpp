#include <fearless/physics/stardb.hpp>

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/spirit/home/support/iterators/istream_iterator.hpp>
#include <boost/spirit/home/qi/parse.hpp>
#include <boost/spirit/home/qi/operator/kleene.hpp>
#include <boost/spirit/home/qi/operator/sequence.hpp>
#include <boost/spirit/home/qi/directive/omit.hpp>
#include <boost/spirit/home/qi/char/char.hpp>
#include <boost/spirit/home/qi/numeric/uint.hpp>
#include <boost/spirit/home/qi/numeric/real.hpp>
#include <boost/spirit/home/support/char_encoding/ascii.hpp>

#include <fearless/fatal.hpp>
#include <fearless/adapt_struct.hpp>
#include <fearless/units/quantity.hpp>
#include <fearless/units/angle.hpp>
#include <fearless/units/length.hpp>
#include <fearless/units/magnitude.hpp>
#include <fearless/units/quantitygrammar.hpp>
#include <fearless/physics/spectraltypegrammar.hpp>

namespace fearless { namespace physics {

namespace spirit = boost::spirit;
namespace qi = spirit::qi;

namespace {

  typedef uint64_t CatalogueNumber;

  struct CelestiaTxtStarData {
    CatalogueNumber catalogue_number;
    units::quantity<units::plane_angle, double> right_ascension;
    units::quantity<units::plane_angle, double> declination;
    units::quantity<units::length, double> distance;
    units::quantity<units::magnitude, double> apparent_magnitude;
    SpectralType spectral_type;
  };

}}}

// Adapt struct at global scope
FEARLESS_ADAPT_STRUCT(
  fearless::physics::CelestiaTxtStarData,
  (catalogue_number)
  (right_ascension)
  (declination)
  (distance)
  (apparent_magnitude)
  (spectral_type)
)

namespace fearless { namespace physics {

namespace {

  template<typename Iterator>
  struct CelestiaTxtStarDataGrammar :
    qi::grammar<Iterator, CelestiaTxtStarData()>
  {
    CelestiaTxtStarDataGrammar() :
      CelestiaTxtStarDataGrammar::base_type(start),
      degreeParser(units::degrees),
      lightYearParser(units::light_years),
      magnitudeParser(units::magnitudes)
    {
      start %= catalogueNumberParser >> qi::omit[*spirit::ascii::space] >>
        degreeParser >> qi::omit[spirit::ascii::space] >>
        degreeParser >> qi::omit[spirit::ascii::space] >>
        lightYearParser >> qi::omit[spirit::ascii::space] >>
        magnitudeParser >> qi::omit[spirit::ascii::space] >>
        spectralTypeParser;
    }

    units::QuantityGrammar<Iterator, units::plane_angle> degreeParser;
    units::QuantityGrammar<Iterator, units::length> lightYearParser;
    units::QuantityGrammar<Iterator, units::magnitude> magnitudeParser;
    qi::uint_parser<CatalogueNumber, 10, 1, -1> catalogueNumberParser;
    SpectralTypeGrammar<Iterator> spectralTypeParser;
    qi::rule<Iterator, CelestiaTxtStarData()> start;
  };

}

void StarDb::load_celestia_txt(std::istream& in)
{
  std::string line;
  if (!std::getline(in, line)) {
    FEARLESS_FATAL("error reading celestia txt file: no count");
  }

  typedef std::string::iterator it;

  {
    it first = line.begin();
    it const last = line.end();

    unsigned int count;

    bool result = qi::parse(
        first,
        last,
        qi::uint_,
        count
      );
    if (!result || first != last) {
      FEARLESS_FATAL(
          "error reading celestia txt file: not a count: '" <<
          line << "'"
        );
    }
  }

  std::vector<CelestiaTxtStarData> v;
  CelestiaTxtStarDataGrammar<it> lineParser;

  while (std::getline(in, line)) {
    it first = line.begin();
    it const last = line.end();
    CelestiaTxtStarData starData;

    bool result = qi::parse(
        first,
        last,
        lineParser,
        starData
      );
    if (!result || first != last) {
      auto next_newline = std::find(first, last, '\n');
      std::string rest_of_line(first, next_newline);
      FEARLESS_FATAL(
          "error reading celestia txt file; line: '" << line <<
          "' rest of line: '" << rest_of_line << "'"
        );
    }
    v.push_back(starData);
  }
}

}}

