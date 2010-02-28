#ifndef FEARLESS_EXPLORE__RENDERER_HPP
#define FEARLESS_EXPLORE__RENDERER_HPP

#include <memory>

#include <boost/noncopyable.hpp>

#include "glutcallbacks.hpp"
#include "texture.hpp"
#include "texturesource.hpp"

namespace fearless { namespace explore {

class Renderer : public GlutCallbacks, private boost::noncopyable {
  public:
    Renderer(TextureSource const&);
    virtual void display();
    virtual void idle();
    virtual void reshape(int width, int height);
  private:
    int width_;
    int height_;
    float fov_;
    std::unique_ptr<Texture> starTexture_;
};

}}

#endif // FEARLESS_EXPLORE__RENDERER_HPP

