#include "glutmain.hpp"
#include "renderer.hpp"

int main(int argc, char** argv)
{
  boost::filesystem::path exe(argv[0]);
  boost::filesystem::path exePath = exe.parent_path();

  fearless::explore::GlutMain m(&argc, argv);
  /** \todo Worry a bit more about where to search */
  fearless::explore::TextureSource texSrc(exePath/".."/".."/".."/"data");
  fearless::explore::Renderer r(texSrc);
  m.go(r);
}

