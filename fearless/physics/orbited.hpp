#ifndef FEARLESS_PHYSICS__ORBITED_HPP
#define FEARLESS_PHYSICS__ORBITED_HPP

#include <memory>
#include <vector>

#include <fearless/physics/api.hpp>

namespace fearless { namespace physics {

class Orbiting;

class FEARLESS_PHYSICS_API Orbited {
  protected:
    Orbited();
    Orbited(Orbited const&) = delete;
    Orbited& operator=(Orbited const&) = delete;
    virtual ~Orbited() = 0;
  private:
    std::vector<std::unique_ptr<Orbiting>> orbiters_;
};

}}

#endif // FEARLESS_PHYSICS__ORBITED_HPP

