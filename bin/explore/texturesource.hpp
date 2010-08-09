#ifndef FEARLESS_EXPLORE__TEXTURESOURCE_HPP
#define FEARLESS_EXPLORE__TEXTURESOURCE_HPP

#include <boost/filesystem/path.hpp>

#include <cagoul/texture.hpp>

namespace fearless { namespace explore {

class TextureSource {
  public:
    TextureSource(boost::filesystem::path const& dataRoot);

    std::unique_ptr<cagoul::texture>
    load_from_file(boost::filesystem::path const&) const;

    std::unique_ptr<cagoul::texture> load_star() const;
  private:
    boost::filesystem::path data_root_;
};

}}

#endif // FEARLESS_EXPLORE__TEXTURESOURCE_HPP

