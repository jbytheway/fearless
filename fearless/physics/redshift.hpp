#ifndef FEARLESS_PHYSICS__REDSHIFT_HPP
#define FEARLESS_PHYSICS__REDSHIFT_HPP

#include <fearless/units/temperature.hpp>
#include <fearless/physics/gamma.hpp>
#include <fearless/physics/velocity.hpp>
#include <fearless/physics/displacement.hpp>
#include <fearless/physics/absolutemagnitude.hpp>

namespace fearless { namespace physics {

template<typename Reality, typename T>
class Redshift {
  public:
    /** \brief Create Redshift for speed and angle
     *
     * \param cos_theta The cosine of the angle between the direction of
     * motion and the direction of the light.  Thus, is 1.0 for an object
     * moving towards the observer, and -1.0 for an object moving away.  If in
     * doubt, use the other constructor.
     */
    template<typename U, typename V>
    Redshift(
      units::quantity<units::velocity, U> const v,
      V const cos_theta
    ) {
      init(v, cos_theta);
    }

    template<typename U, typename V>
    Redshift(
      Velocity<U> const& velocity_in_observer_frame,
      Displacement<V> const& position_in_observer_frame
    ) {
      auto const v_norm = velocity_in_observer_frame.norm();
      auto const light_direction =
        -position_in_observer_frame/position_in_observer_frame.norm();
      auto const cos_theta =
        dot_product(velocity_in_observer_frame, light_direction)/v_norm;
      init(v_norm, cos_theta);
    }

    units::quantity<units::temperature, T>
    apply(units::quantity<units::temperature, T> const t) const {
      return t*z_plus_1_;
    }

    template<typename U>
    AbsoluteMagnitude<U>
    apply(AbsoluteMagnitude<U> const mag) const {
      // Intensities should be multiplied by z_plus_1_^4.  Magnitudes live in
      // -2.5*log10 space, so we add instead.  Nega
      return AbsoluteMagnitude<U>::from_value(
        mag.value() + 4*-2.5*log10(z_plus_1_)
      );
    }
  private:
    template<typename U, typename V>
    void init(
      units::quantity<units::velocity, U> const v,
      V const cos_theta
    ) {
      if (v == units::zero) {
        z_plus_1_ = 1;
      } else {
        assert(fabs(cos_theta) <= 1.0);
        z_plus_1_ = 1.0/gamma<Reality>(v)/(1.0-v*cos_theta/Reality::c());
      }
    }

    T z_plus_1_;
};

}}

#endif // FEARLESS_PHYSICS__REDSHIFT_HPP

