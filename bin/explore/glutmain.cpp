#include "glutmain.hpp"

#include <GL/glut.h>

#include <fearless/fatal.hpp>

namespace fearless { namespace explore {

// Various static implementation details
namespace {
  static bool exists = false;
  GlutCallbacks* callbacks = NULL;

  void display()
  {
    callbacks->display();
  }

  void idle()
  {
    callbacks->idle();
  }

  void reshape(int w, int h)
  {
    callbacks->reshape(w, h);
  }
}

GlutMain::GlutMain(int* argc, char** argv)
{
  /** \bug Not thread-safe */
  if (exists) {
    FEARLESS_FATAL("duplicate GlutMain");
  }
  exists = true;

  glutInit(argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_ALPHA | GLUT_RGBA);
  // Window creation must come *before* tex loading
  glutCreateWindow("explore");

  // Load textures here?
  glEnable(GL_TEXTURE_2D);
}

GlutMain::~GlutMain()
{
  callbacks = NULL;
  exists = false;
}

void GlutMain::go(GlutCallbacks& c)
{
  callbacks = &c;
  glutDisplayFunc(display);
  glutIdleFunc(idle);
  glutReshapeFunc(reshape);

  glutMainLoop();
}

}}

