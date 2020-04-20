#include "material.hpp"

#include "Maths/maths.hpp"
#include "BRDF/brdf.hpp"
#include "World/world.hpp"
#include "Lights/lights.hpp"
#include "ShadeRec/shaderec.hpp"

Colour Matte::shade(ShadeRec& sr)
{
  maths::Vector wo = -1.0f * sr.ray.d;
  Colour L = ambient_BRDF_->rho(sr, wo) * sr.world->amb_light_ptr->L(sr);
  size_t numLights = sr.world->lights.size();

  for (size_t i{ 0 }; i < numLights; ++i)
    {
      maths::Vector wi = sr.world->lights[i]->getDirection(sr);
      float nDotWi = maths::Vector::Dot(sr.normal, wi);

      if (nDotWi > 0.0f)
	{
	  bool in_shadow = false;

	  if (sr.world->lights[i]->cast_shadows()) {
	    maths::Ray shadowRay(sr.hit_point, wi);
	    in_shadow = sr.world->lights[i]->in_shadow(shadowRay, sr);
	  }

	  if (!in_shadow) {
	    L += diffuse_BRDF_->fn(sr, wo, wi) * sr.world->lights[i]->L(sr) *
	      nDotWi;
	  }
	}
    }

  return L;
}

Colour Phong::shade(ShadeRec& sr)
  {
    maths::Vector wo = -1.0f * sr.ray.d;
    Colour L = ambient_BRDF_->rho(sr, wo) * sr.world->amb_light_ptr->L(sr);
    size_t numLights = sr.world->lights.size();
    
    for (size_t i{ 0 }; i < numLights; ++i) {
	maths::Vector wi = sr.world->lights[i]->getDirection(sr);

	float nDotWi = maths::Vector::Dot(sr.normal, wi);
	if (nDotWi > 0.0f) {
	  bool in_shadow = false;
	  if (sr.world->lights[i]->cast_shadows()) {
	    maths::Ray shadowRay(sr.hit_point, wi);
	    in_shadow = sr.world->lights[i]->in_shadow(shadowRay, sr); 
	  }
                
	  if (!in_shadow) {
	    L += (diffuse_BRDF_->fn(sr, wo, wi) + specular_BRDF_->fn(sr, wo, wi))
	      * sr.world->lights[i]->L(sr)
	      * nDotWi;
	  }
    }
   }
    return L;
  }

Colour Reflective::shade(ShadeRec& sr)
{
     Colour L = Phong::shade(sr);

     maths::Vector wo = -1.0f * sr.ray.d;
     maths::Vector wi;
     Colour fr = perfect_specular_BRDF_->sample_f(sr, wo, wi);
     
     maths::Ray reflected_ray(sr.hit_point, wi);

     Colour c = sr.world->tracer_ptr->trace_ray(reflected_ray, sr.depth + 1);
   
     L += fr * c * maths::Vector::Dot(sr.normal, wi);
     return(L);
 }
