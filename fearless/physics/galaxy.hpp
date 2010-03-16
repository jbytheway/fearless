#ifndef FEARLESS_PHYSICS__GALAXY_HPP
#define FEARLESS_PHYSICS__GALAXY_HPP

#include <fearless/physics/starindex.hpp>
#include <fearless/physics/rootframe.hpp>

namespace fearless { namespace physics {

template<typename Reality>
class Galaxy {
  public:
    explicit Galaxy(StarIndex const& star_index) :
      star_index_(star_index),
      root_frame_{new RootFrame<Reality>()}
    {}

    StarIndex const& star_index() const { return star_index_; }
    std::shared_ptr<RootFrame<Reality> const> const& root_frame() const {
      return root_frame_;
    }
  private:
    StarIndex const& star_index_;
    std::shared_ptr<RootFrame<Reality> const> root_frame_;
};

}}

#endif // FEARLESS_PHYSICS__GALAXY_HPP

