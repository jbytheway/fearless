#ifndef FEARLESS_PHYSICS__COLOUR_HPP
#define FEARLESS_PHYSICS__COLOUR_HPP

namespace fearless { namespace physics {

template <typename T>
class Colour {
  public:
    Colour(T const r, T const g, T const b) :
      r_{r}, g_{g}, b_{b}
    {}

    T r() const { return r_; }
    T g() const { return g_; }
    T b() const { return b_; }
  private:
    T r_;
    T g_;
    T b_;
};

}}

#endif // FEARLESS_PHYSICS__COLOUR_HPP

