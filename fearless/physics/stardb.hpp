#ifndef FEARLESS_PHYSICS__STARDB_HPP
#define FEARLESS_PHYSICS__STARDB_HPP

#include <istream>

namespace fearless { namespace physics {

/** \brief A collection of stars, together with the means to read from data
 *
 * Heavily inspired by the Celectia class of the same name (which is Copyright
 * (C) 2001-2008, Chris Laurel <claurel@shatters.net>).
 */
class StarDb {
  public:
    void load_celestia_txt(std::istream&);
};

}}

#endif // FEARLESS_PHYSICS__STARDB_HPP

