#ifndef FEARLESS_PHYSICS__MINKOWSKI_INNER_PRODUCT_HPP
#define FEARLESS_PHYSICS__MINKOWSKI_INNER_PRODUCT_HPP

namespace fearless { namespace physics {

template<typename Quantity>
inline typename boost::units::multiply_typeof_helper<Quantity, Quantity>::type
minkowski_inner_product(
    FourVector<Quantity> const& l,
    FourVector<Quantity> const& r
  )
{
  return dot_product(l.spatial(), r.spatial()) - l.temporal()*r.temporal();
}

}}

#endif // FEARLESS_PHYSICS__MINKOWSKI_INNER_PRODUCT_HPP

