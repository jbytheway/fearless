#ifndef FEARLESS_EXPLORE__RENDERER_HPP
#define FEARLESS_EXPLORE__RENDERER_HPP

#include "glutcallbacks.hpp"

namespace fearless { namespace explore {

class Renderer : public GlutCallbacks {
  public:
    Renderer();
    Renderer(Renderer const&) = delete;
    virtual void display();
    virtual void idle();
    virtual void reshape(int width, int height);
  private:
    int width_;
    int height_;
    float fov_;
};

}}

#endif // FEARLESS_EXPLORE__RENDERER_HPP

