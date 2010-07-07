#include <fearless/physics/starloader.hpp>

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
#include <boost/filesystem/fstream.hpp>

#include <fearless/fatal.hpp>
#include <fearless/adapt_struct.hpp>
#include <fearless/units/quantity.hpp>
#include <fearless/units/angle.hpp>
#include <fearless/units/length.hpp>
#include <fearless/units/quantitygrammar.hpp>
#include <fearless/physics/spectraltypegrammar.hpp>
#include <fearless/physics/absolutemagnitude.ipp>
#include <fearless/physics/apparentmagnitude.hpp>

namespace fearless { namespace physics {

namespace spirit = boost::spirit;
namespace qi = spirit::qi;

namespace {

  struct CelestiaTxtStarData {
    CatalogueNumber catalogue_number;
    units::quantity<units::radian_angle, double> right_ascension;
    units::quantity<units::radian_angle, double> declination;
    units::quantity<units::length, double> distance;
    ApparentMagnitude<double> apparent_magnitude;
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
      lightYearParser(units::light_years)
    {
      namespace px = boost::phoenix;
      /** \todo ApparentMagnitude is supposed to be bolometric.  Are the
       * Hipparcos catalogue numbers? */
      magnitudeParser = qi::double_[
        qi::_val = px::bind(&ApparentMagnitude<double>::from_value, qi::_1)
      ];
      start %= catalogueNumberParser >> qi::omit[*spirit::ascii::space] >>
        degreeParser >> qi::omit[spirit::ascii::space] >>
        degreeParser >> qi::omit[spirit::ascii::space] >>
        lightYearParser >> qi::omit[spirit::ascii::space] >>
        magnitudeParser >> qi::omit[spirit::ascii::space] >>
        spectralTypeParser;
    }

    qi::uint_parser<CatalogueNumber, 10, 1, -1> catalogueNumberParser;
    units::QuantityGrammar<Iterator, units::radian_angle> degreeParser;
    units::QuantityGrammar<Iterator, units::length> lightYearParser;
    qi::rule<Iterator, ApparentMagnitude<double>()> magnitudeParser;
    SpectralTypeGrammar<Iterator> spectralTypeParser;
    qi::rule<Iterator, CelestiaTxtStarData()> start;
  };

}

void StarLoader::load_celestia_txt(std::istream& in)
{
  reference_frame_ = "J2000 Ecliptic";

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
    add_star(
        starData.catalogue_number,
        EquatorialCoordinates<double>(
          starData.right_ascension, starData.declination, starData.distance
        ),
        starData.spectral_type,
        AbsoluteMagnitude<double>(
          starData.apparent_magnitude,
          units::quantity<units::parsec_length, double>(starData.distance)
        )
      );
  }
}

void StarLoader::load_celestia_txt(boost::filesystem::path const& path)
{
  boost::filesystem::ifstream is(path);
  if (!is) {
    FEARLESS_FATAL("error opening " << path);
  }
  load_celestia_txt(is);
}

void StarLoader::add_star(
    CatalogueNumber const num,
    EquatorialCoordinates<double> const& coords,
    SpectralType const& spectralType,
    AbsoluteMagnitude<double> const& absoluteMagnitude
  )
{
  Displacement<double> const position = coords.to_celestial_cartesian();
  add_star(num, position, spectralType, absoluteMagnitude);
}

void StarLoader::add_star(
    CatalogueNumber const num,
    Displacement<double> const& position,
    SpectralType const& spectralType,
    AbsoluteMagnitude<double> const& absoluteMagnitude
  )
{
  stars_.push_back(Star(num, position, spectralType, absoluteMagnitude));
}

}}

