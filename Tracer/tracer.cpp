#include "tracer.hpp"
#include "World/world.hpp"
#include "Material/material.hpp"

Colour MultipuleObj::trace_ray
  (maths::Ray const& ray, const int depth) const
  {
    if (depth > world_ptr_->vp.max_depth) {
    return{ 0,0,0 };
    }
    else {

        ShadeRec sr{};
        sr.world = world_ptr_;
        world_ptr_->hit_colour(ray, sr);

        if (sr.hit_obj) {
            sr.world = world_ptr_;
            sr.depth = depth;
            sr.ray = ray;
            Colour c = sr.material->shade(sr);
            return(c);
        }
        else {
            return { 0,0,0 };
        }

	}
 
}

