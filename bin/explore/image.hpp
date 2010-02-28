#ifndef FEARLESS_EXPLORE__IMAGE_HPP
#define FEARLESS_EXPLORE__IMAGE_HPP

#include <memory>

#include <boost/noncopyable.hpp>
#include <boost/scoped_array.hpp>
#include <boost/filesystem/path.hpp>

namespace fearless { namespace explore {

class Image : boost::noncopyable {
  public:
    static std::unique_ptr<Image>
    load_from_file(boost::filesystem::path const&);

    static std::unique_ptr<Image>
    load_bitmap(boost::filesystem::path const&);

    Image(int format, size_t width, size_t height);

    size_t width() const { return width_; }
    size_t height() const { return height_; }
    int format() const { return format_; }
    int bytes_per_pixel() const { return bytes_per_pixel_; }
    uint8_t const* pixels() const { return pixels_.get(); }
    uint8_t* pixel_row(size_t row);
  private:
    size_t width_;
    size_t height_;
    int format_;
    int bytes_per_pixel_;
    size_t pitch_;
    size_t size_;
    boost::scoped_array<uint8_t> pixels_;
};

}}

#endif // FEARLESS_EXPLORE__IMAGE_HPP

