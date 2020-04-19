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
/*
class Phong : public Material {
public:
    Phong() :
        Material{},x
        mDiffuseBRDF{ new Lambertian() },
        mAmbientBRDF{ new Lambertian() },
        mSpecularBRDF{ new GlossySpecular() }
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
        mDiffuseBRDF->setDiffuseReflection(k);
    }

    void setAmbientReflection(float k)
    {
        mAmbientBRDF->setDiffuseReflection(k);
    }

    void setDiffuseColour(Colour colour)
    {
        mDiffuseBRDF->setDiffuseColour(colour);
        mAmbientBRDF->setDiffuseColour(colour);
    }

    void setSpecularReflection(float k) {
        mSpecularBRDF->setSpecularReflection(k);
    }
    void setSpecularColour(Colour colour) {
        mSpecularBRDF->setSpecularColour(colour);
    }
    void setSpecularExp(float e) {
        mSpecularBRDF->setExp(e);
    }

    Colour shade(ShadeRec& sr) override
    {
        using atlas::math::Ray;
        using atlas::math::Vector;

        Vector wo = -sr.ray.d;
        Colour L = mAmbientBRDF->rho(sr, wo) * sr.world->amb_light_ptr->L(sr);
        size_t numLights = sr.world->lights.size();

        for (size_t i{ 0 }; i < numLights; ++i)
        {
            Vector wi = sr.world->lights[i]->getDirection(sr);

            float nDotWi = glm::dot(sr.normal, wi);
            if (nDotWi > 0.0f) {
                bool in_shadow = false;
                if (sr.world->lights[i]->cast_shadows()) {
                   Ray shadowRay(sr.hit_point, wi);
                   in_shadow = sr.world->lights[i]->in_shadow(shadowRay, sr); 
                }
                
                if (!in_shadow) {
                    L += (mDiffuseBRDF->fn(sr, wo, wi) + mSpecularBRDF->fn(sr, wo, wi)) * sr.world->lights[i]->L(sr) *
                        nDotWi;
                }
            }
        }
        return L;
    }

private:
    std::shared_ptr<Lambertian> mDiffuseBRDF;
    std::shared_ptr<Lambertian> mAmbientBRDF;
    std::shared_ptr<GlossySpecular> mSpecularBRDF;
};

class Reflective : public Phong {
public:
    Reflective() : mPerfectSpecularBRDF{ new PerfectSpecular() }, Phong(){}

    Reflective(float kd, float ka, Colour ca, float ks, Colour cs, float e) : Reflective() {
        setDiffuseReflection(kd);
        setAmbientReflection(ka);
        setDiffuseColour(ca);

        setSpecularReflection(ks);
        setSpecularColour(cs);
        setSpecularExp(e);

        setPerfectSpecularReflection(0.75f);
        setPerfectSpecularColour({ 1,1,1 });
    }

    void setPerfectSpecularReflection(float k) {
        mPerfectSpecularBRDF->setSpecularReflection(k);
    }
    void setPerfectSpecularColour(Colour colour) {
        mPerfectSpecularBRDF->setSpecularColour(colour);
    }

    Colour shade(ShadeRec& sr) override
    {
        using atlas::math::Ray;
        using atlas::math::Vector;

        Colour L = Phong::shade(sr);

        Vector wo = -1.0f * sr.ray.d;
        Vector wi; 
        Colour fr = mPerfectSpecularBRDF->sample_f(sr, wo, wi);
        
        Ray reflected_ray(sr.hit_point, wi);

        Colour c = sr.world->tracer_ptr->trace_ray(reflected_ray, sr.depth + 1);
      
        L += fr * c *glm::dot(sr.normal, wi);
        return(L);
    }
    
private:
    std::shared_ptr<PerfectSpecular> mPerfectSpecularBRDF;
};
*/

#endif


