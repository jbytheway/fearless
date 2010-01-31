#ifndef FEARLESS_MATHS__COMPLEX_HPP
#define FEARLESS_MATHS__COMPLEX_HPP

#include <complex>

#include <boost/units/io.hpp>
#include <boost/units/pow.hpp>
#include <boost/units/quantity.hpp>

namespace fearless { namespace maths {

/** \brief Implementation of std::complex, but with Boost.Units support.
 *
 * Adapted from Boost.Units example, which is
 *
 * Copyright (C) 2003-2008 Matthias Christian Schabel
 * Copyright (C) 2008 Steven Watanabe
 */
template<class T>
class Complex
{
  public:
    typedef Complex<T>  this_type;

    Complex(const T& r = 0,const T& i = 0) : r_(r),i_(i) { }
    Complex(const std::complex<T>& z) : r_(z.real()),i_(z.imag()) { }

    this_type& operator=(const this_type& source)
    {
      if (this == &source) return *this;

      r_ = source.r_;
      i_ = source.i_;

      return *this;
    }

    T& real()                   { return r_; }
    T& imag()                   { return i_; }

    const T& real() const       { return r_; }
    const T& imag() const       { return i_; }

    typename boost::units::multiply_typeof_helper<T,T>::type
    norm_squared() const { return r_*r_+i_*i_; }

    Complex conj() const { return Complex(r_, -i_); }

    this_type& operator+=(const T& val)
    {
      r_ += val;
      return *this;
    }

    this_type& operator-=(const T& val)
    {
      r_ -= val;
      return *this;
    }

    this_type& operator*=(const T& val)
    {
      r_ *= val;
      i_ *= val;
      return *this;
    }

    this_type& operator/=(const T& val)
    {
      r_ /= val;
      i_ /= val;
      return *this;
    }

    this_type& operator+=(const this_type& source)
    {
      r_ += source.r_;
      i_ += source.i_;
      return *this;
    }

    this_type& operator-=(const this_type& source)
    {
      r_ -= source.r_;
      i_ -= source.i_;
      return *this;
    }

    this_type& operator*=(const this_type& source)
    {
      *this = *this * source;
      return *this;
    }

    this_type& operator/=(const this_type& source)
    {
      *this = *this / source;
      return *this;
    }

