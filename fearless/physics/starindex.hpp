#ifndef FEARLESS_PHYSICS__STARINDEX_HPP
#define FEARLESS_PHYSICS__STARINDEX_HPP

#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/function.hpp>

#include <fearless/physics/star.hpp>

namespace fearless { namespace physics {

class StarLoader;

/** \brief Provides efficient access to stars by position or name.
 *
 * Note that a StarIndex is immutable once constructed.  Stars must be added to
 * the StarLoader before it is used to make the StarIndex.
 */
class FEARLESS_PHYSICS_API StarIndex : boost::noncopyable {
  public:
    explicit StarIndex(StarLoader const&);
    ~StarIndex();

    void apply_to_stars(boost::function<void(Star const&)> const&) const;
    void dump(std::ostream&) const;
  private:
    class Impl;
    boost::scoped_ptr<const Impl> impl_;
};

}}

#endif // FEARLESS_PHYSICS__STARINDEX_HPP

