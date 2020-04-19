#ifndef LIGHTS_HPP
#define LIGHTS_HPP

#include "Maths/maths.hpp"
#include "Colour/colour.hpp"
#include "World/world.hpp"
#include "ShadeRec/shaderec.hpp"


class Light
{
public:

  Light() {}
  virtual ~ Light() {}
  
  virtual maths::Vector getDirection(ShadeRec& sr) const = 0;

  Colour L ( [[maybe_unused]] ShadeRec& sr);

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


class Directional : public Light
{
public:
  Directional() : Light{}
  {}

  Directional(maths::Vector const& d)
  {
    setDirection(d);
  }

  void setDirection(maths::Vector const& d)
  {
    direction_ = d;
    direction_.Normalize();
  }

  maths::Vector getDirection([[maybe_unused]] ShadeRec& sr) const
  {
    return direction_;
  }

  bool in_shadow(maths::Ray const& ray, ShadeRec& sr) const;
     
private:
  maths::Vector direction_;
};

class PointLight : public Light
{
public:
  PointLight()
  {}

  PointLight(maths::Point3D const& loc)
  {
    set_location(loc);
  }

  void set_location(maths::Point3D const& loc) {
    location_ = loc;
  }
  
  maths::Vector getDirection([[maybe_unused]] ShadeRec& sr) const
  {
    maths::Vector dir(location_.X() - sr.hit_point.X(),
		      location_.Y() - sr.hit_point.Y(),
		      location_.Z() - sr.hit_point.Z());
      dir.Normalize();

    return dir;
  }

  bool in_shadow(maths::Ray const& ray, ShadeRec& sr) const;

private:
    maths::Point3D location_;
};

class Ambient : public Light
{
public:
    Ambient() : Light{}
    {}

    maths::Vector getDirection( [[maybe_unused]] ShadeRec& sr) const
    {
      return maths::Vector{ 0.0f, 0.0f, 0.0f };
    }

    bool in_shadow([[maybe_unused]] maths::Ray const& ray,
		   [[maybe_unused]] ShadeRec& trace_data) const { 

        return false;
    }
};

#endif
