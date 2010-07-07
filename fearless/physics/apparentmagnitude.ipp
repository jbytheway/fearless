#ifndef FEARLESS_PHYSICS__APPARENT_MAGNITUDE_IPP
#define FEARLESS_PHYSICS__APPARENT_MAGNITUDE_IPP

#include <fearless/physics/apparentmagnitude.hpp>

#include <fearless/physics/absolutemagnitude.hpp>

namespace fearless { namespace physics {

template<typename T>
ApparentMagnitude<T>::ApparentMagnitude(
  AbsoluteMagnitude<T> const absoluteMagnitude,
  units::quantity<units::parsec_length, T> const distance
) :
  value_(absoluteMagnitude.value() - 5 + 5*log10(distance/units::parsec))
{
}

}}

#endif // FEARLESS_PHYSICS__APPARENT_MAGNITUDE_IPP

