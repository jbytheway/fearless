#ifndef FEARLESS_PHYSICS__POINCARETRANSFORM_HPP
#define FEARLESS_PHYSICS__POINCARETRANSFORM_HPP

#include <fearless/physics/event.hpp>
#include <fearless/physics/lorentztransform.hpp>

namespace fearless { namespace physics {

template<typename Reality, typename T>
class PoincareTransform {
  public:
    PoincareTransform() = default;
    explicit PoincareTransform(
        Event<Reality, T> const& translation
      ) :
      translation_(translation),
      lorentz_()
    {}
    explicit PoincareTransform(
        LorentzTransform<Reality, T> const& lorentz
      ) :
      translation_(),
      lorentz_(lorentz)
    {}
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
      return lorentz_.apply(x) + translation_;
    }

    PoincareTransform inverse() const {
      auto const li = lorentz_.inverse();
      return PoincareTransform(li.apply(-translation_), li);
    }

    friend PoincareTransform
    operator*(PoincareTransform const& l, PoincareTransform const& r) {
      // Transform on left, so this means do r, then l
      return PoincareTransform(
          l.apply(r.translation_),
          l.lorentz_ * r.lorentz_
        );
    }
  private:
    Event<Reality, T> translation_;
    LorentzTransform<Reality, T> lorentz_;
};

}}

#endif // FEARLESS_PHYSICS__POINCARETRANSFORM_HPP

