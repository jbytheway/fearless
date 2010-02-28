#ifndef FEARLESS_EXPLORE__TEXTURE_HPP
#define FEARLESS_EXPLORE__TEXTURE_HPP

#include <boost/filesystem/path.hpp>

namespace fearless { namespace explore {

class Texture : boost::noncopyable {
  public:
    static std::unique_ptr<Texture>
    load_from_file(boost::filesystem::path const&);

    virtual ~Texture() = 0;

    virtual void bind() const = 0;
  protected:
    Texture() = default;
};

}}

#endif // FEARLESS_EXPLORE__TEXTURE_HPP

