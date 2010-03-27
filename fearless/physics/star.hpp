#ifndef FEARLESS_PHYSICS__STAR_HPP
#define FEARLESS_PHYSICS__STAR_HPP

#include <boost/shared_ptr.hpp>

#include <fearless/units/temperature.hpp>
#include <fearless/physics/cataloguenumber.hpp>
#include <fearless/physics/displacement.hpp>
#include <fearless/physics/spectraltype.hpp>

namespace fearless { namespace physics {

class FEARLESS_PHYSICS_API Star {
  public:
    Star(
        CatalogueNumber const,
        Displacement<double> const&,
        SpectralType const&
      );

    CatalogueNumber catalogue_number() const { return catalogue_number_; }
    Displacement<double> const& position() const { return position_; }
    units::quantity<units::temperature, float> temperature() const;
  private:
    CatalogueNumber catalogue_number_;
    Displacement<double> position_;
    class Impl;
    boost::shared_ptr<Impl> impl_;
};

std::ostream& operator<<(std::ostream&, Star const&);

}}

#endif // FEARLESS_PHYSICS__STAR_HPP

