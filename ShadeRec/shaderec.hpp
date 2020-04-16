#ifndef SHADEREC_HPP
#define SHADEREC_HPP

#include "includes.hpp"

class Material;

struct ShadeRec {
  bool                    hit_obj;       // Was an object hit?
  rgb_t                   colour;         //Colour of the hit point      
  float                   t;              //ray length
  maths::Vector           normal;         //normal at hit_point
  maths::Point3D          hit_point;
  maths::Ray              ray;
  std::shared_ptr<Material> material;
  //World* world;
  int                     depth{0};
};

#endif
