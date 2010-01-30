#ifndef FEARLESS_UNITS__ZERO_HPP
#define FEARLESS_UNITS__ZERO_HPP

#include <fearless/units/quantity.hpp>

namespace fearless { namespace units {

struct zero_t {
  template<typename Unit>
  operator quantity<Unit, double>() const { return quantity<Unit, double>(0); }
};

static const zero_t zero{};

}}

#endif // FEARLESS_UNITS__ZERO_HPP

