#ifndef COLOUR_HPP
#define COLOUR_HPP

#include "BMP/bitmap_image.hpp"

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

inline Colour operator * ( const Colour & c1, const Colour & c2 )
{return Colour(c1.r * c2.r, c1.g * c2.g, c1.b * c2.b); }

inline Colour operator + ( const Colour & c1, const Colour & c2 )
{return Colour(c1.r + c2.r, c1.g + c2.g, c1.b + c2.b); }

namespace colours {

const Colour ORANGE        (1.0f, 0.7f, 0.0f);
const Colour LIME_GREEN    (0.0f, 1.0f, 0.0f);
const Colour RED           (1.0f, 0.0f, 0.0f);
const Colour BLUE          (0.0f, 0.0f, 1.0f);
const Colour WHITE         (1.0f, 1.0f, 1.0f);
const Colour GREY          (0.2f, 0.2f, 0.2f);
const Colour LIGHT_BLUE    (0.2f, 0.6f, 1.0f);
}

#endif 
