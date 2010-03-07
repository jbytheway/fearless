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
  SpectralType(
      SpectralClass sp,
      boost::optional<SpectralSubclass> su,
      LuminosityClass lu
    ) :
    spectral_class(sp),
    subclass(su),
    luminosity_class(lu)
  {}

  SpectralClass spectral_class;
  boost::optional<SpectralSubclass> subclass;
  LuminosityClass luminosity_class;
};

inline bool operator==(SpectralType const& l, SpectralType const& r) {
  return l.spectral_class == r.spectral_class &&
    l.subclass == r.subclass &&
    l.luminosity_class == r.luminosity_class;
}

inline std::ostream& operator<<(std::ostream& o, SpectralType const& t) {
  o << t.spectral_class;
  if (t.subclass) { o << *t.subclass; }
  o << t.luminosity_class;
  return o;
}

}}

#endif // FEARLESS_PHYSICS__SPECTRALTYPE_HPP

