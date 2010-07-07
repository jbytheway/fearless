#ifndef FEARLESS_PHYSICS__APPARENT_MAGNITUDE_HPP
#define FEARLESS_PHYSICS__APPARENT_MAGNITUDE_HPP

namespace fearless { namespace physics {

template<typename T>
class ApparentMagnitude {
  public:
    static ApparentMagnitude from_value(T const value) {
      return ApparentMagnitude(value);
    }

    ApparentMagnitude() : value_(std::numeric_limits<T>::signaling_NaN()) {}

    ApparentMagnitude(
      AbsoluteMagnitude<T> const,
      units::quantity<units::parsec_length, T> const
    );

    T value() const { return value_; }
  private:
    ApparentMagnitude(T const value) : value_(value) {}

    T value_;
};

}}

#endif // FEARLESS_PHYSICS__APPARENT_MAGNITUDE_HPP

