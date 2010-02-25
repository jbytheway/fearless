#ifndef FEARLESS_EXPLORE__GLUTMAIN_HPP
#define FEARLESS_EXPLORE__GLUTMAIN_HPP

#include "glutcallbacks.hpp"

namespace fearless { namespace explore {

class GlutMain {
  public:
    GlutMain(int* argc, char** argv);
    ~GlutMain();
    void go(GlutCallbacks&);
};

}}

#endif // FEARLESS_EXPLORE__GLUTMAIN_HPP

