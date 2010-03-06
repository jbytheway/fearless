#ifndef FEARLESS_PHYSICS__SPECTRALTYPEGRAMMAR_HPP
#define FEARLESS_PHYSICS__SPECTRALTYPEGRAMMAR_HPP

#include <boost/spirit/home/phoenix/operator/self.hpp>
#include <boost/spirit/home/phoenix/operator/member.hpp>
#include <boost/spirit/home/qi/nonterminal/grammar.hpp>
#include <boost/spirit/home/qi/nonterminal/rule.hpp>
#include <boost/spirit/home/qi/string/symbols.hpp>
#include <boost/spirit/home/qi/operator/optional.hpp>
#include <boost/spirit/include/qi.hpp>

#include <fearless/physics/spectraltype.hpp>

namespace fearless { namespace physics {

struct SpectralClassTable : boost::spirit::qi::symbols<char, SpectralClass>
{
  SpectralClassTable() {
    add
      ("O", SpectralClass::O)
      ("B", SpectralClass::B)
      ("A", SpectralClass::A)
      ("F", SpectralClass::F)
      ("G", SpectralClass::G)
      ("K", SpectralClass::K)
      ("M", SpectralClass::M)
      ;
  }
} spectral_class_table;

struct LuminosityClassTable : boost::spirit::qi::symbols<char, LuminosityClass>
{
  LuminosityClassTable() {
    add
      ("Ia0", LuminosityClass::Ia0)
      ("Ia",  LuminosityClass::Ia)
      ("Ib",  LuminosityClass::Ib)
      ("II",  LuminosityClass::II)
      ("III", LuminosityClass::III)
      ("IV",  LuminosityClass::IV)
      ("V",   LuminosityClass::V)
      ("VI",  LuminosityClass::VI)
      ;
  }
} luminosity_class_table;

template<typename Iterator>
struct SpectralTypeGrammar :
  boost::spirit::qi::grammar<Iterator, SpectralType()>
{
  SpectralTypeGrammar() : SpectralTypeGrammar::base_type(start)
  {
    namespace qi = boost::spirit::qi;
    using qi::_val;
    using qi::_1;

    spectral_type = qi::eps[_val = SpectralType()] >>
      -spectral_class_table[(&_val)->*&SpectralType::spectral_class = _1] >>
      -(
        subclass[(&_val)->*&SpectralType::subclass = _1] >>
        // Some subclasses have a fractional part; ignore them
        -('.' >> qi::uint_)
      ) >>
      -luminosity_class_table[(&_val)->*&SpectralType::luminosity_class = _1] >>
      -qi::lit(':') /* Means uncertain spectral value; ignore it */ >>
      -qi::lit('e') /* Means emission lines present; ignore */;
    // One entry may have more than one spectral type in, seperated by dashes
    // or slashes; igore all but the first
    start %= spectral_type >>
      qi::omit[
        *((qi::lit('-') | '/') >> spectral_type)
      ];
  }

  boost::spirit::qi::uint_parser<SpectralSubclass, 10, 1, 1> subclass;
  boost::spirit::qi::rule<Iterator, SpectralType()> spectral_type;
  boost::spirit::qi::rule<Iterator, SpectralType()> start;
};

}}

#endif // FEARLESS_PHYSICS__SPECTRALTYPEGRAMMAR_HPP

