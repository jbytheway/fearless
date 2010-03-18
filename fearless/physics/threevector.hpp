#ifndef FEARLESS_PHYSICS__THREEVECTOR_HPP
#define FEARLESS_PHYSICS__THREEVECTOR_HPP

#include <boost/mpl/times.hpp>
#include <boost/units/is_quantity.hpp>
#include <boost/units/get_system.hpp>
#include <boost/units/get_dimension.hpp>
#include <boost/units/cmath.hpp>
#include <boost/units/io.hpp>

#include <fearless/units/zero.hpp>
#include <fearless/maths/isthreevector.hpp>

namespace fearless { namespace physics {

template<typename Quantity>
class ThreeVector {
  BOOST_MPL_ASSERT((boost::units::is_quantity<Quantity>));
  public:
    typedef Quantity quantity;
    typedef typename quantity::unit_type unit;
    typedef typename quantity::value_type value_type;
    typedef typename
      boost::units::multiply_typeof_helper<quantity, quantity>::type
      quantity_squared;

    ThreeVector() :
      values_{units::zero, units::zero, units::zero}
    {}
    ThreeVector(quantity x, quantity y, quantity z) :
      values_{std::move(x), std::move(y), std::move(z)}
    {}

    template<typename U>
    explicit ThreeVector(
        ThreeVector<units::quantity<unit, U>> const& v
      ) : values_{v.x(), v.y(), v.z()}
    {}

    quantity const& x() const { return std::get<0>(values_); }
    quantity const& y() const { return std::get<1>(values_); }
    quantity const& z() const { return std::get<2>(values_); }

    quantity_squared norm_squared() const {
      return x()*x()+y()*y()+z()*z();
    }
    quantity norm() const { return quantity(sqrt(norm_squared())); }

    ThreeVector& operator*=(value_type r) {
      std::get<0>(values_) *= r;
      std::get<1>(values_) *= r;
      std::get<2>(values_) *= r;
      return *this;
    }

    ThreeVector& operator/=(value_type r) {
      std::get<0>(values_) /= r;
      std::get<1>(values_) /= r;
      std::get<2>(values_) /= r;
      return *this;
    }

    friend inline bool
    operator==(ThreeVector const& l, ThreeVector const& r) {
      return l.values_ == r.values_;
    }

    friend std::ostream&
    operator<<(std::ostream& o, ThreeVector const& v) {
      o << '[' << v.x() << ", " << v.y() << ", " << v.z() << ']';
      return o;
    }
  private:
    std::tuple<quantity, quantity, quantity> values_;
};

/** Multiply a 3-vector by a unit */
template<typename Q1, typename Dim, typename System>
inline ThreeVector<
  typename boost::units::multiply_typeof_helper<
    Q1,
    units::quantity<
      boost::units::unit<Dim, System>,
      typename Q1::value_type
    >
  >::type
>
operator*(ThreeVector<Q1> const& v, boost::units::unit<Dim, System> const& u) {
  typedef ThreeVector<
    typename boost::units::multiply_typeof_helper<
      Q1,
      units::quantity<
        boost::units::unit<Dim, System>,
        typename Q1::value_type
      >
    >::type
  > type;
  return type{v.x() * u, v.y() * u, v.z() * u};
}

/** Negate a 3-vector */
template<typename Q1>
inline ThreeVector<Q1>
operator-(ThreeVector<Q1> const& v) {
  return ThreeVector<Q1>{-v.x(), -v.y(), -v.z()};
}

/** Multiply a 3-vector by a scalar */
template<typename Q1, typename Q2>
inline ThreeVector<typename boost::units::multiply_typeof_helper<Q1, Q2>::type>
operator*(ThreeVector<Q1> const& v, Q2 const& s) {
  typedef
    ThreeVector<typename boost::units::multiply_typeof_helper<Q1, Q2>::type>
    type;
  return type{v.x() * s, v.y() * s, v.z() * s};
}

/** Divide a 3-vector by a scalar */
template<typename Q1, typename Q2>
inline ThreeVector<typename boost::units::divide_typeof_helper<Q1, Q2>::type>
operator/(ThreeVector<Q1> const& v, Q2 const& s) {
  typedef
    ThreeVector<typename boost::units::divide_typeof_helper<Q1, Q2>::type>
    type;
  return type{v.x() / s, v.y() / s, v.z() / s};
}

/** Add a 3-vector to a 3-vector */
template<typename Q1>
inline ThreeVector<Q1>
operator+(ThreeVector<Q1> const& l, ThreeVector<Q1> const& r) {
  return ThreeVector<Q1>{l.x() + r.x(), l.y() + r.y(), l.z() + r.z()};
}

/** Subtract a 3-vector from a 3-vector */
template<typename Q1>
inline ThreeVector<Q1>
operator-(ThreeVector<Q1> const& l, ThreeVector<Q1> const& r) {
  return ThreeVector<Q1>{l.x() - r.x(), l.y() - r.y(), l.z() - r.z()};
}

/** Cross product aka vector product */
template<typename Q1, typename Q2>
inline ThreeVector<typename boost::units::multiply_typeof_helper<Q1, Q2>::type>
cross_product(ThreeVector<Q1> const& l, ThreeVector<Q2> const& r) {
  typedef
    ThreeVector<typename boost::units::multiply_typeof_helper<Q1, Q2>::type>
    type;
  return type{
    l.y()*r.z() - l.z()*r.y(),
    l.z()*r.x() - l.x()*r.z(),
    l.x()*r.y() - l.y()*r.x()
  };
}

/** Dot product aka scalar product */
template<typename Q1, typename Q2>
inline typename boost::units::multiply_typeof_helper<Q1, Q2>::type
dot_product(ThreeVector<Q1> const& l, ThreeVector<Q2> const& r) {
  return l.x()*r.x() + l.y()*r.y() + l.z()*r.z();
}

/** ADL-found overload of very_near_to */
template<typename Q>
bool very_near_to(
    ThreeVector<Q> const& x,
    ThreeVector<Q> const& y,
    double tolerance
  ) {
  return (x-y).norm()/(x.norm()+y.norm()) < tolerance;
}

namespace detail {

  struct ConvertibleFromThreeVector {
    template<typename Quantity>
    ConvertibleFromThreeVector(ThreeVector<Quantity> const&);
  };

}

}}

// Specialize IsThreeVector
namespace fearless { namespace maths {

template<typename DerivedThreeVector>
struct IsThreeVector<
  DerivedThreeVector,
  typename std::enable_if<
    std::is_convertible<
      DerivedThreeVector,
      fearless::physics::detail::ConvertibleFromThreeVector
    >::value
  >::type
> : std::true_type {};

}}

#endif // FEARLESS_PHYSICS__THREEVECTOR_HPP

