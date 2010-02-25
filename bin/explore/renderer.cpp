#include "renderer.hpp"

#include <algorithm>

#include <GL/glut.h>

namespace fearless { namespace explore {

Renderer::Renderer() :
  fov_{45}
{
}

void Renderer::display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  glTranslatef(0, 0, -6);
  glBegin(GL_QUADS);
    glVertex3f(-1, -1, 0);
    glVertex3f( 1, -1, 0);
    glVertex3f( 1,  1, 0);
    glVertex3f(-1,  1, 0);
  glEnd();
  glutSwapBuffers();
}

void Renderer::idle()
{
  display();
}

void Renderer::reshape(int width, int height)
{
  // Prevent divide by zero
  width = std::max(width, 1);
  height = std::max(height, 1);

  float ratio = 1.0 * width / height;
  // Make wider dimension have specified field of view
  float y_fov = ( ratio > 1 ? fov_/ratio : fov_ );

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // Set the viewport to be the entire window
  glViewport(0/*left*/, 0/*bottom*/, width/*right*/, height/*top*/);

  // Set the correct perspective.
  gluPerspective(y_fov/*fov in y-z plane*/,ratio,1/*near clip*/,10/*far clip*/);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(
      0.0, 0.0, 0.0, /*position*/
      0.0, 0.0,-1.0, /*look at*/
      0.0, 1.0, 0.0  /*up*/
    );
}

}}

