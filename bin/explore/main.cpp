#include <boost/filesystem/fstream.hpp>

#include <fearless/physics/starloader.hpp>
#include <fearless/physics/starindex.hpp>

#include "glutmain.hpp"
#include "renderer.hpp"

int main(int argc, char** argv)
{
  boost::filesystem::path exe(argv[0]);
  boost::filesystem::path exePath = exe.parent_path();
  while (!(exePath.empty() || boost::filesystem::exists(exePath/"data"))) {
    exePath = exePath.parent_path();
  }
  if (exePath.empty()) {
    FEARLESS_FATAL(
        "couldn't locate data directory in any parent of exe directory"
      );
  }
  boost::filesystem::path dataPath = exePath/"data";

  fearless::physics::StarLoader starLoader;
  starLoader.load_celestia_txt(dataPath/"celestia_stars.txt");
  fearless::physics::StarIndex starIndex(starLoader);

  fearless::explore::GlutMain m(&argc, argv);
  /** \todo Worry a bit more about where to search */
  fearless::explore::TextureSource texSrc(dataPath);
  fearless::explore::Renderer r(starIndex, texSrc);
  m.go(r);
}

