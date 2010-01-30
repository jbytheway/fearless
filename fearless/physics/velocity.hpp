#ifndef FEARLESS_PHYSICS__VELOCITY_HPP
#define FEARLESS_PHYSICS__VELOCITY_HPP

#include <fearless/units/velocity.hpp>
#include <fearless/physics/fourvector.hpp>

namespace fearless { namespace physics {

template<typename T>
class Velocity : public ThreeVector<units::velocity, T> {
  public:
    typedef ThreeVector<units::velocity, T> base_type;
    typedef typename base_type::quantity_type quantity_type;

    Velocity(quantity_type x, quantity_type y, quantity_type z) :
      base_type(std::move(x), std::move(y), std::move(z))
    {}
};


}}

#endif // FEARLESS_PHYSICS__VELOCITY_HPP

