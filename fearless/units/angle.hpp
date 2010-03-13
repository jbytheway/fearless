#ifndef FEARLESS_UNITS__ANGLE_HPP
#define FEARLESS_UNITS__ANGLE_HPP

#include <boost/units/systems/angle/degrees.hpp>
#include <boost/units/systems/si/plane_angle.hpp>

namespace fearless { namespace units {

typedef boost::units::degree::plane_angle degree_angle;
using boost::units::degree::degree;
using boost::units::degree::degrees;

typedef boost::units::si::plane_angle radian_angle;
using boost::units::si::radian;
using boost::units::si::radians;

}}

#endif // FEARLESS_UNITS__ANGLE_HPP

