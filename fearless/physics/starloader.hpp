#ifndef FEARLESS_PHYSICS__STARLOADER_HPP
#define FEARLESS_PHYSICS__STARLOADER_HPP

#include <iosfwd>

#include <boost/filesystem/path.hpp>

#include <fearless/physics/api.hpp>
#include <fearless/physics/cataloguenumber.hpp>
#include <fearless/physics/equatorialcoordinates.hpp>
#include <fearless/physics/spectraltype.hpp>
#include <fearless/physics/displacement.hpp>
#include <fearless/physics/star.hpp>

namespace fearless { namespace physics {

/** \brief A means to read stars from various sources
 *
 * Having loaded the stars, the StarLoader can be given to a StarIndex to
 * provide efficient access.
 *
 * Heavily inspired by the Celectia class StarDatabase (which is Copyright
 * (C) 2001-2008, Chris Laurel <claurel@shatters.net>).
 */
class FEARLESS_PHYSICS_API StarLoader {
  public:
    void load_celestia_txt(std::istream&);
    void load_celestia_txt(boost::filesystem::path const&);
    void add_star(
        CatalogueNumber const,
        EquatorialCoordinates<double> const&,
        SpectralType const&
      );
    void add_star(
        CatalogueNumber const,
        Displacement<double> const&,
        SpectralType const&
      );

    std::vector<Star> const& stars() const { return stars_; }
  private:
    std::vector<Star> stars_;
};

}}

#endif // FEARLESS_PHYSICS__STARLOADER_HPP

