#include <fearless/physics/star.hpp>

#include <array>

#include <fearless/fatal.hpp>

// Logic and tables herein adapted from equivalents in Celestia,
// celengine/star.cpp, which is
// Copyright (C) 2001, Chris Laurel <claurel@shatters.net>

namespace fearless { namespace physics {

namespace {

  // Star temperature data from Lang's _Astrophysical Data: Planets and Stars_
  // Temperatures from missing (and typically not used) types in those
  // tables were just interpolated.
  float tempO[3][10] =
  {
    { 52500, 52500, 52500, 52500, 48000, 44500, 41000, 38000, 35800, 33000 },
    { 50000, 50000, 50000, 50000, 45500, 42500, 39500, 37000, 34700, 32000 },
    { 47300, 47300, 47300, 47300, 44100, 42500, 39500, 37000, 34700, 32000 },
  };

  float tempB[3][10] =
  {
    { 30000, 25400, 22000, 18700, 17000, 15400, 14000, 13000, 11900, 10500 },
    { 29000, 24000, 20300, 17100, 16000, 15000, 14100, 13200, 12400, 11000 },
    { 26000, 20800, 18500, 16200, 15100, 13600, 13000, 12200, 11200, 10300 },
  };

  float tempA[3][10] =
  {
    {  9520, 9230, 8970, 8720, 8460, 8200, 8020, 7850, 7580, 7390 },
    { 10100, 9480, 9000, 8600, 8300, 8100, 7850, 7650, 7450, 7250 },
    {  9730, 9230, 9080, 8770, 8610, 8510, 8310, 8150, 7950, 7800 },
  };

  float tempF[3][10] =
  {
    { 7200, 7050, 6890, 6740, 6590, 6440, 6360, 6280, 6200, 6110 },
    { 7150, 7000, 6870, 6720, 6570, 6470, 6350, 6250, 6150, 6080 },
    { 7700, 7500, 7350, 7150, 7000, 6900, 6500, 6300, 6100, 5800 },
  };

  float tempG[3][10] =
  {
    { 6030, 5940, 5860, 5830, 5800, 5770, 5700, 5630, 5570, 5410 },
    { 5850, 5650, 5450, 5350, 5250, 5150, 5050, 5070, 4900, 4820 },
    { 5550, 5350, 5200, 5050, 4950, 4850, 4750, 4660, 4600, 4500 },
  };

  float tempK[3][10] =
  {
    { 5250, 5080, 4900, 4730, 4590, 4350, 4200, 4060, 3990, 3920 },
    { 4750, 4600, 4420, 4200, 4000, 3950, 3900, 3850, 3830, 3810 },
    { 4420, 4330, 4250, 4080, 3950, 3850, 3760, 3700, 3680, 3660 },
  };

  float tempM[3][10] =
  {
    { 3850, 3720, 3580, 3470, 3370, 3240, 3050, 2940, 2640, 2000 },
    { 3800, 3720, 3620, 3530, 3430, 3330, 3240, 3240, 3240, 3240 },
    { 3650, 3550, 3450, 3200, 2980, 2800, 2600, 2600, 2600, 2600 },
  };

  // Wolf-Rayet temperatures.  From Lang's Astrophysical Data: Planets and
  // Stars.
  float tempWN[10] =
  {
    50000, 50000, 50000, 50000, 47000, 43000, 39000, 32000, 29000, 29000
  };

  float tempWC[10] =
  {
    60000, 60000, 60000, 60000, 60000, 60000, 60000, 54000, 46000, 38000
  };

  // Brown dwarf temperatures
  float tempL[10] =
  {
    1960, 1930, 1900, 1850, 1800, 1740, 1680, 1620, 1560, 1500
  };

  float tempT[10] =
  {
    1425, 1350, 1275, 1200, 1140, 1080, 1020, 900, 800, 750
  };

  // White dwarf temperatures
  float tempWD[10] =
  {
    100000.0f, 50400.0f, 25200.0f, 16800.0f, 12600.0f,
    10080.0f, 8400.0f, 7200.0f, 6300.0f, 5600.0f,
  };

}

class Star::Impl {
  public:
    static boost::shared_ptr<Impl> get(SpectralType const& spectralType) {
      // Use subclass 10 for unknown subclasses
      size_t const subclassIndex =
        spectralType.subclass ? *spectralType.subclass : 10;
      size_t specClass = size_t(spectralType.spectral_class);
      size_t lumClass = size_t(spectralType.luminosity_class);
      size_t const index =
        subclassIndex + (specClass + lumClass*size_t(SpectralClass::Max))*11;
      assert(index < num_types_);

      if (!flyweights_[index]) {
        flyweights_[index] = create(spectralType);
      }

      return flyweights_[index];
    }

