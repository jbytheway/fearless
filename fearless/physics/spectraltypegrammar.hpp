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
      ("L", SpectralClass::L)
      ("T", SpectralClass::T)
      //("Y", SpectralClass::T) // T/Y distinction still debated
      // Obsolete
      ("R", SpectralClass::R)
      ("N", SpectralClass::N)
      // Late giants
      ("S", SpectralClass::S)
      ("C", SpectralClass::C)
      // Subtypes of C we don't distinguish
      ("CH", SpectralClass::C)
      ("CN", SpectralClass::C)
      // Wolf-Rayet
      ("WC", SpectralClass::WC)
      ("WN", SpectralClass::WN)
      // White dwarf types
      ("DA", SpectralClass::DA)
      ("DB", SpectralClass::DB)
      ("DC", SpectralClass::DC)
      ("DG", SpectralClass::DZ) // DG is deprecated
      ("DF", SpectralClass::D) // e.g. HR 10267.  Don't know what this means
      ;
  }
} spectral_class_table;

struct LuminosityClassTable : boost::spirit::qi::symbols<char, LuminosityClass>
{
  LuminosityClassTable() {
    // We don't distinguish all the available subclasses
    add
      ("I",    LuminosityClass::Ib)
      ("Ia0",  LuminosityClass::Ia0)
      ("Ia",   LuminosityClass::Ia)
      ("Iab",  LuminosityClass::Ia)
      ("Ib",   LuminosityClass::Ib)
      ("II",   LuminosityClass::II)
      ("III",  LuminosityClass::III)
      ("IIIa", LuminosityClass::III)
      ("IIIb", LuminosityClass::III)
      ("IV",   LuminosityClass::IV)
      ("V",    LuminosityClass::V)
      ("Va",   LuminosityClass::V)
      ("VI",   LuminosityClass::VI)
      ("a",    LuminosityClass::Unknown) // Presumably a typo?
      ("b",    LuminosityClass::Unknown) // Presumably a typo?
      ("c",    LuminosityClass::Unknown) // ?
      ("d",    LuminosityClass::V) // Conjecture, by assuming it means "dwarf"?
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

    subclass %=
      (
        subclass_digit >>
        // Some subclasses have a fractional part (with either decimal
        // separator); ignore them
        qi::omit[-((qi::lit('.') | ',') >> qi::uint_)]
      ) |
      (
        // Some subclasses come in parentheses
        '(' >> subclass >> ')'
      );
    luminosity_class %=
      luminosity_class_table |
      ( '(' >> luminosity_class >> ')' );
    annenda =
      // Various other annenda that we ignore:
      +(
        qi::lit(':') /* Uncertain spectral value */ ||
        '.' /* (Usually "...", but also appears as "." and "..")
               Undescribed peculiarities */ ||
        '+' /* ? */ ||
        "comp" /* ? */ ||
        'e' /* Emission lines present */ ||
        'E' /* As in "M5E-M7e", probably a typo */ ||
        "(e)" /* ? */ ||
        'f' /* NIII and HeII emission */ ||
        'h' /* Hydrogen emission lines present */ ||
        'i' /* ? */ ||
        'm' /* Enhanced metal features */ ||
        "(m)" /* ? */ ||
        "neb" /* Nebula spectrum mixed in */ ||
        'n' /* Broad spectrum due to spinning */ ||
        "(n)" /* ? */ ||
        "(ne)" /* ? */ ||
        "(Nova)" /* ? */ ||
        'P' /* As in "GP", typo? */ ||
        'p' /* Unspecified peculiarity */ ||
        "(p)" /* ? */ ||
        'q' /* Red and blue shift lines present */ ||
        's' /* Sharp spectral lines */ ||
        "var" || 'v' /* Variable spectral feature */ ||
        'w' /* Weak lines */ ||
        "(w)" /* ? */
      );
    // Some types end with another parenthetic type, like "F5II(R)",
    // "M2e(S)-M6e", "G8/K0(V)(+G)" or "G3pe-K0(M3)"
    parenthetic_type =
      '(' >> -qi::lit('+') >> spectral_class_table >> -subclass >> ')';
    // The difference betwwen complete and incomplete is that complete must
    // have a spectral class at the start and one of the other components
    incomplete_spectral_type = qi::eps[_val = SpectralType()] >>
      (
        // "sd" means "subdwarf", aka luminosity class VI
        -qi::lit("sd")[
          (&_val)->*&SpectralType::luminosity_class = LuminosityClass::VI
        ] >>
        spectral_class_table[(&_val)->*&SpectralType::spectral_class = _1] ||
        subclass[(&_val)->*&SpectralType::subclass = _1] ||
        luminosity_class[
          (&_val)->*&SpectralType::luminosity_class = _1
        ] ||
        annenda ||
        parenthetic_type
      );
    spectral_type = qi::eps[_val = SpectralType()] >>
      // "sd" means "subdwarf", aka luminosity class VI
      -qi::lit("sd")[
          (&_val)->*&SpectralType::luminosity_class = LuminosityClass::VI
        ] >>
      spectral_class_table[(&_val)->*&SpectralType::spectral_class = _1] >>
      (
        subclass[(&_val)->*&SpectralType::subclass = _1] ||
        luminosity_class[
          (&_val)->*&SpectralType::luminosity_class = _1
        ] ||
        annenda ||
        parenthetic_type
      );
    // One entry may have more than one spectral type in, seperated by dashes
    // or slashes or nothing at all; ignore all but the first.
    /** \todo It would be nice to parse these ranges properly; they can be
     * ranges at different levels, so it's tough, especially because of strange
     * types like M2S and CNIVK1III */
    start %=
      // If any are juxtaposed then we insist the first is complete
      (
        spectral_type >>
        qi::omit[
          +(-(qi::lit('-') | '/') >> incomplete_spectral_type) >>
          -(qi::lit('-') | '/')
        ]
      ) |
      // If there are always explicit separators then we allow incomplete types
      (
        incomplete_spectral_type >>
        qi::omit[
          *((qi::lit('-') | '/') >> incomplete_spectral_type) >>
          -(qi::lit('-') | '/')
        ]
      );
  }

  boost::spirit::qi::uint_parser<SpectralSubclass, 10, 1, 1> subclass_digit;
  boost::spirit::qi::rule<Iterator, SpectralSubclass()> subclass;
  boost::spirit::qi::rule<Iterator, LuminosityClass()> luminosity_class;
  boost::spirit::qi::rule<Iterator, void()> annenda;
  boost::spirit::qi::rule<Iterator, void()> parenthetic_type;
  boost::spirit::qi::rule<Iterator, SpectralType()> incomplete_spectral_type;
  boost::spirit::qi::rule<Iterator, SpectralType()> spectral_type;
  boost::spirit::qi::rule<Iterator, SpectralType()> start;
};

}}

#endif // FEARLESS_PHYSICS__SPECTRALTYPEGRAMMAR_HPP

