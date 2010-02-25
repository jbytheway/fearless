#include "bitmapstring.hpp"

#include <GL/glut.h>

#include <boost/foreach.hpp>

#include <fearless/fatal.hpp>

namespace fearless { namespace explore {

BitmapString::BitmapString(Font font, int height, std::string s) :
  height_{height},
  string_(std::move(s))
{
  // Crazy selection of GLUT fonts
  switch (font) {
    case Font::Mono:
      switch (height) {
        case 13:
          font_ = GLUT_BITMAP_8_BY_13;
          break;
        case 15:
          font_ = GLUT_BITMAP_9_BY_15;
          break;
        default:
          FEARLESS_FATAL("invalid font size");
      }
      break;
    case Font::TimesRoman:
      switch (height) {
        case 10:
          font_ = GLUT_BITMAP_TIMES_ROMAN_10;
          break;
        case 24:
          font_ = GLUT_BITMAP_TIMES_ROMAN_24;
          break;
        default:
          FEARLESS_FATAL("invalid font size");
      }
      break;
    case Font::Helvetica:
      switch (height) {
        case 10:
          font_ = GLUT_BITMAP_HELVETICA_10;
          break;
        case 12:
          font_ = GLUT_BITMAP_HELVETICA_12;
          break;
        case 18:
          font_ = GLUT_BITMAP_HELVETICA_18;
          break;
        default:
          FEARLESS_FATAL("invalid font size");
      }
      break;
    default:
      FEARLESS_FATAL("invalid font");
  }
}

void BitmapString::render_top_left(float x, float y, float lineskip)
{
  render_bottom_left(x, y+height_, lineskip);
}

void BitmapString::render_bottom_left(float x, float y, float lineskip)
{
  glRasterPos2f(x, y);
  BOOST_FOREACH(char const c, string_) {
    if (c == '\n') {
      y += height_ * lineskip;
      glRasterPos2f(x, y);
      continue;
    }
    glutBitmapCharacter(font_, c);
  }
}

}}

