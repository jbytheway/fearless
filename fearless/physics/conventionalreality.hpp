#ifndef FEARLESS_PHYSICS__CONVENTIONALREALITY_HPP
#define FEARLESS_PHYSICS__CONVENTIONALREALITY_HPP

#include <boost/units/systems/si/codata/universal_constants.hpp>

#include <fearless/units/quantity.hpp>
#include <fearless/units/velocity.hpp>

namespace fearless { namespace physics {

class ConventionalReality {
  public:
    static units::quantity<units::velocity, double> c() {
      return boost::units::si::constants::codata::c;
    }
};

}}

#endif // FEARLESS_PHYSICS__CONVENTIONALREALITY_HPP

