#include "renderer.hpp"

#include <algorithm>

#include <boost/bind.hpp>
#include <boost/format.hpp>

#include <GL/glut.h>

#include <fearless/debug.hpp>
#include <fearless/units/dimensionless.hpp>
#include <fearless/maths/clamp.hpp>
#include <fearless/physics/redshift.hpp>
#include <fearless/physics/acceleration.hpp>
#include <fearless/physics/worldline.hpp>
#include <fearless/physics/gamma.hpp>
#include <fearless/physics/colour_of_temperature.hpp>

#include "scopedorthographicprojection.hpp"
#include "scopedbindtexture.hpp"
#include "bitmapstring.hpp"

namespace fearless { namespace explore {

Renderer::Renderer(
    physics::StarIndex const& starIndex,
    TextureSource const& textureSource
  ) :
  galaxy_{starIndex},
  observer_{
    physics::RelativeInertialFrame<Reality>(galaxy_.root_frame(), "Observer")
  },
  width_{1},
  height_{1},
  fov_{45*units::degrees},
  fov_change_rate_{1/units::seconds},
  pixel_size_{1*units::degree},
  star_texture_{textureSource.load_star()},
  last_time_{},
  acceleration_{Reality::c() / (10.0*units::second)}
{
  int asciiKeys[] = {
    'z', 'x'
  };
  BOOST_FOREACH(int const key, asciiKeys) {
    key_states_[std::make_pair(KeyType::ascii, key)] = false;
  }
  int specialKeys[] = {
    GLUT_KEY_LEFT, GLUT_KEY_RIGHT, GLUT_KEY_UP, GLUT_KEY_DOWN
  };
  BOOST_FOREACH(int const key, specialKeys) {
    key_states_[std::make_pair(KeyType::special, key)] = false;
  }
}

void Renderer::display()
{
  // Update frame_times_ for FPS monitor
  int time = glutGet(GLUT_ELAPSED_TIME);
  frame_times_.push(time);
  while (frame_times_.front() < time - 1000) {
    frame_times_.pop();
  }
  units::quantity<units::time, double> timeSinceLastFrame =
    (time - last_time_)*0.001*units::seconds;
  last_time_ = time;
  // Truncate to one second to prevent craziness
  if (timeSinceLastFrame < 0.0*units::seconds) {
    FEARLESS_DEBUG("negative time since last frame");
    timeSinceLastFrame = units::zero;
  } else if (timeSinceLastFrame > 1.0*units::seconds) {
    FEARLESS_DEBUG("large time since last frame");
    timeSinceLastFrame = 1.0*units::seconds;
  }

  // Deal with FOV update
  decltype(fov_change_rate_) dfov_dt{};
  if (key_states_[std::make_pair(KeyType::ascii, 'z')]) {
    dfov_dt += fov_change_rate_;
  }
  if (key_states_[std::make_pair(KeyType::ascii, 'x')]) {
    dfov_dt -= fov_change_rate_;
  }
  if (dfov_dt != 0.0*units::hertz) {
    fov_ *= float(exp(dfov_dt*timeSinceLastFrame));
    fov_ = maths::clamp(fov_, 1.0f*units::degrees, 120.0f*units::degrees);
    update_projection();
  }

  // Deal with observer acceleration
  typedef physics::Acceleration<double> Acc;
  Acc acceleration{};
  if (key_states_[std::make_pair(KeyType::special, GLUT_KEY_UP)]) {
    acceleration += Acc(0, 0, -acceleration_);
  };
  if (key_states_[std::make_pair(KeyType::special, GLUT_KEY_DOWN)]) {
    acceleration += Acc(0, 0, acceleration_);
  };
  if (key_states_[std::make_pair(KeyType::special, GLUT_KEY_LEFT)]) {
    acceleration += Acc(-acceleration_, 0, 0);
  };
  if (key_states_[std::make_pair(KeyType::special, GLUT_KEY_RIGHT)]) {
    acceleration += Acc(acceleration_, 0, 0);
  };
  observer_.boost(acceleration * timeSinceLastFrame);
  observer_.advance(timeSinceLastFrame);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // Turn on blending which just adds up the colour
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE);

