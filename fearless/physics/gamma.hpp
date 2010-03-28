#ifndef FEARLESS_PHYSICS__GAMMA_HPP
#define FEARLESS_PHYSICS__GAMMA_HPP

#include <fearless/units/quantity.hpp>
#include <fearless/units/velocity.hpp>

namespace fearless { namespace physics {

template<typename Reality, typename T>
T gamma(units::quantity<units::velocity, T> const v) {
  auto const v_squared = v*v;
  auto const c_squared = Reality::c.quantity()*Reality::c.quantity();
  assert(v_squared < c_squared);
  return 1.0/sqrt(1.0-v_squared/c_squared);
}

template<typename Reality, typename Velocity>
typename Velocity::value_type gamma(Velocity const& v) {
  auto const v_norm_squared = v.norm_squared();
  auto const c_squared = Reality::c.quantity()*Reality::c.quantity();
  assert(v_norm_squared < c_squared);
  return 1.0/sqrt(1.0-v_norm_squared/c_squared);
}

}}

#endif // FEARLESS_PHYSICS__GAMMA_HPP

