#include "renderer.hpp"

#include <algorithm>

#include <boost/bind.hpp>
#include <boost/format.hpp>

#include <GL/glut.h>

#include <fearless/debug.hpp>
#include <fearless/units/dimensionless.hpp>

#include "scopedorthographicprojection.hpp"
#include "scopedbindtexture.hpp"
#include "bitmapstring.hpp"

namespace fearless { namespace explore {

Renderer::Renderer(
    physics::StarIndex const& starIndex,
    TextureSource const& textureSource
  ) :
  star_index_(starIndex),
  width_{1},
  height_{1},
  fov_{45*units::degrees},
  pixel_size_{1*units::degree},
  star_texture_{textureSource.load_star()}
{
}

void Renderer::display()
{
  // Update frame_times_ for FPS monitor
  int time = glutGet(GLUT_ELAPSED_TIME);
  frame_times_.push(time);
  while (frame_times_.front() < time - 1000) {
    frame_times_.pop();
  }

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // Turn on blending which just adds up the colour
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE);

  {
    ScopedBindTexture s(*star_texture_);
    glLoadIdentity();
    glEnable(GL_POINT_SPRITE);
    glPointSize(4);
    glBegin(GL_POINTS);
      glColor3f(0.2, 0, 0);
      star_index_.apply_to_stars(
          boost::bind(&Renderer::render_star, this, _1)
        );
    glEnd();
    glDisable(GL_POINT_SPRITE);
  }
  {
    ScopedOrthographicProjection p(width_, height_);
    glLoadIdentity();
    glColor3f(1, 1, 1);
    BitmapString(
        BitmapString::Font::Helvetica, 12,
        (boost::format("Fearless Explorer\n%d fps") %
          frame_times_.size()).str()
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
  units::quantity<units::degree_angle, float> y_fov =
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
      0.5/*near clip*/,
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

void Renderer::render_star(physics::Star const& star)
{
  physics::Displacement<float> pos(star.position());
  physics::ThreeVector<units::quantity<units::dimensionless, float>> n_pos =
    pos/pos.norm();
  glVertex3f(n_pos.x(), n_pos.y(), n_pos.z());
}

}}

