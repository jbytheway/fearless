#ifndef FEARLESS_PHYSICS__OBSERVER_HPP
#define FEARLESS_PHYSICS__OBSERVER_HPP

#include <fearless/physics/relativeinertialframe.hpp>

namespace fearless { namespace physics {

template<typename Reality>
class Observer {
  public:
    explicit Observer(RelativeInertialFrame<Reality> frame) :
      frame_{std::move(frame)},
      travellers_time_{units::zero}
    {}

    RelativeInertialFrame<Reality> const& frame() const { return frame_; }
    units::quantity<units::time, double> travellers_time() const {
      return travellers_time_;
    }

    PoincareTransform<Reality, double>
    make_transform_from(InertialFrame<Reality> const& f) {
      return frame_.make_transform_from(f);
    }
  private:
    RelativeInertialFrame<Reality> frame_;
    units::quantity<units::time, double> travellers_time_;
};

}}

#endif // FEARLESS_PHYSICS__OBSERVER_HPP

