#include "renderer.hpp"

#include <algorithm>

#include <GL/glut.h>

#include <fearless/debug.hpp>

#include "scopedorthographicprojection.hpp"
#include "scopedbindtexture.hpp"
#include "bitmapstring.hpp"

namespace fearless { namespace explore {

Renderer::Renderer(TextureSource const& textureSource) :
  width_{1},
  height_{1},
  fov_{45*units::degrees},
  pixel_size_{1*units::degree},
  starTexture_{textureSource.load_star()}
{
}

void Renderer::display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // Turn on blending which just adds up the colour
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE);

  glLoadIdentity();
  glTranslatef(0, 0, -6);
  glColor3f(1, 1, 1);
  glBegin(GL_QUADS);
    glVertex3f(-1, -1, 0);
    glVertex3f( 1, -1, 0);
    glVertex3f( 1,  1, 0);
    glVertex3f(-1,  1, 0);
  glEnd();
  {
    ScopedBindTexture s(*starTexture_);
    glEnable(GL_POINT_SPRITE);
    glPointSize(20);
    glBegin(GL_POINTS);
      glColor3f(0.5, 0, 0);
      glVertex3f(-1.5, 0, 0);
      glVertex3f(-1.5, 0.1, 0);
    glEnd();
    glDisable(GL_POINT_SPRITE);
  }
  {
    ScopedOrthographicProjection p(width_, height_);
    glLoadIdentity();
    glColor3f(1, 1, 1);
    BitmapString(
        BitmapString::Font::Helvetica, 12,
        "Fearless Explorer\nTest"
      ).render_top_left(5, 5);
  }
  glutSwapBuffers();
}

void Renderer::idle()
{
  display();
}

void Renderer::reshape(int width, int height)
{
  // Prevent divide by zero
  width_ = std::max(width, 1);
  height_ = std::max(height, 1);

  float ratio = 1.0 * width_ / height_;
  // Make wider dimension have specified field of view
  units::quantity<units::plane_angle, float> y_fov =
    ( ratio > 1 ? fov_/ratio : fov_ );
  pixel_size_ = y_fov / float(height_);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // Set the viewport to be the entire window
  glViewport(0/*left*/, 0/*bottom*/, width_/*right*/, height_/*top*/);

  // Set the correct perspective.
  gluPerspective(
      y_fov / units::degree/*fov in y-z plane*/,
      ratio,
      1/*near clip*/,
      10/*far clip*/
    );
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(
      0.0, 0.0, 0.0, /*position*/
      0.0, 0.0,-1.0, /*look at*/
      0.0, 1.0, 0.0  /*up*/
    );
}

}}

