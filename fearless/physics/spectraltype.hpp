#ifndef FEARLESS_PHYSICS__SPECTRALTYPE_HPP
#define FEARLESS_PHYSICS__SPECTRALTYPE_HPP

#include <fearless/physics/spectralclass.hpp>
#include <fearless/physics/spectralsubclass.hpp>
#include <fearless/physics/luminosityclass.hpp>

namespace fearless { namespace physics {

struct SpectralType {
  SpectralType() :
    spectral_class(SpectralClass::Unknown),
    luminosity_class(LuminosityClass::Unknown)
  {}

  SpectralClass spectral_class;
  boost::optional<SpectralSubclass> subclass;
  LuminosityClass luminosity_class;
};

}}

#endif // FEARLESS_PHYSICS__SPECTRALTYPE_HPP

