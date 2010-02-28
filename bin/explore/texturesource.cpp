#include "texturesource.hpp"

namespace fearless { namespace explore {

TextureSource::TextureSource(boost::filesystem::path const& dataRoot) :
  data_root_(dataRoot)
{}

std::unique_ptr<Texture> TextureSource::load_star() const
{
  return Texture::load_from_file(data_root_/"distant_star.bmp");
}

}}

