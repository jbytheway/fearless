#ifndef FEARLESS_PHYSICS__EVENT_HPP
#define FEARLESS_PHYSICS__EVENT_HPP

#include <fearless/units/length.hpp>
#include <fearless/units/time.hpp>
#include <fearless/physics/fourvector.hpp>

namespace fearless { namespace physics {

template<typename Reality, typename T>
class Event : public FourVector<units::quantity<units::length, T>> {
  public:
    typedef FourVector<units::quantity<units::length, T>> base_type;
    typedef typename base_type::quantity quantity;
    typedef typename base_type::three_vector three_vector;

    Event() : base_type{quantity(), three_vector()} {}
    Event(base_type const& v) : base_type{v} {}
    Event(quantity t_c, three_vector v) :
      base_type{std::move(t_c), std::move(v)}
    {}
    Event(units::quantity<units::time, T> t, three_vector v) :
      base_type{std::move(t)*Reality::c.quantity(), std::move(v)}
    {}
};

}}

#endif // FEARLESS_PHYSICS__EVENT_HPP

