#ifndef FEARLESS_EXPLORE__BITMAPSTRING_HPP
#define FEARLESS_EXPLORE__BITMAPSTRING_HPP

#include <string>

namespace fearless { namespace explore {

class BitmapString {
  public:
    enum class Font {
      Mono,
      TimesRoman,
      Helvetica
    };
    BitmapString(Font font, int height, std::string);
    void render_top_left(float x, float y, float lineskip = 1.2);
    void render_bottom_left(float x, float y, float lineskip = 1.2);
  private:
    void* font_;
    int height_;
    std::string string_;
};

}}

#endif // FEARLESS_EXPLORE__BITMAPSTRING_HPP

