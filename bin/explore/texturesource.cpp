#include "texturesource.hpp"

// workaround Boost.GIL bug https://svn.boost.org/trac/boost/ticket/3908
// (should be fixed in 1.44 or 1.45)
#ifndef png_infopp_NULL
#define png_infopp_NULL NULL
#endif
#ifndef int_p_NULL
#define int_p_NULL NULL
#endif
#include <boost/gil/extension/io/png_io.hpp>

#include <cagoul/scoped/bindtexture.hpp>
#include <cagoul/teximage2d.hpp>

#include <fearless/fatal.hpp>

namespace fearless { namespace explore {

TextureSource::TextureSource(boost::filesystem::path const& dataRoot) :
  data_root_(dataRoot)
{}

std::unique_ptr<cagoul::texture> TextureSource::load_from_file(
  boost::filesystem::path const& file
) const
{
  auto ext = file.extension();
  boost::gil::gray8_image_t image;
  if (ext == ".png") {
    boost::gil::png_read_image(file.file_string(), image);
  } else {
    FEARLESS_FATAL("unsupported file type");
  }
  std::unique_ptr<cagoul::texture> result(
    new cagoul::texture(cagoul::enums::BindTextureTarget::TEXTURE_2D)
  );
  cagoul::scoped::BindTexture s(*result);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  cagoul::TexImage2D(
    cagoul::enums::TexImage2DTarget::TEXTURE_2D,
    0,
    cagoul::enums::TexImage2DInternalFormat::RGB,
    const_view(image)
  );
  return result;
}


std::unique_ptr<cagoul::texture> TextureSource::load_star() const
{
  return load_from_file(data_root_/"distant_star.png");
}

}}

