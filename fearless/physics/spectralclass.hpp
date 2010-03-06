#ifndef FEARLESS_PHYSICS__SPECTRALCLASS_HPP
#define FEARLESS_PHYSICS__SPECTRALCLASS_HPP

namespace fearless { namespace physics {

enum class SpectralClass {
  O,
  B,
  A,
  F,
  G,
  K,
  M,
  R, // superceded by class C
  S,
  N, // superceded by class C
  WC,
  WN,
  Unknown,
  L,
  T,
  C,
  DA, // white dwarf A (Balmer lines, no He I or metals)
  DB, // white dwarf B (He I lines, no H or metals)
  DC, // white dwarf C, continuous spectrum
  DO, // white dwarf O, He II strong, He I or H
  DQ, // white dwarf Q, carbon features
  DZ, // white dwarf Z, metal lines only, no H or He
  D,  // generic white dwarf, no additional data
  DX,
  Max,
};

}}

#endif // FEARLESS_PHYSICS__SPECTRALCLASS_HPP

