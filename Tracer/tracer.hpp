#ifndef TRACER_HPP
#define TRACER_HPP

#include "World/world.hpp"
#include "Material/material.hpp"

class World;

class Tracer {
public:
    Tracer() {};
  
    Tracer(World* world_ptr) :
        world_ptr_{ world_ptr } {}
  
    virtual Colour trace_ray
    (maths::Ray const& ray, const int depth) const = 0;

protected:
    World* world_ptr_;
};


class MultipuleObj : public Tracer{ //: public Tracer {
public:
  World* world_ptr_;
  MultipuleObj(World* world_ptr) {
    world_ptr_ = world_ptr;
  }
  
  Colour trace_ray
  (maths::Ray const& ray, const int depth) const; 
    
};

#endif 
