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

    void boost(Velocity<double> const&);
    void advance(units::quantity<units::time, double> time);
  private:
    RelativeInertialFrame<Reality> frame_;
    units::quantity<units::time, double> travellers_time_;
};

template<typename Reality>
void Observer<Reality>::boost(Velocity<double> const& delta_v)
{
  auto lorentz = LorentzTransform<Reality, double>::boost(delta_v);
  frame_.push(PoincareTransform<Reality, double>(lorentz));
}

template<typename Reality>
void Observer<Reality>::advance(units::quantity<units::time, double> time)
{
  Event<Reality, double> translation{-time, Displacement<double>()};
  frame_.push(PoincareTransform<Reality, double>(translation));
  travellers_time_ += time;
}

}}

#endif // FEARLESS_PHYSICS__OBSERVER_HPP

