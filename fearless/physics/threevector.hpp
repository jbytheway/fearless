#ifndef FEARLESS_PHYSICS__THREEVECTOR_HPP
#define FEARLESS_PHYSICS__THREEVECTOR_HPP

#include <boost/mpl/times.hpp>
#include <boost/units/is_unit.hpp>
#include <boost/units/get_system.hpp>
#include <boost/units/get_dimension.hpp>

namespace fearless { namespace physics {

template<typename Unit, typename T>
class ThreeVector {
  BOOST_MPL_ASSERT((boost::units::is_unit<Unit>));
  public:
    typedef Unit unit;
    typedef typename boost::units::get_system<unit>::type system;
    typedef typename boost::units::get_dimension<unit>::type dimension;
    typedef typename boost::mpl::times<dimension, dimension>::type dim_squared;
    typedef typename boost::units::unit<dimension, system> unit_squared;
    typedef units::quantity<Unit, T> quantity_type;
    typedef units::quantity<unit_squared, T> quantity_squared_type;

    ThreeVector() :
      values_{units::zero, units::zero, units::zero}
    {}
    ThreeVector(quantity_type x, quantity_type y, quantity_type z) :
      values_{std::move(x), std::move(y), std::move(z)}
    {}

    quantity_type const& x() const { return std::get<0>(values_); }
    quantity_type const& y() const { return std::get<1>(values_); }
    quantity_type const& z() const { return std::get<2>(values_); }

    quantity_squared_type const& norm_squared() const {
      return x()*x()+y()*y()+z()*z();
    }
    quantity_type const& norm() const { return sqrt(norm_squared()); }
    
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
    std::tuple<quantity_type, quantity_type, quantity_type> values_;
};

namespace threevector_detail {

template<typename Sys, typename Dim1, typename T1, typename Dim2, typename T2>
struct mul {
  typedef ThreeVector<
    boost::units::unit<typename boost::mpl::times<Dim1, Dim2>::type, Sys>,
    decltype(T1(0)*T2(0))
  > type;
};

template<typename Sys, typename Dim1, typename T1, typename Dim2, typename T2>
struct div {
  typedef ThreeVector<
    boost::units::unit<typename boost::mpl::divides<Dim1, Dim2>::type, Sys>,
    decltype(T1(0)/T2(0))
  > type;
};

}

/** Multiply a 3-vector by a scalar */
template<typename Sys, typename Dim1, typename T1, typename Dim2, typename T2>
inline typename threevector_detail::mul<Sys, Dim1, T1, Dim2, T2>::type
operator*(
    ThreeVector<boost::units::unit<Dim1, Sys>, T1> const& v,
    units::quantity<boost::units::unit<Dim2, Sys>, T2> const& s
  ) {
  return typename threevector_detail::mul<Sys, Dim1, T1, Dim2, T2>::type{
      v.x() * s, v.y() * s, v.z() * s
    };
}

/** Divide a 3-vector by a scalar */
template<typename Sys, typename Dim1, typename T1, typename Dim2, typename T2>
inline typename threevector_detail::div<Sys, Dim1, T1, Dim2, T2>::type
operator/(
    ThreeVector<boost::units::unit<Dim1, Sys>, T1> const& v,
    units::quantity<boost::units::unit<Dim2, Sys>, T2> const& s
  ) {
  return typename threevector_detail::div<Sys, Dim1, T1, Dim2, T2>::type{
      v.x() / s, v.y() / s, v.z() / s
    };
}

}}

#endif // FEARLESS_PHYSICS__THREEVECTOR_HPP

