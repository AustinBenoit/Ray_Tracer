#ifndef COLOUR_HPP
#define COLOUR_HPP

#include "includes.hpp"

class Colour{
public:
  float r, g, b;
  Colour(): r{0.0f}, g{0.0f}, b{0.0f} {}
  Colour(float ri, float gi, float bi)
    : r{ri}, g{gi}, b{bi} {}

  //virtual Colour Light::L([[maybe_unused]] ShadeRec& sr);

  operator rgb_t() {
    return rgb_t{ (unsigned char)((int)(r * 255)),
		   (unsigned char)((int)(g * 255)),
		   (unsigned char)((int)(b * 255))};
  }

  void operator += (const Colour & c){
    r += c.r;
    g += c.g;
    b += c.b;
    
  }
  
  void operator /= (float f){
    r /= f;
    g /= f;
    b /= f;
  }

  
};

inline Colour operator * ( float f , const Colour & c )
{return Colour(f * c.r, f * c.g, f * c.b); }

inline Colour operator * ( const Colour & c, float f )
{return Colour(f * c.r, f * c.g, f * c.b); }

inline Colour operator / ( const Colour & c, float f )
{return Colour( c.r / f, c.g / f, c.b / f ); }

#endif 
