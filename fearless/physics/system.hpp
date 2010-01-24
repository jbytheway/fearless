#ifndef FEARLESS_PHYSICS__SYSTEM_HPP
#define FEARLESS_PHYSICS__SYSTEM_HPP

#include <fearless/physics/barycentre.hpp>

namespace fearless { namespace physics {

/** Defines a star system, keeping track of all the things therein. */
class System {
  private:
    Barycentre barycentre_;
};

}}

#endif // FEARLESS_PHYSICS__SYSTEM_HPP