  private:
    T   r_,i_;
};

template<class X>
Complex<typename boost::units::unary_plus_typeof_helper<X>::type>
operator+(const Complex<X>& x)
{
  typedef typename boost::units::unary_plus_typeof_helper<X>::type  type;

  return Complex<type>(x.real(),x.imag());
}

template<class X>
Complex<typename boost::units::unary_minus_typeof_helper<X>::type>
operator-(const Complex<X>& x)
{
  typedef typename boost::units::unary_minus_typeof_helper<X>::type type;

  return Complex<type>(-x.real(),-x.imag());
}

template<class X,class Y>
Complex<typename boost::units::add_typeof_helper<X,Y>::type>
operator+(const Complex<X>& x,const Complex<Y>& y)
{
  typedef typename boost::units::add_typeof_helper<X,Y>::type type;

  return Complex<type>(x.real()+y.real(),x.imag()+y.imag());
}

template<class X,class Y>
Complex<typename boost::units::subtract_typeof_helper<X,Y>::type>
operator-(const Complex<X>& x,const Complex<Y>& y)
{
  typedef typename boost::units::subtract_typeof_helper<X,Y>::type    type;

  return Complex<type>(x.real()-y.real(),x.imag()-y.imag());
}

template<class X,class Y>
Complex<typename boost::units::multiply_typeof_helper<X,Y>::type>
operator*(const Complex<X>& x,const Y& y)
{
  typedef typename boost::units::multiply_typeof_helper<X,Y>::type    type;

  return Complex<type>(x.real()*y,x.imag()*y);
}

template<class X,class Y>
Complex<typename boost::units::multiply_typeof_helper<X,Y>::type>
operator*(const X& x,const Complex<Y>& y)
{
  typedef typename boost::units::multiply_typeof_helper<X,Y>::type    type;

  return Complex<type>(x*y.real(), x*y.imag());
}

template<class X,class Y>
Complex<typename boost::units::multiply_typeof_helper<X,Y>::type>
operator*(const Complex<X>& x,const Complex<Y>& y)
{
  typedef typename boost::units::multiply_typeof_helper<X,Y>::type    type;

  return Complex<type>(x.real()*y.real() - x.imag()*y.imag(),
      x.real()*y.imag() + x.imag()*y.real());

  //  fully correct implementation has more complex return type
  //
  //    typedef typename boost::units::multiply_typeof_helper<X,Y>::type xy_type;
  //    
  //    typedef typename boost::units::add_typeof_helper<
  //      xy_type,xy_type>::type         xy_plus_xy_type;
  //    typedef typename
  //        boost::units::subtract_typeof_helper<xy_type,xy_type>::type
  //        xy_minus_xy_type;
  //    
  //    BOOST_STATIC_ASSERT((boost::is_same<xy_plus_xy_type,
  //                                       xy_minus_xy_type>::value == true));
  //    
  //    return Complex<xy_plus_xy_type>(x.real()*y.real()-x.imag()*y.imag(),
  //                                    x.real()*y.imag()+x.imag()*y.real());
}

template<class X,class Y>
Complex<typename boost::units::divide_typeof_helper<X,Y>::type>
operator/(const Complex<X>& x,const Y& y)
{
  typedef typename boost::units::divide_typeof_helper<X,Y>::type    type;

  return Complex<type>(x.real()/y,x.imag()/y);
}

template<class X,class Y>
Complex<typename boost::units::divide_typeof_helper<X,Y>::type>
operator/(const X& x,const Complex<Y>& y)
{
  typedef typename boost::units::divide_typeof_helper<X,Y>::type    type;

  auto norm_squared = y.norm_squared();

  return Complex<type>(x*y.real()/norm_squared, -x*y.imag()/norm_squared);
}

template<class X,class Y>
Complex<typename boost::units::divide_typeof_helper<X,Y>::type>
operator/(const Complex<X>& x,const Complex<Y>& y)
{
  // naive implementation of complex division
  typedef typename boost::units::divide_typeof_helper<X,Y>::type type;

  return Complex<type>((x.real()*y.real()+x.imag()*y.imag())/
      (y.real()*y.real()+y.imag()*y.imag()),
      (x.imag()*y.real()-x.real()*y.imag())/
      (y.real()*y.real()+y.imag()*y.imag()));

  //  fully correct implementation has more complex return type
  //
  //  typedef typename boost::units::multiply_typeof_helper<X,Y>::type xy_type;
  //  typedef typename boost::units::multiply_typeof_helper<Y,Y>::type yy_type;
  //
  //  typedef typename boost::units::add_typeof_helper<xy_type, xy_type>::type
  //      xy_plus_xy_type;
  //  typedef typename boost::units::subtract_typeof_helper<
  //      xy_type,xy_type>::type xy_minus_xy_type;
  //
  //  typedef typename boost::units::divide_typeof_helper<
  //      xy_plus_xy_type,yy_type>::type      xy_plus_xy_over_yy_type;
  //  typedef typename boost::units::divide_typeof_helper<
  //      xy_minus_xy_type,yy_type>::type     xy_minus_xy_over_yy_type;
  //
  //  BOOST_STATIC_ASSERT((boost::is_same<xy_plus_xy_over_yy_type,
  //                                  xy_minus_xy_over_yy_type>::value == true));
  //
  //  return Complex<xy_plus_xy_over_yy_type>(
  //      (x.real()*y.real()+x.imag()*y.imag())/
  //          (y.real()*y.real()+y.imag()*y.imag()),
  //      (x.imag()*y.real()-x.real()*y.imag())/
  //          (y.real()*y.real()+y.imag()*y.imag()));
}

template<class Y>
Complex<Y> 
pow(const Complex<Y>& x,const Y& y)
{
  std::complex<Y> tmp(x.real(),x.imag());

  tmp = std::pow(tmp,y);

  return Complex<Y>(tmp.real(),tmp.imag());
}

template<class Y>
Complex<Y> 
sqrt(const Complex<Y>& x)
{
  return pow(x, 0.5);
}

template<class Y>
bool isfinite(const Complex<Y>& x)
{
  using std::isfinite;
  return isfinite(x.real()) && isfinite(x.imag());
}

template<class Y>
std::ostream& operator<<(std::ostream& os,const Complex<Y>& val)
{
  os << val.real() << " + " << val.imag() << " i";

  return os;
}

}} // Leave namespaces

