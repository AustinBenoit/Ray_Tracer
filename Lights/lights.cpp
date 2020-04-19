#include <limits>

#include "Lights/lights.hpp"
#include "Maths/maths.hpp"
#include "Colour/colour.hpp"
#include "World/world.hpp"
#include "ShadeRec/shaderec.hpp"


Colour Light::L([[maybe_unused]] ShadeRec& sr)
{
  return radiance_ * colour_;
}

void Light::scaleRadiance(float b)
{
  radiance_ = b;
}
  
void Light::setColour(Colour const& c)
{
  colour_ = c;
}

bool Directional::in_shadow(maths::Ray const& ray, ShadeRec& sr) const {
  float t = 1000000;
  float d = std::numeric_limits<float>::max();

  for (auto& obj : sr.world->objs) {
    if (obj->ShadowHit(ray, t) && t < d) {
      return true;
    }
  }
  return false;
}

bool PointLight::in_shadow(maths::Ray const& ray, ShadeRec& sr) const {
  float t;
  float d = location_.Distance( ray.o);
  
  for (auto& obj : sr.world->objs) {
    
    if (obj->ShadowHit(ray, t) && t < d){
                return true;
    }
  }
  return false;
}
