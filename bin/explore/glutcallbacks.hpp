#ifndef FEARLESS_EXPLORE__GLUTCALLBACKS_HPP
#define FEARLESS_EXPLORE__GLUTCALLBACKS_HPP

namespace fearless { namespace explore {

class GlutCallbacks {
  public:
    virtual void display() = 0;
    virtual void idle() = 0;
    virtual void reshape(int width, int height) = 0;
    virtual void special(int /*key*/, int /*x*/, int /*y*/) {}
    virtual void special_up(int /*key*/, int /*x*/, int /*y*/) {}
    virtual void keyboard(unsigned char /*key*/, int /*x*/, int /*y*/) {}
    virtual void keyboard_up(unsigned char /*key*/, int /*x*/, int /*y*/) {}
  protected:
    GlutCallbacks() = default;
    GlutCallbacks(GlutCallbacks const&) = default;
    GlutCallbacks& operator=(GlutCallbacks const&) = default;
    virtual ~GlutCallbacks() = 0;
};

}}

#endif // FEARLESS_EXPLORE__GLUTCALLBACKS_HPP

