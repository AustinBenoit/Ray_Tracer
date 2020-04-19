#include "world.hpp"

#include "Colour/colour.hpp"
#include "GeometricObject/geometricobject.hpp"
#include "Maths/maths.hpp"
#include "ShadeRec/shaderec.hpp"
#include "BMP/bitmap_image.hpp"
#include "Camera/camera.hpp"
#include "ViewPlane/viewplane.hpp"

void World::add_obj(GeometricObj* obj) {
    objs.push_back(obj);
}

bool World::hit_colour(maths::Ray ray, ShadeRec& trace_data) const {
  bool hit = false;
  ShadeRec minShade{};
  float min_t = std::numeric_limits<float>::max();
  for (auto& obj : objs) {
    
    if (obj->Hit(ray, minShade)) {
      
      if (minShade.t < min_t) {
	min_t = minShade.t;
	trace_data = minShade;
	hit = true;
      }
      
    }
    
  }
  
  return hit;
}

//Create an orthographic render of the scene
//Looking down the - z axis perfectly center in the z axis

void World::render_ortho_scene(std::string out_file) {
  // Holds the final image
  std::vector<rgb_t> output_image;
  output_image.assign(vp.x_resolution_ * vp.y_resolution_, background_colour);
  Colour pixel;
  maths::Ray ray;
  ray.d = { 0, 0, -1 };
  
  ShadeRec trace_data{};
  maths::Point3D sp;
  
  for (std::size_t r{ 0 }; r < vp.y_resolution_; ++r) {
    for (std::size_t c{ 0 }; c < vp.x_resolution_; ++c) {
      pixel = { 0,0,0 }; // reset colour
      //for (int j{ 0 }; j < vp.num_samples_; ++j) {
	
	//sp = vp.sampler_ptr_->sampleUnitSquare();
	float x = c - 0.5f * vp.x_resolution_; //+ sp.X();
	float y = r - 0.5f * vp.y_resolution_; //+ sp.Y();

	
        ShadeRec sr{};
        sr.world = this;
	
	ray.o = { x , y , 100 };
	if( hit_colour(ray, sr)) {
	  pixel += sr.colour;
	}
	//}
      // thing are a little up side down just need to go the opposite way then I am good
      //pixel /= vp.num_samples_;
      output_image[c + (vp.x_resolution_ - 1 - r) * vp.y_resolution_] = pixel;
    }
  }
  save_to_bmp(out_file, vp.x_resolution_, vp.y_resolution_, output_image);
}

void World::set_camera(Camera* c_ptr) {
  camera_ptr = c_ptr;
}
