#ifndef FEARLESS_PHYSICS__COLOUR_OF_TEMPERATURE_HPP
#define FEARLESS_PHYSICS__COLOUR_OF_TEMPERATURE_HPP

#include <fearless/units/quantity.hpp>
#include <fearless/units/temperature.hpp>
#include <fearless/physics/api.hpp>
#include <fearless/physics/colour.hpp>

namespace fearless { namespace physics {

FEARLESS_PHYSICS_API Colour<float>
colour_of_temperature(units::quantity<units::temperature, float>);

}}

#endif // FEARLESS_PHYSICS__COLOUR_OF_TEMPERATURE_HPP

