#ifndef FEARLESS_PHYSICS__DISPLACEMENT_HPP
#define FEARLESS_PHYSICS__DISPLACEMENT_HPP

#include <fearless/units/length.hpp>
#include <fearless/physics/threevector.hpp>

namespace fearless { namespace physics {

template<typename T>
class Displacement : public ThreeVector<units::length, T> {
  public:
    typedef ThreeVector<units::length, T> base_type;
    typedef typename base_type::quantity_type quantity_type;

    Displacement() = default;
    Displacement(base_type const& v) : base_type(v) {}
    Displacement(quantity_type x, quantity_type y, quantity_type z) :
      base_type{std::move(x), std::move(y), std::move(z)}
    {}
};


}}

#endif // FEARLESS_PHYSICS__DISPLACEMENT_HPP

