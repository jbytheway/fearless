#ifndef FEARLESS_PHYSICS__VELOCITY_HPP
#define FEARLESS_PHYSICS__VELOCITY_HPP

#include <fearless/units/velocity.hpp>
#include <fearless/physics/fourvector.hpp>

namespace fearless { namespace physics {

template<typename T>
class Velocity : public ThreeVector<units::quantity<units::velocity, T>> {
  public:
    typedef ThreeVector<units::quantity<units::velocity, T>> base_type;
    typedef typename base_type::quantity quantity;

    Velocity() = default;
    Velocity(base_type const& v) : base_type(v) {}
    Velocity(quantity x, quantity y, quantity z) :
      base_type(std::move(x), std::move(y), std::move(z))
    {}
};


}}

#endif // FEARLESS_PHYSICS__VELOCITY_HPP

