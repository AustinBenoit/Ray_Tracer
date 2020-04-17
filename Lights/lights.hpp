#ifndef LIGHTS_HPP
#define LIGHTS_HPP

#include "includes.hpp"

class Light
{
public:
    virtual maths::Vector getDirection(ShadeRec& sr)const = 0;

  virtual Colour L ( [[maybe_unused]] ShadeRec& sr);

  void scaleRadiance(float b);
  
  void setColour(Colour const& c);
  
  virtual bool in_shadow
  (maths::Ray const& ray, ShadeRec& sr) const = 0;
  
  bool cast_shadows()
  {
    return true;
  }
  

protected:
    Colour  colour_;
    float radiance_;

};

#endif
