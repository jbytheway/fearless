#include <fearless/physics/luminosityclass.hpp>

#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/spirit/include/karma_string.hpp>
#include <boost/spirit/include/karma_generate.hpp>

#include <fearless/fatal.hpp>

namespace fearless { namespace physics {

namespace karma = boost::spirit::karma;

#define LUMINOSITYCLASS_ADD(r, d, value) \
  (LuminosityClass::value, BOOST_PP_STRINGIZE(value))

namespace {

  struct LuminosityClassKarmaTable :
    karma::symbols<LuminosityClass, char const*>
  {
    LuminosityClassKarmaTable() {
      add
        (LuminosityClass::Unknown, "")
        BOOST_PP_SEQ_FOR_EACH(
            LUMINOSITYCLASS_ADD, _, FEARLESS_PHYSICS_LUMINOSITYCLASS_VALUES()
          )
        ;
    }
  } luminosity_class_karma_table;

}

std::ostream& operator<<(std::ostream& o, LuminosityClass const c)
{
  auto sink = std::ostream_iterator<char>(o);
  if (!karma::generate(sink, luminosity_class_karma_table, c)) {
    FEARLESS_FATAL("output error");
  }
  return o;
}

}}

