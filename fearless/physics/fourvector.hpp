#ifndef FEARLESS_PHYSICS__FOURVECTOR_HPP
#define FEARLESS_PHYSICS__FOURVECTOR_HPP

#include <boost/mpl/times.hpp>

#include <fearless/units/velocity.hpp>
#include <fearless/physics/threevector.hpp>

namespace fearless { namespace physics {

template<typename Quantity>
class FourVector {
  BOOST_MPL_ASSERT((boost::units::is_quantity<Quantity>));
  public:
    typedef Quantity quantity;
    typedef ThreeVector<quantity> three_vector;
    typedef typename quantity::value_type value_type;
    typedef typename
      boost::units::multiply_typeof_helper<quantity, quantity>::type
      quantity_squared;
    typedef typename boost::units::divide_typeof_helper<
      quantity, units::quantity<units::velocity, value_type>
    >::type quantity_over_velocity;

    FourVector(quantity t, three_vector s) :
      temporal_{std::move(t)},
      spatial_{std::move(s)}
    {}

    quantity const& temporal() const { return temporal_; }
    quantity const& t() const { return temporal_; }
    template<typename Reality>
    quantity_over_velocity t_over_c() const {
      return temporal_/Reality::c();
    }
    three_vector const& spatial() const { return spatial_; }
    quantity const& x() const { return spatial_.x(); }
    quantity const& y() const { return spatial_.y(); }
    quantity const& z() const { return spatial_.z(); }

    quantity_squared l2_norm_squared() const {
      return temporal()*temporal()+spatial().norm_squared();
    }
    quantity l2_norm() const { return sqrt(l2_norm_squared()); }

    quantity_squared minkowski_norm_squared() const {
      return spatial().norm_squared()-temporal()*temporal();
    }

    bool is_timelike() const {
      return minkowski_norm_squared() < quantity_squared::from_value(0.0);
    }

    friend inline bool
    operator==(FourVector const& l, FourVector const& r) {
      return l.temporal_ == r.temporal_ && l.spatial_ == r.spatial_;
    }

    friend std::ostream&
    operator<<(std::ostream& o, FourVector const& v) {
      o << '[' << v.t() << ", " << v.spatial() << ']';
      return o;
    }
  private:
    quantity temporal_;
    ThreeVector<Quantity> spatial_;
};

/** Negate a 4-vector */
template<typename Q1>
inline FourVector<Q1>
operator-(FourVector<Q1> const& v) {
  return FourVector<Q1>{-v.t(), -v.spatial()};
}

/** Multiply a 4-vector by a scalar */
template<typename Q1, typename Q2>
inline FourVector<typename boost::units::multiply_typeof_helper<Q1, Q2>::type>
operator*(FourVector<Q1> const& v, Q2 const& s) {
  typedef
    FourVector<typename boost::units::multiply_typeof_helper<Q1, Q2>::type>
    type;
  return type{v.temporal() * s, v.spatial() * s};
}

template<typename Q1, typename Q2>
inline FourVector<typename boost::units::multiply_typeof_helper<Q1, Q2>::type>
operator*(Q2 const& s, FourVector<Q1> const& v) {
  typedef
    FourVector<typename boost::units::multiply_typeof_helper<Q1, Q2>::type>
    type;
  return type{v.temporal() * s, v.spatial() * s};
}

/** Add a 4-vector to a 4-vector */
template<typename Q1>
inline FourVector<Q1>
operator+(FourVector<Q1> const& l, FourVector<Q1> const& r) {
  return FourVector<Q1>{l.t() + r.t(), l.spatial() + r.spatial()};
}

/** Subtract a 4-vector from a 4-vector */
template<typename Q1>
inline FourVector<Q1>
operator-(FourVector<Q1> const& l, FourVector<Q1> const& r) {
  return FourVector<Q1>{l.t() - r.t(), l.spatial() - r.spatial()};
}

/** ADL-found overload of very_near_to */
template<typename Q>
bool very_near_to(
    FourVector<Q> const& x,
    FourVector<Q> const& y,
    double tolerance
  ) {
  return (x-y).l2_norm()/(x.l2_norm()+y.l2_norm()) < tolerance;
}

}}

#endif // FEARLESS_PHYSICS__FOURVECTOR_HPP

