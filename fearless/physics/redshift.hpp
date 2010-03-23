#ifndef FEARLESS_PHYSICS__REDSHIFT_HPP
#define FEARLESS_PHYSICS__REDSHIFT_HPP

#include <fearless/physics/gamma.hpp>

namespace fearless { namespace physics {

template<typename Reality, typename T>
class Redshift {
  public:
    template<typename U, typename V>
    Redshift(
      units::quantity<units::velocity, U> const v,
      V const cos_theta
    ) :
      z_plus_1_(gamma<Reality>(v)*(1.0+v*cos_theta/Reality::c.quantity()))
    {}

    units::quantity<units::temperature, T>
    apply(units::quantity<units::temperature, T> const t) const {
      return t*z_plus_1_;
    }
  private:
    T z_plus_1_;
};

}}

#endif // FEARLESS_PHYSICS__REDSHIFT_HPP

