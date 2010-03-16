#ifndef FEARLESS_PHYSICS__WORLDLINE_HPP
#define FEARLESS_PHYSICS__WORLDLINE_HPP

#include <fearless/units/area.hpp>
#include <fearless/maths/solve_quadratic.hpp>
#include <fearless/physics/minkowski_inner_product.hpp>

namespace fearless { namespace physics {

template<typename Reality, typename T>
class Worldline {
  public:
    Worldline(Event<Reality, T> const& pos, Event<Reality, T> const& dir) :
      position_{pos},
      direction_{dir}
    {
      assert(direction_.is_timelike());
      assert(direction_.temporal().value() > 0);
    }

    Event<Reality, T> visible_at() const;
  private:
    Event<Reality, T> position_;
    Event<Reality, T> direction_;
};

template<typename Reality, typename T>
Event<Reality, T> Worldline<Reality, T>::visible_at() const
{
  // We need to solve for the intersection of the worldline with the past light
  // cone (at the origin) This means solving a quadratic in the line parameter.
  T const a = direction_.minkowski_norm_squared() / units::square_metre;
  T const b =
    2.0*minkowski_inner_product(position_, direction_) / units::square_metre;
  T const c = position_.minkowski_norm_squared() / units::square_metre;
  // We always want the smaller root (the larger is on the future light cone)
  T const tau = boost::get<0>(maths::solve_quadratic(a, b, c));
  return position_+tau*direction_;
}

}}

#endif // FEARLESS_PHYSICS__WORLDLINE_HPP

