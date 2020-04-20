#include "geometricobject.hpp"

#include "Maths/maths.hpp"
#include "ShadeRec/shaderec.hpp"

void GeometricObj::SetColour(Colour const& col)
{
  colour_ = col;
}

Colour GeometricObj::GetColour() const
{
  return colour_;
}


Sphere::Sphere(maths::Point3D center, float radius) :
    center_{ center },
    radius_{radius},
    radius_sqr_{ radius * radius }
  { }

bool Sphere::Hit( maths::Ray const& ray, ShadeRec &trace_data) const
{
  maths::Vector o_c (ray.o.X() - center_.X(),
		     ray.o.Y() - center_.Y(),
		     ray.o.Z() - center_.Z());
	  
  auto a{ maths::Vector::Dot(ray.d, ray.d) };
  auto b{ maths::Vector::Dot(ray.d, o_c) * 2 };
  auto c{ maths::Vector::Dot(o_c, o_c) - radius_sqr_ };
  
  auto roots{ b * b - (4.0f * a * c) };
  
  if (roots >= 0.0f) {
    //hit

    
    float t = ((-b - std::sqrt(roots)) / (2.0f * a));
    if (t > 0.01f) {
      maths::Vector norm = ((o_c + t * ray.d) / radius_);
      norm.Normalize();
      trace_data.hit_obj = true;
      trace_data.t = t;
      trace_data.colour = colour_;
      trace_data.normal = norm;
      trace_data.material = material_;
      trace_data.hit_point = ray.o + t * ray.d;
      return true;
    }

    t = ((-b + std::sqrt(roots)) / (2.0f * a));
    if (t > 0.01f) {
      maths::Vector norm = ((o_c + t * ray.d) / radius_);
      norm.Normalize();
      trace_data.hit_obj = true;
      
      trace_data.t = t;
      trace_data.colour = colour_;
      trace_data.normal = norm;
      trace_data.material = material_;
      trace_data.hit_point = ray.o + t * ray.d;
      return true;
    }
  }
  
  trace_data.hit_obj = false;
  return false;
}

bool Sphere::ShadowHit(maths::Ray const& ray, float& tmin) const
{
   maths::Vector o_c (ray.o.X() - center_.X(),
		     ray.o.Y() - center_.Y(),
		     ray.o.Z() - center_.Z());
	  
  auto a{ maths::Vector::Dot(ray.d, ray.d) };
  auto b{ maths::Vector::Dot(ray.d, o_c) * 2 };
  auto c{ maths::Vector::Dot(o_c, o_c) - radius_sqr_ };
  
  auto roots{ b * b - (4.0f * a * c) };
  if (roots >= 0.0f) {
    //hit
    float t = ((-b - std::sqrt(roots)) / (2.0f * a));
    if (t > 0.01f) {
      tmin = t;
      return true;
    }

    t = ((-b + std::sqrt(roots)) / (2.0f * a));
    if (t > 0.01f) {
      tmin = t;
      return true;
    }
    
  }

  return false;

}

float Sphere::radius(){
  return radius_;
}
