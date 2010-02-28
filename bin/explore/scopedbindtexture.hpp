#ifndef FEARLESS_EXPLORE__SCOPEDBINDTEXTURE_HPP
#define FEARLESS_EXPLORE__SCOPEDBINDTEXTURE_HPP

#include "texture.hpp"

namespace fearless { namespace explore {

class ScopedBindTexture {
  public:
    ScopedBindTexture(Texture const& texture) { texture.bind(); }
    ~ScopedBindTexture() { glBindTexture(GL_TEXTURE_2D, 0); }
    ScopedBindTexture(ScopedBindTexture const&) = delete;
};

}}

#endif // FEARLESS_EXPLORE__SCOPEDBINDTEXTURE_HPP

