#ifndef GEOMETRICOBJECT_HPP
#define GEOMETRICOBJECT_HPP

#include "Maths/maths.hpp"
#include "ShadeRec/shaderec.hpp"


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



class Triangle : public GeometricObj {
public:

  Triangle(maths::Point3D a, maths::Point3D b, maths::Point3D c, Colour colour) :
    p1_{ a }, p2_{ b }, p3_{ c }
  {
    colour_ = colour;

    maths::Vector ab( p2_.X() - p1_.X(), p2_.Y() - p1_.Y(), p2_.Z() - p1_.Z());
    maths::Vector ac( p3_.X() - p1_.X(), p3_.Y() - p1_.Y(), p3_.Z() - p1_.Z());	
    normal_ = maths::Vector::Cross(ab, ac);
    normal_.Normalize();
  }

  bool Hit(maths::Ray const& ray, ShadeRec& trace_data) const ;

  bool ShadowHit(maths::Ray const& ray, float& tmin) const;

private:
  maths::Point3D p1_, p2_, p3_;
  maths::Vector normal_;
  
};

class Plane : public GeometricObj {
public:
  Plane(maths::Point3D p, maths::Vector n, Colour colour) :
    point_{ p }
  {
    colour_ = colour;
    normal_ = n;
    normal_.Normalize();
  }

  bool Hit(maths::Ray const& ray, ShadeRec& trace_data) const;
  bool ShadowHit(maths::Ray const& ray, float& tmin) const;
private:
  maths::Point3D point_;
  maths::Vector normal_;
  
};
#endif

