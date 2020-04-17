#include "lights.hpp"
#include "includes.hpp"

/*
virtual Colour Light::L([[maybe_unused]] ShadeRec& sr)
{
  return radiance_ * colour_;
}
*/

void Light::scaleRadiance(float b)
{
  radiance_ = b;
}
  
void Light::setColour(Colour const& c)
{
  colour_ = c;
}

Colour operator * (float f , const Colour & c ){
  return Colour(c.r * f, c.g * f, c.b * f);
}
