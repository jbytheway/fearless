#ifndef FEARLESS_EXPLORE__RENDERER_HPP
#define FEARLESS_EXPLORE__RENDERER_HPP

#include <memory>
#include <queue>
#include <map>

#include <boost/noncopyable.hpp>

#include <fearless/units/quantity.hpp>
#include <fearless/units/angle.hpp>
#include <fearless/units/frequency.hpp>
#include <fearless/units/acceleration.hpp>
#include <fearless/physics/observer.hpp>
#include <fearless/physics/galaxy.hpp>
#include <fearless/physics/conventionalreality.hpp>

#include "glutcallbacks.hpp"
#include "texturesource.hpp"

namespace fearless { namespace explore {

class Renderer : public GlutCallbacks, private boost::noncopyable {
  private:
    typedef physics::ConventionalReality Reality;
  public:
    Renderer(physics::StarIndex const&, TextureSource const&);
    virtual void display();
    virtual void idle();
    virtual void reshape(int width, int height);
    virtual void special(int /*key*/, int /*x*/, int /*y*/);
    virtual void special_up(int /*key*/, int /*x*/, int /*y*/);
    virtual void keyboard(unsigned char /*key*/, int /*x*/, int /*y*/);
    virtual void keyboard_up(unsigned char /*key*/, int /*x*/, int /*y*/);
  private:
    void update_projection();
    void render_star(
        physics::PoincareTransform<Reality, double> const& galaxyToObserver,
        physics::Velocity<double> const& starVelocityInObserverFrame,
        physics::Star const&
      );

    enum class KeyType { ascii, special };

    friend inline bool operator<(Renderer::KeyType l, Renderer::KeyType r) {
      return int(l) < int(r);
    }

    physics::Galaxy<Reality> galaxy_;
    physics::Observer<Reality> observer_;
    std::map<std::pair<KeyType, int>, bool> key_states_;
    int width_;
    int height_;
    units::quantity<units::degree_angle, float> fov_;
    units::quantity<units::frequency, float> fov_change_rate_;
    units::quantity<units::degree_angle, float> pixel_size_;
    std::unique_ptr<cagoul::texture> star_texture_;
    std::queue<int> frame_times_;
    int last_time_;
    units::quantity<units::acceleration, double> acceleration_;
    double faintest_magnitude_;
    double magnitude_scale_;
    double alpha_offset_;
};

}}

#endif // FEARLESS_EXPLORE__RENDERER_HPP

