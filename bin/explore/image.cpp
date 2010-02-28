#include "image.hpp"

#include <unordered_map>

#include <boost/scoped_array.hpp>
#include <boost/filesystem/fstream.hpp>

#include <GL/gl.h>

#include <fearless/fatal.hpp>
#include <fearless/debug.hpp>
#include <fearless/maths/round_up_to_multiple.hpp>

namespace fearless { namespace explore {

// Image loading code adapted from Celestia
namespace {

static int format_bytes_per_pixel(int format)
{
  switch (format)
  {
    case GL_RGBA:
    case GL_BGRA_EXT:
      return 4;
    case GL_RGB:
    case GL_BGR_EXT:
      return 3;
    case GL_LUMINANCE_ALPHA:
    case GL_DSDT_NV:
      return 2;
    case GL_ALPHA:
    case GL_LUMINANCE:
      return 1;

      // Compressed formats
    case GL_COMPRESSED_RGBA_S3TC_DXT1_EXT:
      return 3;
    case GL_COMPRESSED_RGBA_S3TC_DXT3_EXT:
    case GL_COMPRESSED_RGBA_S3TC_DXT5_EXT:
      return 4;

      // Unknown format
    default:
      FEARLESS_FATAL("unrecognized pixel format");
  }
}

enum class ContentType {
  BMP,
  Unknown
};

class ContentTypeMap {
  public:
    ContentTypeMap() {
      map_[".bmp"] = ContentType::BMP;
    }

    ContentType operator()(boost::filesystem::path const& p) {
      return (*this)(p.extension());
    }

