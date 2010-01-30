#ifndef FEARLESS_PHYSICS__LORENTZTRANSFORM_HPP
#define FEARLESS_PHYSICS__LORENTZTRANSFORM_HPP

#include <complex>

#include <fearless/maths/speciallinearmatrix.hpp>
#include <fearless/maths/specialorthogonalmatrix.hpp>
#include <fearless/maths/hermitianmatrix.hpp>
#include <fearless/maths/matrix_element.hpp>
#include <fearless/maths/careful_functions.hpp>
#include <fearless/units/quantity.hpp>
#include <fearless/units/dimensionless.hpp>
#include <fearless/physics/velocity.hpp>
#include <fearless/physics/displacement.hpp>
#include <fearless/physics/event.hpp>

namespace fearless { namespace physics {

/** Lorentz transform
 *
 * This is a Lorentz transformation preserving the direction of time and of
 * positive determinant, i.e. in SO+(1,3), the identity component of SO(1,3).
 *
 * All these transforms are linear (they fix the origin).  (If it included
 * the translation component it would be a Poincaré transform).
 *
 * Internally, represented as an element of SL_2(C).  See
 * http://en.wikipedia.org/wiki/SL2(C)#Lorentz_transformations
 */
template<typename Reality, typename T>
class LorentzTransform {
  public:
    typedef maths::SpecialLinearMatrix<std::complex<T>, 2> Representation;

    /** Creates a LorentzTransform into the frame of an object moving with
     * given velocity */
    static LorentzTransform boost(Velocity<T> const&);

    Event<Reality, T> apply(Event<Reality, T> const&) const;
  private:
    Representation representation_;
};

template<typename Reality, typename T>
LorentzTransform<Reality, T>
LorentzTransform<Reality, T>::boost(Velocity<T> const& v)
{
  units::quantity<units::velocity, T> const v_norm = v.norm();
  ThreeVector<units::dimensionless, T> const n = v / v_norm;
  ThreeVector<units::dimensionless, T> const pole(0, 0, 1);
  auto const rotate_n_to_pole =
    maths::SpecialOrthogonalMatrix<T>::rotation_from_to(n, pole);
  T const scale =
    sqrt(maths::careful_functions::one_plus_x_over_one_minus_x(v/Reality::c));
  auto const boost_at_pole = Representation::scale_by(scale);
  return rotation(rotate_n_to_pole) * LorentzTransform(boost_at_pole) *
    rotation(rotate_n_to_pole.inverse());
}

template<typename Reality, typename T>
Event<Reality, T>
LorentzTransform<Reality, T>::apply(Event<Reality, T> const& x) const
{
  typedef maths::HermitianMatrix<units::quantity<units::length, T>, 2>
    EventAsMatrix;
  EventAsMatrix const x_as_matrix{
      x.t() + x.z(),
      std::complex<units::quantity<units::length, T>>{x.x(), -x.y()},
      x.t() - x.z()
    };
  EventAsMatrix const result_as_matrix = x_as_matrix.conjugate(representation_);
  auto const m00 = maths::matrix_element<0, 0>(result_as_matrix);
  auto const m01 = maths::matrix_element<0, 1>(result_as_matrix);
  auto const m11 = maths::matrix_element<1, 1>(result_as_matrix);
  T const two{2};
  Event<Reality, T> result{
    (m00+m11)/two,
    Displacement<T>{real(m01), -imag(m01), (m00-m11)/two}
  };
  return result;
}

}}

#endif // FEARLESS_PHYSICS__LORENTZTRANSFORM_HPP