    units::quantity<units::temperature, float> temperature() const {
      return temperature_;
    }
  private:
    static boost::shared_ptr<Impl> create(SpectralType const& spectralType) {
      size_t subclass;
      if (spectralType.subclass) {
        subclass = *spectralType.subclass;
      } else {
        // Since early O and Wolf-Rayet stars are exceedingly rare,
        // use temperature of the more common late types when the subclass
        // is unspecified in the spectral type.  For other stars, default
        // to subclass 5.
        switch (spectralType.spectral_class)
        {
          case SpectralClass::O:
          case SpectralClass::WN:
          case SpectralClass::WC:
            subclass = 9;
            break;
          default:
            subclass = 5;
            break;
        }
      }

      size_t lumIndex;
      switch (spectralType.luminosity_class) {
        case LuminosityClass::Ia0:
        case LuminosityClass::Ia:
        case LuminosityClass::Ib:
        case LuminosityClass::II:
          lumIndex = 2;
          break;
        case LuminosityClass::III:
        case LuminosityClass::IV:
          lumIndex = 1;
          break;
        case LuminosityClass::V:
        case LuminosityClass::VI:
        case LuminosityClass::Unknown:
          lumIndex = 0;
          break;
        default:
          FEARLESS_FATAL("unknown luminosity class");
      }

      float temp;
      switch (spectralType.spectral_class) {
        case SpectralClass::O:
          temp = tempO[lumIndex][subclass];
          break;
        case SpectralClass::B:
          temp = tempB[lumIndex][subclass];
          break;
        case SpectralClass::Unknown:
        case SpectralClass::A:
          temp = tempA[lumIndex][subclass];
          break;
        case SpectralClass::F:
          temp = tempF[lumIndex][subclass];
          break;
        case SpectralClass::G:
          temp = tempG[lumIndex][subclass];
          break;
        case SpectralClass::K:
          temp = tempK[lumIndex][subclass];
          break;
        case SpectralClass::M:
          temp = tempM[lumIndex][subclass];
          break;
        case SpectralClass::R:
          temp = tempK[lumIndex][subclass];
          break;
        case SpectralClass::S:
          temp = tempM[lumIndex][subclass];
          break;
        case SpectralClass::N:
          temp = tempM[lumIndex][subclass];
          break;
        case SpectralClass::C:
          temp = tempM[lumIndex][subclass];
          break;
        case SpectralClass::WN:
          temp = tempWN[subclass];
          break;
        case SpectralClass::WC:
          temp = tempWC[subclass];
          break;
        case SpectralClass::L:
          temp = tempL[subclass];
          break;
        case SpectralClass::T:
          temp = tempT[subclass];
          break;
        case SpectralClass::D:
        case SpectralClass::DA:
        case SpectralClass::DB:
        case SpectralClass::DC:
        case SpectralClass::DZ:
          temp = tempWD[subclass];
          break;
        default:
          FEARLESS_FATAL(
            "unknown spectral class " << spectralType.spectral_class
          );
      }

      return boost::shared_ptr<Impl>(new Impl(temp*units::kelvin));
    }

    Impl(units::quantity<units::temperature, float> temperature) :
      temperature_{temperature}
    {}

    static const size_t num_types_ =
      size_t(SpectralClass::Max) * 11 * size_t(LuminosityClass::Max);
    static std::array<boost::shared_ptr<Impl>, num_types_> flyweights_;
    units::quantity<units::temperature, float> temperature_;
};

std::array<boost::shared_ptr<Star::Impl>, Star::Impl::num_types_>
Star::Impl::flyweights_;

Star::Star(
    CatalogueNumber const num,
    Displacement<double> const& position,
    SpectralType const& spectralType,
    AbsoluteMagnitude<double> const& mag
  ) :
  catalogue_number_(num),
  position_(position),
  absolute_magnitude_(mag),
  impl_(Impl::get(spectralType))
{}

units::quantity<units::temperature, float> Star::temperature() const
{
  return impl_->temperature();
}

std::ostream& operator<<(std::ostream& o, Star const& s)
{
  o << s.catalogue_number() << ' ' << s.position();
  return o;
}

}}

