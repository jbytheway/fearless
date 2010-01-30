#ifndef FEARLESS_PHYSICS__FOURVECTOR_HPP
#define FEARLESS_PHYSICS__FOURVECTOR_HPP

#include <boost/mpl/times.hpp>
#include <boost/units/is_unit.hpp>

#include <fearless/physics/threevector.hpp>

namespace fearless { namespace physics {

template<typename Unit, typename T>
class FourVector {
  BOOST_MPL_ASSERT((boost::units::is_unit<Unit>));
  public:
    typedef units::quantity<Unit, T> quantity_type;
    typedef ThreeVector<Unit, T> three_vector;

    FourVector(quantity_type t, three_vector s) :
      temporal_{std::move(t)},
      spatial_{std::move(s)}
    {}

    quantity_type const& temporal() const { return temporal_; }
    quantity_type const& t() const { return temporal_; }
    three_vector const& spatial() const { return spatial_; }
    quantity_type const& x() const { return spatial_.x(); }
    quantity_type const& y() const { return spatial_.x(); }
    quantity_type const& z() const { return spatial_.x(); }
  private:
    quantity_type temporal_;
    ThreeVector<Unit, T> spatial_;
};

/** Multiply a 4-vector by a scalar */
template<
  typename System, typename Dimension1, typename T1,
  typename Dimension2, typename T2
>
inline FourVector<
    boost::units::unit<
      typename boost::mpl::times<Dimension1, Dimension2>::type, System
    >,
    decltype(T1(0)*T2(0))
  >
operator*(
    FourVector<boost::units::unit<Dimension1, System>, T1> const& v,
    units::quantity<boost::units::unit<Dimension2, System>, T2> const& s
  ) {
  return FourVector<
      boost::units::unit<
        typename boost::mpl::times<Dimension1, Dimension2>::type, System
      >,
      decltype(T1(0)*T2(0))
    >{
      v.temporal() * s, v.spatial() * s
    };
}

}}

#endif // FEARLESS_PHYSICS__FOURVECTOR_HPP

