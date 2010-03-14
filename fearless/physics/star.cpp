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

std::ostream& operator<<(std::ostream& o, Star const& s)
{
  o << s.catalogue_number() << ' ' << s.position();
  return o;
}

}}

