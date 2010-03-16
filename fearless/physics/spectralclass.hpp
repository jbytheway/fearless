#ifndef FEARLESS_PHYSICS__SPECTRALCLASS_HPP
#define FEARLESS_PHYSICS__SPECTRALCLASS_HPP

#include <ostream>
#include <type_traits>

#include <boost/preprocessor/seq/enum.hpp>

#include <fearless/physics/api.hpp>

namespace fearless { namespace physics {

#define FEARLESS_PHYSICS_SPECTRALCLASS_VALUES() \
  /* O through M are 'normal' classes, in decreasing order of colour
   * temperature */ \
  (O) \
  (B) \
  (A) \
  (F) \
  (G) \
  (K) \
  (M) \
  (R) /* superceded by class C */ \
  (S) \
  (N) /* superceded by class C */ \
  (WC) \
  (WN) \
  (L) \
  (T) \
  (C) \
  (DA) /*  white dwarf A (Balmer lines, no He I or metals) */ \
  (DB) /*  white dwarf B (He I lines, no H or metals) */ \
  (DC) /*  white dwarf C, continuous spectrum */ \
  (DO) /*  white dwarf O, He II strong, He I or H */ \
  (DQ) /*  white dwarf Q, carbon features */ \
  (DZ) /*  white dwarf Z, metal lines only, no H or He */ \
  (D) /*  generic white dwarf, no additional data */ \
  (DX) \
  (Unknown) \
  (Max)

/** \brief Spectral class of star.
 *
 * \todo Do we need R and N?  What about L and T? DX?
 *
 * For more details see http://en.wikipedia.org/wiki/Spectral_type */
enum class SpectralClass {
  BOOST_PP_SEQ_ENUM(FEARLESS_PHYSICS_SPECTRALCLASS_VALUES())
};

FEARLESS_PHYSICS_API std::ostream&
operator<<(std::ostream&, SpectralClass const);

inline bool operator<(SpectralClass const l, SpectralClass const r) {
  typedef std::make_unsigned<SpectralClass>::type Integer;
  return Integer(l) < Integer(r);
}

}}

#endif // FEARLESS_PHYSICS__SPECTRALCLASS_HPP

