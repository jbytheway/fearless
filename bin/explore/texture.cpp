#include "texture.hpp"

#include <GL/gl.h>

#include "image.hpp"
#include "scopedbindtexture.hpp"

namespace fearless { namespace explore {

namespace {

class ImageTexture : public Texture {
  public:
    ImageTexture(Image const&);
    ~ImageTexture();

    void bind() const;
  private:
    GLuint name_;
};

ImageTexture::ImageTexture(Image const& image)
{
  glGenTextures(1, &name_);
  ScopedBindTexture s(*this);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
  glTexImage2D(
      GL_TEXTURE_2D,
      0 /* level of detail (mip level) */,
      image.bytes_per_pixel(),
      image.width(),
      image.height(),
      0 /* border */,
      image.format(),
      GL_UNSIGNED_BYTE,
      image.pixels()
    );
}

ImageTexture::~ImageTexture()
{
  glDeleteTextures(1, &name_);
}

void ImageTexture::bind() const
{
  glBindTexture(GL_TEXTURE_2D, name_);
}

bool dimension_good_for_texture(size_t const d)
{
  // Limiting to 256 is probably unnecessary; video cards supporting other
  // things we use probably can support more
  return d == 64 || d == 128 || d == 256;
}

bool dimensions_good_for_texture(Image const& image)
{
  return dimension_good_for_texture(image.width()) &&
    dimension_good_for_texture(image.height());
}

}

std::unique_ptr<Texture>
Texture::load_from_file(boost::filesystem::path const& p)
{
  std::unique_ptr<Image> image = Image::load_from_file(p);
  if (!dimensions_good_for_texture(*image)) {
    throw std::runtime_error("bad image dimensions");
  }
  return std::unique_ptr<Texture>(new ImageTexture(*image));
}

Texture::~Texture() = default;

}}

