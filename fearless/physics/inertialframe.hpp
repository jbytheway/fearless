#ifndef FEARLESS_PHYSICS__INERTIALFRAME_HPP
#define FEARLESS_PHYSICS__INERTIALFRAME_HPP

#include <fearless/physics/poincaretransform.hpp>

namespace fearless { namespace physics {

template<typename Reality>
class InertialFrame {
  public:
    virtual ~InertialFrame() = 0;

    virtual size_t depth() const = 0;

    virtual PoincareTransform<Reality, double>
    make_transform_from(InertialFrame const& f) const = 0;
  protected:
    InertialFrame() = default;
    InertialFrame(InertialFrame const&) = default;
    InertialFrame& operator=(InertialFrame const&) = default;
};

template<typename Reality>
inline InertialFrame<Reality>::~InertialFrame() = default;

}}

#endif // FEARLESS_PHYSICS__INERTIALFRAME_HPP

