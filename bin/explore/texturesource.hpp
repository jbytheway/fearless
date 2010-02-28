#ifndef FEARLESS_EXPLORE__TEXTURESOURCE_HPP
#define FEARLESS_EXPLORE__TEXTURESOURCE_HPP

#include <boost/filesystem/path.hpp>

#include "texture.hpp"

namespace fearless { namespace explore {

class TextureSource {
  public:
    TextureSource(boost::filesystem::path const& dataRoot);

    std::unique_ptr<Texture> load_star() const;
  private:
    boost::filesystem::path data_root_;
};

}}

#endif // FEARLESS_EXPLORE__TEXTURESOURCE_HPP

