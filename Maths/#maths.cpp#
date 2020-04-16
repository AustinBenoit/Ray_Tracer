#include "maths.hpp"

#include <cmath>
#include <memory>

maths::Point3D::Point3D() :
  x_{0}, y_{0}, z_{0} {}

maths::Point3D::Point3D(float x, float y, float z) :
  x_{x}, y_{y}, z_{z} {}

float maths::Point3D::X() const { return x_; }
float maths::Point3D::Y() const { return y_; }
float maths::Point3D::Z() const { return z_; }

void maths::Point3D::set_x( float x ) { x_ = x;}
void maths::Point3D::set_y( float y ) { y_ = y;}
void maths::Point3D::set_z( float z ) { z_ = z;}


maths::Vector::Vector() :
  x_{0}, y_{0}, z_{0} {}

maths::Vector::Vector(float x, float y, float z) :
  x_{x}, y_{y}, z_{z} {}

float maths::Vector::X() const { return x_; }
float maths::Vector::Y() const { return y_; }
float maths::Vector::Z() const { return z_; }

void maths::Vector::set_x( float x ) { x_ = x;}
void maths::Vector::set_y( float y ) { y_ = y;}
void maths::Vector::set_z( float z ) { z_ = z;}

float maths::Vector::Dot(const Vector &v1, const Vector &v2){
  return (v1.x_ * v2.x_ + v1.y_ * v2.y_ + v1.z_ * v2.z_); 
}

maths::Vector maths::Vector::Cross(const Vector &v1, const Vector &v2){
  return Vector(v1.y_ * v2.z_ - v1.z_ * v2.y_ ,
		v1.z_ * v2.x_ - v1.x_ * v2.z_ ,
		v1.x_ * v2.y_ - v1.y_ * v2.x_);
}

void maths::Vector::Normalize(){
  float length = std::sqrt(x_ * x_ + y_ * y_ + z_ * z_);

  x_ = x_ / length;
  y_ = y_ / length;
  z_ = z_ / length;
}

maths::Ray::Ray() :
  o{maths::Point3D()},
  d{maths::Vector()}
  {}

maths::Ray::Ray(float ox, float oy, float oz, float dx, float dy, float dz) :
  o{maths::Point3D(ox, oy, oz)},
  d{maths::Vector(dx, dy, dz)}
{}

