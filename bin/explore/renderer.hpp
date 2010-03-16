#ifndef FEARLESS_EXPLORE__RENDERER_HPP
#define FEARLESS_EXPLORE__RENDERER_HPP

#include <memory>
#include <queue>

#include <boost/noncopyable.hpp>

#include <fearless/units/quantity.hpp>
#include <fearless/units/angle.hpp>
#include <fearless/physics/observer.hpp>
#include <fearless/physics/galaxy.hpp>
#include <fearless/physics/conventionalreality.hpp>

#include "glutcallbacks.hpp"
#include "texture.hpp"
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
  private:
    void render_star(
        physics::PoincareTransform<Reality, double> const& galaxyToObserver,
        physics::Event<Reality, double> const& starDirectionInObserverFrame,
        physics::Star const&
      );

    physics::Galaxy<Reality> galaxy_;
    physics::Observer<Reality> observer_;
    int width_;
    int height_;
    units::quantity<units::degree_angle, float> fov_;
    units::quantity<units::degree_angle, float> pixel_size_;
    std::unique_ptr<Texture> star_texture_;
    std::queue<int> frame_times_;
};

}}

#endif // FEARLESS_EXPLORE__RENDERER_HPP

