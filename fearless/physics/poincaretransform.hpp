#ifndef FEARLESS_PHYSICS__POINCARETRANSFORM_HPP
#define FEARLESS_PHYSICS__POINCARETRANSFORM_HPP

#include <fearless/physics/event.hpp>
#include <fearless/physics/lorentztransform.hpp>

namespace fearless { namespace physics {

template<typename Reality, typename T>
class PoincareTransform {
  public:
    PoincareTransform() = default;
    PoincareTransform(
        Event<Reality, T> const& translation,
        LorentzTransform<Reality, T> const& lorentz
      ) :
      translation_(translation),
      lorentz_(lorentz)
    {}

    Event<Reality, T> const& translation() const { return translation_; }
    LorentzTransform<Reality, T> const& lorentz() const { return lorentz_; }
    Event<Reality, T> apply(Event<Reality, T> const& x) const {
      return lorentz_.apply(x + translation_);
    }

    PoincareTransform inverse() const {
      return PoincareTransform(
          lorentz_.apply(-translation_),
          lorentz_.inverse()
        );
    }

    friend PoincareTransform
    operator*(PoincareTransform const& l, PoincareTransform const& r) {
      // Transform on left, so this means do r, then l
      return PoincareTransform(
          l.inverse().apply(r.translation_),
          l.lorentz_ * r.lorentz_
        );
    }
  private:
    Event<Reality, T> translation_;
    LorentzTransform<Reality, T> lorentz_;
};

}}

#endif // FEARLESS_PHYSICS__POINCARETRANSFORM_HPP

