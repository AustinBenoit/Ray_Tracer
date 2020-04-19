#ifndef BRDF_HPP
#define BRDF_HPP

#include "includes.hpp"

class BRDF
{
public:
  virtual ~BRDF() = default;

  virtual Colour fn(ShadeRec const& sr,
		    maths::Vector const& reflected,
		    maths::Vector const& incoming) const = 0;
  virtual Colour rho(ShadeRec const& sr,
		     maths::Vector const& reflected) const = 0;
};

class PerfectSpecular : public BRDF {
public:

  Colour fn(ShadeRec const& sr,
	    maths::Vector const& reflected,
	    maths::Vector const& incoming) const ;
  
  Colour rho(ShadeRec const& sr,
	     maths::Vector const& reflected) const;
  
  Colour sample_f(ShadeRec const& sr,
		  maths::Vector const& wo,
		  maths::Vector& wi) const;
  
  void setSpecularReflection(float kr) {
    specular_reflection_ = kr;
  }
  
  void setSpecularColour(Colour cs) {
    specular_colour_ = cs;
  }
  
private:
  float specular_reflection_; //ks
  Colour specular_colour_; //Cs
};

class Lambertian : public BRDF
{
public:
  Lambertian() : diffuse_colour_{}, diffuse_reflection_{} {}

  Lambertian(Colour diffuseColor, float diffuseReflection) :
    diffuse_colour_{ diffuseColor }, diffuse_reflection_ { diffuseReflection }
  {}
  
  Colour fn([[maybe_unused]] ShadeRec const& sr,
	    [[maybe_unused]] maths::Vector const& reflected,
	    [[maybe_unused]] maths::Vector const& incoming) const;
  
  Colour rho([[maybe_unused]] ShadeRec const& sr,
	     [[maybe_unused]] maths::Vector const& reflected) const;

    void setDiffuseReflection(float kd)
    {
        diffuse_reflection_ = kd;
    }

    void setDiffuseColour(Colour const& colour)
    {
        diffuse_colour_ = colour;
    }

private:
    Colour diffuse_colour_;
    float diffuse_reflection_;
};

class GlossySpecular : public BRDF {
public:
  GlossySpecular() :  specular_reflection_{}, specular_colour_{}, exps_{}
  {}

  GlossySpecular(Colour cs, float ks, float e)
    :  specular_reflection_{ ks }, specular_colour_{ cs }, exps_{ e }
  {}

  Colour fn([[maybe_unused]] ShadeRec const& sr,
	    [[maybe_unused]] maths::Vector const& reflected,
	    [[maybe_unused]] maths::Vector const& incoming) const;
  
  Colour rho([[maybe_unused]] ShadeRec const& sr,
	     [[maybe_unused]] maths::Vector const& reflected) const;
  
  void setSpecularReflection(float ks) {
    specular_reflection_ = ks;
  }
  void setSpecularColour(Colour cs) {
    specular_colour_ = cs;
  }
  void setExp(float e) {
    exps_ = e;
  }

private:
  float specular_reflection_; //ks
  Colour specular_colour_; //Cs
  float exps_; // e
};

#endif
