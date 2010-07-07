#ifndef FEARLESS_PHYSICS__ABSOLUTE_MAGNITUDE_HPP
#define FEARLESS_PHYSICS__ABSOLUTE_MAGNITUDE_HPP

#include <fearless/units/length.hpp>
#include <fearless/physics/fwd.hpp>

namespace fearless { namespace physics {

template<typename T>
class AbsoluteMagnitude {
  public:
    static AbsoluteMagnitude from_value(T const value) {
      return AbsoluteMagnitude(value);
    }

    AbsoluteMagnitude(
      ApparentMagnitude<T> const,
      units::quantity<units::parsec_length, T> const
    );

    T value() const { return value_; }
  private:
    AbsoluteMagnitude(T const value) : value_(value) {}

    T value_;
};

}}

#endif // FEARLESS_PHYSICS__ABSOLUTE_MAGNITUDE_HPP