  {
    physics::PoincareTransform<Reality, double> galaxyToObserverTransform =
      observer_.make_transform_from(*galaxy_.root_frame());
    // Because we don't support proper motion of Stars we can pull out the
    // direction bit of the worldline transformation here, rarther than doing
    // iy every time round the loop
    physics::Velocity<double> starVelocityInObserverFrame =
      galaxyToObserverTransform.lorentz().inverse().velocity();
    ScopedBindTexture s(*star_texture_);
    glLoadIdentity();
    glEnable(GL_POINT_SPRITE);
    glPointSize(4);
    glBegin(GL_POINTS);
      galaxy_.star_index().apply_to_stars(
          boost::bind(
            &Renderer::render_star, this,
            galaxyToObserverTransform, starVelocityInObserverFrame, _1
          )
        );
    glEnd();
    glDisable(GL_POINT_SPRITE);
  }
  {
    auto const& observerFrame = observer_.frame();
    auto const& referenceFrame = *observerFrame.relative_to();
    auto const topTransform =
      observerFrame.make_transform_from(referenceFrame);
    // Position of observer in reference frame is the inverse image of the
    // origin in the transform
    physics::Event<Reality, double> const inReferenceFrame =
      topTransform.inverse().translation();
    physics::Velocity<double> const velocity =
      topTransform.lorentz().velocity();
    double const gamma = physics::gamma<Reality>(velocity);
    ScopedOrthographicProjection p(width_, height_);
    glLoadIdentity();
    glColor3f(1, 1, 1);
    BitmapString(
        BitmapString::Font::Helvetica, 12,
        (boost::format(
            "Fearless Explorer\n"
            "Reference frame: %s\n"
            "Position: %s\n"
            "Time: %s\n"
            "Velocity: %s\n"
            "Gamma: %f\n"
            "Traveller's time: %s\n"
            "FOV: %s\n"
            "%d fps") %
            referenceFrame.name() %
            inReferenceFrame.spatial() %
            inReferenceFrame.t_over_c<Reality>() %
            velocity %
            gamma %
            observer_.travellers_time() %
            fov_ %
            frame_times_.size()
        ).str()
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
  update_projection();
}

void Renderer::special(int key, int /*x*/, int /*y*/)
{
  auto const it = key_states_.find(std::make_pair(KeyType::special, key));
  if (it != key_states_.end()) it->second = true;
}

void Renderer::special_up(int key, int /*x*/, int /*y*/)
{
  auto const it = key_states_.find(std::make_pair(KeyType::special, key));
  if (it != key_states_.end()) it->second = false;
}

void Renderer::keyboard(unsigned char key, int /*x*/, int /*y*/)
{
  auto const it = key_states_.find(std::make_pair(KeyType::ascii, key));
  if (it != key_states_.end()) it->second = true;
}

void Renderer::keyboard_up(unsigned char key, int /*x*/, int /*y*/)
{
  auto const it = key_states_.find(std::make_pair(KeyType::ascii, key));
  if (it != key_states_.end()) it->second = false;
}

void Renderer::update_projection()
{
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
      0.1/*near clip*/,
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

void Renderer::render_star(
    physics::PoincareTransform<Reality, double> const& galaxyToObserver,
    physics::Velocity<double> const& starVelocityInObserverFrame,
    physics::Star const& star
  )
{
  physics::Worldline<Reality, double> starWorldline(
      galaxyToObserver.apply(
        physics::Event<Reality, double>(0.0*units::metres, star.position())
      ),
      starVelocityInObserverFrame
    );
  /** \todo Using floats instead of doubles below here caused bizarre issues:
   * stars started to vanish seemingly at random at high speeds.  This should
   * be investigated at some point. */
  physics::Displacement<double> pos{starWorldline.visible_at().spatial()};
  assert(isfinite(pos));
  units::quantity<units::length, double> const distance = pos.norm();
  physics::ThreeVector<units::quantity<units::dimensionless, double>> n_pos =
    pos/distance;
  physics::Redshift<Reality, float> redshift{
    starVelocityInObserverFrame, pos
  };
  /** \bug Colour should depend on redshift */
  auto const starColour =
    physics::colour_of_temperature(redshift.apply(star.temperature()));
  /** \bug Magnitude should depend on redshift */
  /*physics::ApparentMagnitude<double> appMag{
    star.absolute_magnitude(), distance
  };*/
  glColor4f(starColour.r(), starColour.g(), starColour.b(), 0.5);
  glVertex3d(n_pos.x(), n_pos.y(), n_pos.z());
}

}}

