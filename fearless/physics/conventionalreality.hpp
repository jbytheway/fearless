#ifndef FEARLESS_PHYSICS__CONVENTIONALREALITY_HPP
#define FEARLESS_PHYSICS__CONVENTIONALREALITY_HPP

#include <boost/units/systems/si/codata/universal_constants.hpp>

#include <fearless/units/quantity.hpp>
#include <fearless/units/velocity.hpp>

namespace fearless { namespace physics {

class ConventionalReality {
  public:
    struct c_t {
      operator units::quantity<units::velocity, double>() const {
        return boost::units::si::constants::codata::c;
      }
      units::quantity<units::velocity, double> quantity() const {
        return boost::units::si::constants::codata::c;
      }
    };
    static c_t const c;
};

}}

#endif // FEARLESS_PHYSICS__CONVENTIONALREALITY_HPP

