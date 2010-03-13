#ifndef FEARLESS_PHYSICS__STAR_HPP
#define FEARLESS_PHYSICS__STAR_HPP

#include <fearless/physics/cataloguenumber.hpp>
#include <fearless/physics/displacement.hpp>
#include <fearless/physics/spectraltype.hpp>

namespace fearless { namespace physics {

class Star {
  public:
    Star(
        CatalogueNumber const,
        Displacement<double> const&,
        SpectralType const&
      );
  private:
    CatalogueNumber catalogue_number_;
    Displacement<double> position_;
};

}}

#endif // FEARLESS_PHYSICS__STAR_HPP

