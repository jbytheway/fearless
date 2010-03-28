#include <boost/filesystem/fstream.hpp>
#include <boost/algorithm/string/join.hpp>

#include <optimal/optionsparser.h>

#include <fearless/physics/starloader.hpp>
#include <fearless/physics/starindex.hpp>

#include "glutmain.hpp"
#include "renderer.hpp"

namespace {

  struct Options {
    Options() :
      help{}
    {}

    bool help;
    boost::filesystem::path data;
  };

  void usage()
  {
    std::cout <<
"Explorer is a free relativistic space simulator\n"
"\n"
"Command line options:\n"
"\n"
" -d, --data PATH  Use PATH as data directory.  Default is to search for a\n"
"                  directory named 'data' in the executable's directory or\n"
"                  any parent thereof.\n"
" -h, --help       Display this message.\n"
"\n"
" Explorer also accepts many standard X options, such as -display and\n"
" -geometry.  See the glut documentation for details, for example at\n"
" http://www.opengl.org/documentation/specs/glut/spec3/node10.html\n"
"\n"
"Controls:\n"
"\n"
" Arrow keys  Accelerate in various directions at c/10s.\n"
" z,x         Increase or decrease FOV.\n"
<< std::endl;
  }

  Options get_options(int const argc, char* const* const argv)
  {
    optimal::OptionsParser parser;
    Options results;
    parser.addOption("data", 'd', &results.data);
    parser.addOption("help", 'h', &results.help);

    if (parser.parse(argc, argv)) {
      std::cerr <<
        "Error(s) parsing options:\n  " <<
        boost::algorithm::join(parser.getErrors(), "\n  ") << "\n\n" <<
        "Try --help for usage instructions.\n";
      exit(EXIT_FAILURE);
    }

    return results;
  }

}

int main(int argc, char** argv)
{
  fearless::explore::GlutMain m(&argc, argv);
  Options options = get_options(argc, argv);

  if (options.help) {
    usage();
    return EXIT_SUCCESS;
  }

  boost::filesystem::path dataPath = options.data;

  if (dataPath.empty()) {
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
    dataPath = exePath/"data";
  }

  fearless::physics::StarLoader starLoader;
  starLoader.load_celestia_txt(dataPath/"celestia_stars.txt");
  fearless::physics::StarIndex starIndex(starLoader);

  /** \todo Worry a bit more about where to search */
  fearless::explore::TextureSource texSrc(dataPath);
  fearless::explore::Renderer r(starIndex, texSrc);
  m.go(r);
}

