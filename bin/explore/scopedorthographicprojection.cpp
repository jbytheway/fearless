#include "scopedorthographicprojection.hpp"

#include <GL/glut.h>

namespace fearless { namespace explore {

ScopedOrthographicProjection::ScopedOrthographicProjection(
    double width, double height
  )
{
  glMatrixMode(GL_PROJECTION);
  // save previous matrix which contains the
  // settings for the perspective projection
  glPushMatrix();
  // reset matrix
  glLoadIdentity();
  // set a 2D orthographic projection
  gluOrtho2D(0, width, 0, height);
  // invert the y axis, down is positive
  glScalef(1, -1, 1);
  // mover the origin from the bottom left corner
  // to the upper left corner
  glTranslatef(0, -height, 0);
  glMatrixMode(GL_MODELVIEW);
}

ScopedOrthographicProjection::~ScopedOrthographicProjection()
{
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
}

}}

