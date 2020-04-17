#ifndef GEOMETRICOBJECT_HPP
#define GEOMETRICOBJECT_HPP

#include "includes.hpp"

// Needs:
// maths

class GeometricObj{
public:
  virtual bool Hit(maths::Ray const& ray, ShadeRec &s) const = 0;
  virtual bool ShadowHit(maths::Ray const& ray, float & tmin) const = 0;
  void SetColour(Colour const& col);
  Colour GetColour() const;
  
  void setMaterial(std::shared_ptr<Material> const& material) {
    material_ = material;
  }
  
  std::shared_ptr<Material> getMaterial() const {
    return material_;
  }
  
protected:
  Colour colour_;
  std::shared_ptr<Material> material_;
};


class Sphere : public GeometricObj {
public:
  Sphere(maths::Point3D center, float radius);
  bool Hit(maths::Ray const& ray, ShadeRec &s) const;
  bool ShadowHit(maths::Ray const& ray, float & tmin) const;
  float radius();
  
private:
  maths::Point3D  center_;
  float radius_;
  float radius_sqr_;
};
#endif

