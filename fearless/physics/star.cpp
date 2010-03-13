#include <fearless/physics/star.hpp>

namespace fearless { namespace physics {

Star::Star(
    CatalogueNumber const num,
    Displacement<double> const& position,
    SpectralType const&
  ) :
  catalogue_number_(num),
  position_(position)
{}

}}

