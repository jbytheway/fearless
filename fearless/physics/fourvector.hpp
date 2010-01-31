#ifndef FEARLESS_PHYSICS__FOURVECTOR_HPP
#define FEARLESS_PHYSICS__FOURVECTOR_HPP

#include <boost/mpl/times.hpp>

#include <fearless/physics/threevector.hpp>

namespace fearless { namespace physics {

template<typename Quantity>
class FourVector {
  BOOST_MPL_ASSERT((boost::units::is_quantity<Quantity>));
  public:
    typedef Quantity quantity;
    typedef ThreeVector<quantity> three_vector;

    FourVector(quantity t, three_vector s) :
      temporal_{std::move(t)},
      spatial_{std::move(s)}
    {}

    quantity const& temporal() const { return temporal_; }
    quantity const& t() const { return temporal_; }
    three_vector const& spatial() const { return spatial_; }
    quantity const& x() const { return spatial_.x(); }
    quantity const& y() const { return spatial_.x(); }
    quantity const& z() const { return spatial_.x(); }
  private:
    quantity temporal_;
    ThreeVector<Quantity> spatial_;
};

/** Multiply a 4-vector by a scalar */
template<typename Q1, typename Q2>
inline FourVector<typename boost::units::multiply_typeof_helper<Q1, Q2>::type>
operator*(FourVector<Q1> const& v, Q2 const& s) {
  typedef
    FourVector<typename boost::units::multiply_typeof_helper<Q1, Q2>::type>
    type;
  return type{v.temporal() * s, v.spatial() * s};
}

}}

#endif // FEARLESS_PHYSICS__FOURVECTOR_HPP