    ContentType operator()(std::string const& extension) {
      auto it = map_.find(extension);
      if (it == map_.end()) {
        return ContentType::Unknown;
      } else {
        return it->second;
      }
    }
  private:
    std::unordered_map<std::string, ContentType> map_;
} contentTypeMap;

// BMP file definitions--can't use windows.h because we might not be
// built on Windows!
typedef struct
{
  uint8_t b;
  uint8_t m;
  uint32_t size;
  uint32_t reserved;
  uint32_t offset;
} BMPFileHeader;

typedef struct
{
  uint32_t size;
  int32_t width;
  int32_t height;
  uint16_t planes;
  uint16_t bpp;
  uint32_t compression;
  uint32_t imageSize;
  int32_t widthPPM;
  int32_t heightPPM;
  uint32_t colorsUsed;
  uint32_t colorsImportant;
} BMPImageHeader;

static int32_t readInt32(std::istream& in)
{
  unsigned char b[4];
  in.read(reinterpret_cast<char*>(b), 4);
  return ((int) b[3] << 24) + ((int) b[2] << 16)
    + ((int) b[1] << 8) + (int) b[0];
}

static int16_t readInt16(std::istream& in)
{
  unsigned char b[2];
  in.read(reinterpret_cast<char*>(b), 2);
  return ((short) b[1] << 8) + (short) b[0];
}

std::unique_ptr<Image> LoadBMPImage(std::istream& in)
{
  BMPFileHeader fileHeader;
  BMPImageHeader imageHeader;

  fileHeader.b = in.get();
  fileHeader.m = in.get();
  fileHeader.size = readInt32(in);
  fileHeader.reserved = readInt32(in);
  fileHeader.offset = readInt32(in);

  if (fileHeader.b != 'B' || fileHeader.m != 'M')
    FEARLESS_FATAL("not a bitmap");

  imageHeader.size = readInt32(in);
  imageHeader.width = readInt32(in);
  imageHeader.height = readInt32(in);
  imageHeader.planes = readInt16(in);
  imageHeader.bpp = readInt16(in);
  imageHeader.compression = readInt32(in);
  imageHeader.imageSize = readInt32(in);
  imageHeader.widthPPM = readInt32(in);
  imageHeader.heightPPM = readInt32(in);
  imageHeader.colorsUsed = readInt32(in);
  imageHeader.colorsImportant = readInt32(in);

  if (imageHeader.width <= 0 || imageHeader.height <= 0)
    FEARLESS_FATAL("bad size");

  // We currently don't support compressed BMPs
  if (imageHeader.compression != 0)
    FEARLESS_FATAL("bitmap compressed - not supported");
  // We don't handle 1-, 2-, or 4-bpp images
  if (imageHeader.bpp != 8 && imageHeader.bpp != 24 && imageHeader.bpp != 32)
    FEARLESS_FATAL("bitmap uses unsupported bits per pixel");

  boost::scoped_array<uint8_t> palette;
  if (imageHeader.bpp == 8) {
    palette.reset(new uint8_t[imageHeader.colorsUsed * 4]);
    in.read(reinterpret_cast<char*>(palette.get()), imageHeader.colorsUsed * 4);
  }

  // check for truncated file
  if (!in) {
    FEARLESS_FATAL("file truncated");
  }

  in.seekg(fileHeader.offset, std::ios::beg);

  uint32_t bytesPerRow = (imageHeader.width * imageHeader.bpp / 8 + 1) & ~1;
  uint32_t imageBytes = bytesPerRow * imageHeader.height;

  // slurp the image data
  boost::scoped_array<uint8_t> pixels(new uint8_t[imageBytes]);
  in.read(reinterpret_cast<char*>(pixels.get()), imageBytes);

  // check for truncated file
  if (!in) {
    FEARLESS_FATAL("file truncated");
  }

  std::unique_ptr<Image> image(
      new Image(GL_RGB, imageHeader.width, imageHeader.height)
    );

  // Copy the image and perform any necessary conversions
  for (int y = 0; y < imageHeader.height; y++) {
    uint8_t* src = &pixels[y * bytesPerRow];
    uint8_t* dst = image->pixel_row(y);

    switch (imageHeader.bpp)
    {
      case 8:
        {
          for (int x = 0; x < imageHeader.width; x++) {
            uint8_t* color = palette.get() + (*src << 2);
            dst[0] = color[2];
            dst[1] = color[1];
            dst[2] = color[0];
            src++;
            dst += 3;
          }
        }
        break;

      case 24:
        {
          for (int x = 0; x < imageHeader.width; x++) {
            dst[0] = src[2];
            dst[1] = src[1];
            dst[2] = src[0];
            src += 3;
            dst += 3;
          }
        }
        break;

      case 32:
        {
          for (int x = 0; x < imageHeader.width; x++) {
            dst[0] = src[2];
            dst[1] = src[1];
            dst[2] = src[0];
            src += 4;
            dst += 3;
          }
        }
        break;
    }
  }

  return image;
}

}

std::unique_ptr<Image>
Image::load_from_file(boost::filesystem::path const& p)
{
  ContentType type = contentTypeMap(p);

  switch (type) {
    case ContentType::BMP:
      return load_bitmap(p);
    default:
      FEARLESS_FATAL("unknown image type");
  }
}

std::unique_ptr<Image>
Image::load_bitmap(boost::filesystem::path const& p)
{
  boost::filesystem::ifstream bmpFile(p, std::ios::in | std::ios::binary);

  if (bmpFile.good()) {
    return LoadBMPImage(bmpFile);
  } else {
    FEARLESS_FATAL("file not found or wouldn't open: " << p);
  }
}

Image::Image(int format, size_t width, size_t height) :
  width_(width),
  height_(height),
  format_(format),
  bytes_per_pixel_(format_bytes_per_pixel(format)),
  pitch_(maths::round_up_to_multiple(width * bytes_per_pixel_, 4)),
  size_(pitch_ * height),
  pixels_(new uint8_t[size_])
{
  /*FEARLESS_DEBUG(
      "\nwidth_ = " << width_ <<
      "\nheight_ = " << height_ <<
      "\nbytes_per_pixel_ = " << bytes_per_pixel_ <<
      "\npitch_ = " << pitch_ <<
      "\nsize_ = " << size_
    );*/
}

uint8_t* Image::pixel_row(size_t row)
{
  assert(row < height_);
  assert(row*pitch_ < size_);
  return pixels_.get() + row * pitch_;
}

}}

