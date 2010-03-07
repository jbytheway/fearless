#include <boost/filesystem/fstream.hpp>

#include <fearless/physics/stardb.hpp>

#include "glutmain.hpp"
#include "renderer.hpp"

int main(int argc, char** argv)
{
  boost::filesystem::path exe(argv[0]);
  boost::filesystem::path exePath = exe.parent_path();
  boost::filesystem::path dataPath = exePath/".."/".."/".."/"data";

  fearless::physics::StarDb starDb;
  boost::filesystem::ifstream starsTxt(dataPath/"celestia_stars.txt");
  starDb.load_celestia_txt(starsTxt);

  fearless::explore::GlutMain m(&argc, argv);
  /** \todo Worry a bit more about where to search */
  fearless::explore::TextureSource texSrc(dataPath);
  fearless::explore::Renderer r(texSrc);
  m.go(r);
}

