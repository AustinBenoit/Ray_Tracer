#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <memory>

#include "Maths/maths.hpp"
#include "BRDF/brdf.hpp"
#include "World/world.hpp"
#include "Lights/lights.hpp"
#include "ShadeRec/shaderec.hpp"

class Material
{
public:
  virtual ~Material() = default;

  virtual  Colour shade(ShadeRec& sr) = 0;
};

class Matte : public Material
{
public:
  Matte() :
    Material{},
    diffuse_BRDF_{ new Lambertian() },
    ambient_BRDF_{ new Lambertian() }
  {}

  Matte(float kd, float ka, Colour color) : Matte{}
  {
    setDiffuseReflection(kd);
    setAmbientReflection(ka);
    setDiffuseColour(color);
  }

  void setDiffuseReflection(float k)
  {
    diffuse_BRDF_->setDiffuseReflection(k);
  }

  void setAmbientReflection(float k)
  {
    ambient_BRDF_->setDiffuseReflection(k);
  }

  void setDiffuseColour(Colour colour)
  {
    diffuse_BRDF_->setDiffuseColour(colour);
    ambient_BRDF_->setDiffuseColour(colour);
  }

  Colour shade(ShadeRec& sr);

private:
    std::shared_ptr<Lambertian> diffuse_BRDF_;
    std::shared_ptr<Lambertian> ambient_BRDF_;
};

class Phong : public Material {
public:
  ~Phong() = default;
  Phong() :
    Material{},
    diffuse_BRDF_{ new Lambertian() },
    ambient_BRDF_{ new Lambertian() },
    specular_BRDF_{ new GlossySpecular() }
  {}

  Phong(float kd, float ka, Colour ca, float ks, Colour cs, float e) : Phong() {
    setDiffuseReflection(kd);
    setAmbientReflection(ka);
    setDiffuseColour(ca);

    setSpecularReflection(ks);
    setSpecularColour(cs);
    setSpecularExp(e);
  }

  void setDiffuseReflection(float k)
  {
    diffuse_BRDF_->setDiffuseReflection(k);
  }

  void setAmbientReflection(float k)
  {
    ambient_BRDF_->setDiffuseReflection(k);
  }

  void setDiffuseColour(Colour colour)
  {
    diffuse_BRDF_->setDiffuseColour(colour);
    ambient_BRDF_->setDiffuseColour(colour);
  }

  void setSpecularReflection(float k) {
    specular_BRDF_->setSpecularReflection(k);
  }
  void setSpecularColour(Colour colour) {
    specular_BRDF_->setSpecularColour(colour);
  }
  void setSpecularExp(float e) {
    specular_BRDF_->setExp(e);
  }

  Colour shade(ShadeRec& sr);

private:
  std::shared_ptr<Lambertian> diffuse_BRDF_;
  std::shared_ptr<Lambertian> ambient_BRDF_;
  std::shared_ptr<GlossySpecular> specular_BRDF_;
};

class Reflective : public Phong {
public:
    Reflective() : Phong(), perfect_specular_BRDF_{ new PerfectSpecular() } {}

    Reflective(float kd, float ka, Colour ca, float ks, Colour cs, float e,
               Colour cps, float es ) : Reflective() {
        setDiffuseReflection(kd);
        setAmbientReflection(ka);
        setDiffuseColour(ca);

        setSpecularReflection(ks);
        setSpecularColour(cs);
        setSpecularExp(e);

        setPerfectSpecularReflection(es);
        setPerfectSpecularColour(cps);
    }

    void setPerfectSpecularReflection(float k) {
        perfect_specular_BRDF_->setSpecularReflection(k);
    }
    void setPerfectSpecularColour(Colour colour) {
        perfect_specular_BRDF_->setSpecularColour(colour);
    }

  Colour shade(ShadeRec& sr);
    
private:
    std::shared_ptr<PerfectSpecular> perfect_specular_BRDF_;
};

#endif


