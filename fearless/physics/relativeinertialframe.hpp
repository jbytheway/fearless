#ifndef FEARLESS_PHYSICS__RELATIVEINERTIALFRAME_HPP
#define FEARLESS_PHYSICS__RELATIVEINERTIALFRAME_HPP

#include <fearless/physics/poincaretransform.hpp>
#include <fearless/physics/inertialframe.hpp>

namespace fearless { namespace physics {

template<typename Reality>
class RelativeInertialFrame : InertialFrame<Reality> {
  public:
    explicit RelativeInertialFrame(
        std::shared_ptr<InertialFrame<Reality> const> r,
        std::string name
      ) :
      relative_to_{std::move(r)},
      depth_{relative_to_->depth()+1},
      name_(std::move(name))
    {}

    std::shared_ptr<InertialFrame<Reality> const> const& relative_to() const {
      return relative_to_;
    }
    virtual size_t depth() const { return depth_; }
    virtual std::string name() const { return name_; }

    virtual PoincareTransform<Reality, double>
    make_transform_from(InertialFrame<Reality> const& f) const;
  private:
    std::shared_ptr<InertialFrame<Reality> const> relative_to_;
    PoincareTransform<Reality, double> transform_;
    size_t depth_;
    std::string name_;
};

template<typename Reality>
PoincareTransform<Reality, double>
RelativeInertialFrame<Reality>::make_transform_from(
    InertialFrame<Reality> const& f
  ) const
{
  /** \bug This implementation should work, but it's not the most efficient */
  if (&f == this) return PoincareTransform<Reality, double>();
  if (depth_ >= f.depth()) {
    auto const higherTrans = relative_to_->make_transform_from(f);
    return transform_ * higherTrans;
  }
  return f.make_transform_from(*this).inverse();
}

}}

#endif // FEARLESS_PHYSICS__RELATIVEINERTIALFRAME_HPP

