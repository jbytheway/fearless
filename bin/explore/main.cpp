#include <boost/filesystem/fstream.hpp>

#include <fearless/physics/starloader.hpp>
#include <fearless/physics/starindex.hpp>

#include "glutmain.hpp"
#include "renderer.hpp"

int main(int argc, char** argv)
{
  boost::filesystem::path exe(argv[0]);
  boost::filesystem::path exePath = exe.parent_path();
  boost::filesystem::path dataPath = exePath/".."/".."/".."/"data";

  fearless::physics::StarLoader starLoader;
  boost::filesystem::ifstream starsTxt(dataPath/"celestia_stars.txt");
  starLoader.load_celestia_txt(starsTxt);
  fearless::physics::StarIndex starIndex(starLoader);

  fearless::explore::GlutMain m(&argc, argv);
  /** \todo Worry a bit more about where to search */
  fearless::explore::TextureSource texSrc(dataPath);
  fearless::explore::Renderer r(texSrc);
  m.go(r);
}

