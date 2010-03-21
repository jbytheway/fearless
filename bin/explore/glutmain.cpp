#include "glutmain.hpp"

#include <GL/freeglut.h>

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

  void special(int key, int x, int y)
  {
    callbacks->special(key, x, y);
  }

  void specialUp(int key, int x, int y)
  {
    callbacks->special_up(key, x, y);
  }

  void keyboard(unsigned char key, int x, int y)
  {
    callbacks->keyboard(key, x, y);
  }

  void keyboardUp(unsigned char key, int x, int y)
  {
    callbacks->keyboard_up(key, x, y);
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

  glEnable(GL_TEXTURE_2D);
  // Something like this might hypothetically allow variable size points within
  // one glBegin/End, but probably only with GLSL fun.
  //glEnable(GL_VERTEX_PROGRAM_POINT_SIZE_ARB);

  // I can't find out what this means, but it's important.  Described by one
  // source as "Specify point sprite texture coordinate replacement mode for
  // each texture unit" (What?!)
  glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);
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
  glutSpecialFunc(special);
  glutSpecialUpFunc(specialUp);
  glutKeyboardFunc(keyboard);
  glutKeyboardUpFunc(keyboardUp);

  // Almost certain to want to ignore key repeats
  glutIgnoreKeyRepeat(1);
  // This option allows glutMainLoop to return, thus allowing all our
  // destructors to run and not leak memory everywhere
  glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);

  glutMainLoop();
}

}}