namespace boost { namespace units {

/// specialize power typeof helper for Complex<Y>
template<class Y,long N,long D> 
struct power_typeof_helper<
  fearless::maths::Complex<Y>,
  boost::units::static_rational<N,D>
>
{
  typedef fearless::maths::Complex<
    typename boost::units::power_typeof_helper<
      Y,boost::units::static_rational<N,D>
    >::type
  > type; 

  static type value(const fearless::maths::Complex<Y>& x)  
  { 
    const boost::units::static_rational<N,D>  rat;

    const Y    m = Y(rat.numerator())/Y(rat.denominator());

    return boost::units::pow(x,m);
  }
};

/// specialize root typeof helper for Complex<Y>
template<class Y,long N,long D> 
struct root_typeof_helper<
  fearless::maths::Complex<Y>,
  boost::units::static_rational<N,D>
>
{ 
  typedef fearless::maths::Complex<
    typename boost::units::root_typeof_helper<
      Y,boost::units::static_rational<N,D>
    >::type
  > type; 

  static type value(const fearless::maths::Complex<Y>& x)  
  { 
    const boost::units::static_rational<N,D>  rat;

    const Y    m = Y(rat.denominator())/Y(rat.numerator());

    return boost::units::pow(x,m);
  }
};

/// specialize power typeof helper for Complex<quantity<Unit,Y> >
template<class Y,class Unit,long N,long D> 
struct power_typeof_helper<
  fearless::maths::Complex<quantity<Unit,Y> >,
  boost::units::static_rational<N,D>
>
{
  typedef typename boost::units::power_typeof_helper<
      Y,boost::units::static_rational<N,D>
    >::type value_type;
  typedef typename boost::units::power_typeof_helper<
      Unit,boost::units::static_rational<N,D>
    >::type unit_type;
  typedef quantity<unit_type,value_type>                      quantity_type;
  typedef fearless::maths::Complex<quantity_type>             type; 

  static type value(const fearless::maths::Complex<quantity<Unit,Y> >& x)  
  { 
    const fearless::maths::Complex<value_type>   tmp =
      pow<boost::units::static_rational<N,D> >(
          fearless::maths::Complex<Y>(x.real().value(),x.imag().value()));

    return type(quantity_type::from_value(tmp.real()),
        quantity_type::from_value(tmp.imag()));
  }
};

/// specialize root typeof helper for Complex<quantity<Unit,Y> >
template<class Y,class Unit,long N,long D> 
struct root_typeof_helper<
  fearless::maths::Complex<quantity<Unit,Y> >,
  boost::units::static_rational<N,D>
>
{ 
  typedef typename boost::units::root_typeof_helper<
      Y,boost::units::static_rational<N,D>
    >::type value_type;
  typedef typename boost::units::root_typeof_helper<
      Unit,boost::units::static_rational<N,D>
    >::type unit_type;
  typedef quantity<unit_type,value_type>                      quantity_type;
  typedef fearless::maths::Complex<quantity_type>             type; 

  static type value(const fearless::maths::Complex<quantity<Unit,Y> >& x)  
  { 
    const fearless::maths::Complex<value_type>   tmp =
      root<boost::units::static_rational<N,D> >(
          fearless::maths::Complex<Y>(x.real().value(),x.imag().value()));

    return type(quantity_type::from_value(tmp.real()),
        quantity_type::from_value(tmp.imag()));
  }
};

}}

#endif // FEARLESS_MATHS__COMPLEX_HPP

