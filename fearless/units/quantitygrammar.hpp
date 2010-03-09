#ifndef FEARLESS_UNITS__QUANTITYGRAMMAR_HPP
#define FEARLESS_UNITS__QUANTITYGRAMMAR_HPP

#include <boost/spirit/include/qi_grammar.hpp>
#include <boost/spirit/include/phoenix_bind.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

#include <fearless/units/dimensionless.hpp>

namespace fearless { namespace units {

template<typename Iterator, typename Unit>
struct QuantityGrammar :
  boost::spirit::qi::grammar<Iterator, quantity<Unit, double>()>
{
  typedef quantity<Unit, double> quantity_type;

  template<typename BaseUnit>
  QuantityGrammar(BaseUnit baseUnit) : QuantityGrammar::base_type(start)
  {
    namespace qi = boost::spirit::qi;
    namespace px = boost::phoenix;
    double scale =
      quantity<dimensionless>(baseUnit / quantity_type::from_value(1));
    start = qi::double_[
      qi::_val = px::bind(quantity_type::from_value, boost::spirit::_1 * scale)
    ];
  }

  boost::spirit::qi::rule<Iterator, quantity<Unit, double>()> start;
};

}}

#endif // FEARLESS_UNITS__QUANTITYGRAMMAR_HPP

