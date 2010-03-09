#include <fearless/physics/spectralclass.hpp>

#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/spirit/include/karma_string.hpp>
#include <boost/spirit/include/karma_generate.hpp>

#include <fearless/fatal.hpp>

namespace fearless { namespace physics {

namespace karma = boost::spirit::karma;

#define SPECTRALCLASS_ADD(r, d, value) \
  (SpectralClass::value, BOOST_PP_STRINGIZE(value))

namespace {

  struct SpectralClassKarmaTable : karma::symbols<SpectralClass, char const*>
  {
    SpectralClassKarmaTable() {
      add
        (SpectralClass::Unknown, "?")
        BOOST_PP_SEQ_FOR_EACH(
            SPECTRALCLASS_ADD, _, FEARLESS_PHYSICS_SPECTRALCLASS_VALUES()
          )
        ;
    }
  } spectral_class_karma_table;

}

std::ostream& operator<<(std::ostream& o, SpectralClass const c)
{
  auto sink = std::ostream_iterator<char>(o);
  if (!karma::generate(sink, spectral_class_karma_table, c)) {
    FEARLESS_FATAL("output error");
  }
  return o;
}

}}

