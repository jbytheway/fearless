#ifndef FEARLESS_PHYSICS__ABSOLUTE_MAGNITUDE_IPP
#define FEARLESS_PHYSICS__ABSOLUTE_MAGNITUDE_IPP

#include <fearless/physics/absolutemagnitude.hpp>

#include <fearless/physics/apparentmagnitude.hpp>

namespace fearless { namespace physics {

template<typename T>
AbsoluteMagnitude<T>::AbsoluteMagnitude(
  ApparentMagnitude<T> const apparentMagnitude,
  units::quantity<units::parsec_length, T> const distance
) :
  value_(apparentMagnitude.value() + 5 - 5*log10(distance/units::parsec))
{
}

}}

#endif // FEARLESS_PHYSICS__ABSOLUTE_MAGNITUDE_IPP

