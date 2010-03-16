#ifndef FEARLESS_PHYSICS__LORENTZTRANSFORM_HPP
#define FEARLESS_PHYSICS__LORENTZTRANSFORM_HPP

#include <complex>

#include <fearless/maths/speciallinearmatrix.hpp>
#include <fearless/maths/specialorthogonalmatrix.hpp>
#include <fearless/maths/hermitianmatrix.hpp>
#include <fearless/maths/matrix_element.hpp>
#include <fearless/maths/dump_matrix.hpp>
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
    typedef maths::SpecialLinearMatrix<maths::Complex<T>> Representation;

    static LorentzTransform boost(Velocity<T> const&);

    static LorentzTransform rotation(maths::SpecialOrthogonalMatrix<T> const&);

    LorentzTransform() = default;

    LorentzTransform inverse() const;

    Event<Reality, T> apply(Event<Reality, T> const&, bool debug=false) const;

    void dump(std::ostream&) const;

    friend inline LorentzTransform
    operator*(LorentzTransform const& l, LorentzTransform const& r) {
      return LorentzTransform(l.representation_ * r.representation_);
    }
  private:
    explicit LorentzTransform(Representation r) :
      representation_(std::move(r))
    {}

    Representation representation_;
};

/** \brief Creates a LorentzTransform into the frame of an object moving
 * with given velocity */
template<typename Reality, typename T>
LorentzTransform<Reality, T>
LorentzTransform<Reality, T>::boost(Velocity<T> const& v)
{
  units::quantity<units::velocity, T> const v_norm = v.norm();
  assert(v_norm < Reality::c.quantity());
  ThreeVector<units::quantity<units::dimensionless, T>> const n = v / v_norm;
  ThreeVector<units::quantity<units::dimensionless, T>> const pole(0, 0, 1);
  auto const rotate_n_to_pole =
    maths::SpecialOrthogonalMatrix<T>::rotation_from_to(n, pole);
  T const beta = v_norm/Reality::c.quantity();
  T const scale = sqrt((1-beta) / (1+beta));
  auto const boost_at_pole = Representation::scale_by(scale);
  return rotation(rotate_n_to_pole.inverse()) *
    LorentzTransform(boost_at_pole) *
    rotation(rotate_n_to_pole);
}

/** \brief Creates a LorentzTranform corresponding to the given rotation of
 * space */
template<typename Reality, typename T>
LorentzTransform<Reality, T>
LorentzTransform<Reality, T>::rotation(
    maths::SpecialOrthogonalMatrix<T> const& r
  )
{
  boost::math::quaternion<T> q = r.as_quaternion();
  maths::Complex<T> const z1(q.R_component_1(), q.R_component_4());
  maths::Complex<T> const z2(q.R_component_3(), q.R_component_2());
  return LorentzTransform(Representation(z1.conj(), -z2, z2.conj(), z1));
}

template<typename Reality, typename T>
LorentzTransform<Reality, T>
LorentzTransform<Reality, T>::inverse() const
{
  return LorentzTransform(representation_.inverse());
}

template<typename Reality, typename T>
Event<Reality, T>
LorentzTransform<Reality, T>::apply(
    Event<Reality, T> const& x,
    bool debug
  ) const
{
  typedef maths::HermitianMatrix<units::quantity<units::length, T>, 2>
    EventAsMatrix;
  EventAsMatrix const x_as_matrix{
      x.t() + x.z(),
      maths::Complex<units::quantity<units::length, T>>{x.x(), -x.y()},
      x.t() - x.z()
    };
  if (debug) {
    std::cout << "x_as_matrix:\n";
    maths::dump_matrix(std::cout, x_as_matrix);
  }
  EventAsMatrix const result_as_matrix = x_as_matrix.conjugate(representation_);
  if (debug) {
    std::cout << "result_as_matrix:\n";
    maths::dump_matrix(std::cout, result_as_matrix);
  }
  auto const m00 = maths::matrix_element<0, 0>(result_as_matrix);
  auto const m01 = maths::matrix_element<0, 1>(result_as_matrix);
  auto const m11 = maths::matrix_element<1, 1>(result_as_matrix);
  T const two{2};
  Event<Reality, T> result{
    (m00+m11)/two,
    Displacement<T>{m01.real(), -m01.imag(), (m00-m11)/two}
  };
  return result;
}

template<typename Reality, typename T>
void LorentzTransform<Reality, T>::dump(std::ostream& o) const
{
  o << representation_;
}

}}

#endif // FEARLESS_PHYSICS__LORENTZTRANSFORM_HPP

