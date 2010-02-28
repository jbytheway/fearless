#ifndef FEARLESS_EXPLORE__GLUTCALLBACKS_HPP
#define FEARLESS_EXPLORE__GLUTCALLBACKS_HPP

namespace fearless { namespace explore {

class GlutCallbacks {
  public:
    virtual void display() = 0;
    virtual void idle() = 0;
    virtual void reshape(int width, int height) = 0;
  protected:
    GlutCallbacks() = default;
    GlutCallbacks(GlutCallbacks const&) = default;
    GlutCallbacks& operator=(GlutCallbacks const&) = default;
    virtual ~GlutCallbacks() = 0;
};

}}

#endif // FEARLESS_EXPLORE__GLUTCALLBACKS_HPP

