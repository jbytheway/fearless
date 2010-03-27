#ifndef FEARLESS_PHYSICS__ACCELERATION_HPP
#define FEARLESS_PHYSICS__ACCELERATION_HPP

#include <fearless/units/acceleration.hpp>
#include <fearless/physics/fourvector.hpp>

namespace fearless { namespace physics {

template<typename T>
class Acceleration :
  public ThreeVector<units::quantity<units::acceleration, T>> {
  public:
    typedef ThreeVector<units::quantity<units::acceleration, T>> base_type;
    typedef typename base_type::quantity quantity;

    Acceleration() = default;
    Acceleration(base_type const& v) : base_type(v) {}
    Acceleration(quantity x, quantity y, quantity z) :
      base_type(std::move(x), std::move(y), std::move(z))
    {}
};


}}

#endif // FEARLESS_PHYSICS__ACCELERATION_HPP

