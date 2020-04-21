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

bool Triangle::Hit(maths::Ray const& ray,
		   ShadeRec& trace_data) const
{
  float a = p1_.X() - p2_.X(), b = p1_.X() - p3_.X(), c = ray.d.X(), d = p1_.X() - ray.o.X();
  float e = p1_.Y() - p2_.Y(), f = p1_.Y() - p3_.Y(), g = ray.d.Y(), h = p1_.Y() - ray.o.Y();
  float i = p1_.Z() - p2_.Z(), j = p1_.Z() - p3_.Z(), k = ray.d.Z(), l = p1_.Z() - ray.o.Z();

  float m = f * k - g * j, n = h * k - g * l, p = f * l - h * j;
  float q = g * i - e * k, s = e * j - f * i;

  float inverse_denom = 1.0f / (a * m + b * q + c * s);
  float e1 = d * m - b * n - c * p;
  float beta = e1 * inverse_denom;

  if (beta < 0.0f) {
    trace_data.hit_obj = false;
    return false;
  }

  float r = e * l - h * i;
  float e2 = a * n + d * q + c * r;
  float gamma = e2 * inverse_denom;

  if (gamma < 0.0f) {
    trace_data.hit_obj = false;
    return false;
  }

  if (gamma + beta > 1.0f) {
    trace_data.hit_obj = false;
    return false;
  }

  float e3 = a * p - b * r + d * s;
  float t = e3 * inverse_denom;

  trace_data.colour = colour_;
  trace_data.t = t;
  trace_data.hit_obj = true;
  trace_data.normal = normal_;
  trace_data.material = material_;
  trace_data.hit_point = ray.o + t * ray.d;
  
  if (t > 0.001f) {
    return true;
  }
  else {
    trace_data.hit_obj = true;
    return false;
  }

}

bool Triangle::ShadowHit(maths::Ray const& ray, float& tmin) const
{

  float a = p1_.X() - p2_.X(), b = p1_.X() - p3_.X(), c = ray.d.X(), d = p1_.X() - ray.o.X();
  float e = p1_.Y() - p2_.Y(), f = p1_.Y() - p3_.Y(), g = ray.d.Y(), h = p1_.Y() - ray.o.Y();
  float i = p1_.Z() - p2_.Z(), j = p1_.Z() - p3_.Z(), k = ray.d.Z(), l = p1_.Z() - ray.o.Z();

  float m = f * k - g * j, n = h * k - g * l, p = f * l - h * j;
  float q = g * i - e * k, s = e * j - f * i;

  float inverse_denom = 1.0f / (a * m + b * q + c * s);
  float e1 = d * m - b * n - c * p;
  float beta = e1 * inverse_denom;

  if (beta < 0.0f) {

    return false;
  }

  float r = e * l - h * i;
  float e2 = a * n + d * q + c * r;
  float gamma = e2 * inverse_denom;

  if (gamma < 0.0f) {

    return false;
  }

  if (gamma + beta > 1.0f) {

    return false;
  }

  float e3 = a * p - b * r + d * s;
  float t = e3 * inverse_denom;

  if (t > 0.001) {
    tmin = t;
    return true;
  } else
    return false;
}

bool Plane::Hit(maths::Ray const& ray, ShadeRec& trace_data) const
{
  maths::Vector po (point_.X() - ray.o.X(), point_.Y() - ray.o.Y(), point_.Z() - ray.o.Z());
  float t = (maths::Vector::Dot(po, normal_)) / maths::Vector::Dot(ray.d, normal_);


  if (t > 0.0f) {
    trace_data.hit_obj = true;
    trace_data.t = t;
    trace_data.colour = colour_;
    trace_data.normal = normal_;
    trace_data.material = material_;
    trace_data.material = material_;
    trace_data.hit_point = ray.o + t * ray.d;

    return true;

  }
  trace_data.hit_obj = false;
  return false;
}

bool Plane::ShadowHit(maths::Ray const& ray, float& tmin) const
{
  maths::Vector po (point_.X() - ray.o.X(), point_.Y() - ray.o.Y(), point_.Z() - ray.o.Z());
  float t = (maths::Vector::Dot(po, normal_)) / maths::Vector::Dot(ray.d, normal_);
    
  if (t > 0.001f) {
    tmin = t;
    return true;
  }
  return false;
}
