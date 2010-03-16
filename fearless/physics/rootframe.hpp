#ifndef FEARLESS_PHYSICS__ROOTFRAME_HPP
#define FEARLESS_PHYSICS__ROOTFRAME_HPP

#include <fearless/physics/inertialframe.hpp>

namespace fearless { namespace physics {

/** \brief The frame relative to which all others are defined.
 *
 * In the case of the Celestia data, this will be the J2000 ecliptic frame.
 */
template<typename Reality>
class RootFrame : public InertialFrame<Reality> {
  public:
    RootFrame(std::string name) : name_(std::move(name)) {}

    virtual size_t depth() const { return 0; }
    virtual std::string name() const { return name_; }

    virtual PoincareTransform<Reality, double>
    make_transform_from(InertialFrame<Reality> const& f) const;
  private:
    std::string name_;
};

template<typename Reality>
PoincareTransform<Reality, double>
RootFrame<Reality>::make_transform_from(
    InertialFrame<Reality> const& f
  ) const
{
  if (&f == this) return PoincareTransform<Reality, double>();
  assert(f.depth() > 0);
  return f.make_transform_from(*this).inverse();
}

}}

#endif // FEARLESS_PHYSICS__ROOTFRAME_HPP

