#include <fearless/physics/starindex.hpp>

#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

#include <fearless/physics/starloader.hpp>

namespace fearless { namespace physics {

class StarIndex::Impl {
  public:
    explicit Impl(StarLoader const& loader) {
      std::copy(
          loader.stars().begin(), loader.stars().end(),
          std::back_inserter(stars_)
        );
    }

    void apply_to_stars(boost::function<void(Star const&)> const&) const;
  private:
    std::vector<Star> stars_;
};

StarIndex::StarIndex(StarLoader const& loader) :
  impl_(new Impl(loader))
{}

StarIndex::~StarIndex() = default;

void StarIndex::apply_to_stars(
    boost::function<void(Star const&)> const& f
  ) const
{
  impl_->apply_to_stars(f);
}

void StarIndex::dump(std::ostream& o) const
{
  using boost::phoenix::arg_names::arg1;
  apply_to_stars(boost::phoenix::ref(o) << arg1 << '\n');
}

void StarIndex::Impl::apply_to_stars(
    boost::function<void(Star const&)> const& f
  ) const
{
  std::for_each(stars_.begin(), stars_.end(), f);
}

}}

