#ifndef FEARLESS_EXPLORE__SCOPEDORTHOGRAPHICPROJECTION_HPP
#define FEARLESS_EXPLORE__SCOPEDORTHOGRAPHICPROJECTION_HPP

namespace fearless { namespace explore {

class ScopedOrthographicProjection {
  public:
    ScopedOrthographicProjection(double width, double height);
    ~ScopedOrthographicProjection();
    ScopedOrthographicProjection(ScopedOrthographicProjection const&) = delete;
};

}}

#endif // FEARLESS_EXPLORE__SCOPEDORTHOGRAPHICPROJECTION_HPP

