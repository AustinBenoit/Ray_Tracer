#include "camera.hpp"
#include "includes.hpp"

void Camera::compute_uvw() {
  w_ = maths::Vector(
		     eye_.X() - look_at_.X(),
		     eye_.Y() - look_at_.Y(),
		     eye_.Z() - look_at_.Z());
  w_.Normalize();
  
  u_ = maths::Vector::Cross(up_, w_);
  w_.Normalize();
  
  v_ = maths::Vector::Cross(w_, u_);
  v_.Normalize();
  
  if (areEqual(eye_.X(), look_at_.X()) && areEqual(eye_.Z(), look_at_.Z()) &&
      eye_.Y() > look_at_.Y())
    {
      u_ = { 0.0f, 0.0f, 1.0f };
      v_ = { 1.0f, 0.0f, 0.0f };
      w_ = { 0.0f, 1.0f, 0.0f };
    }
  
  if (areEqual(eye_.X(), look_at_.X()) && areEqual(eye_.Z(), look_at_.Z()) &&
      eye_.Y() < look_at_.Y())
    {
      u_ = { 1.0f, 0.0f, 0.0f };
      v_ = { 0.0f, 0.0f, 1.0f };
      w_ = { 0.0f, -1.0f, 0.0f };
    } 
}



void PinHole::get_image(ViewPlane& vp, World& w,
			std::vector<rgb_t>& output_image,
			std::size_t start_row, std::size_t start_col,
			std::size_t end_row, std::size_t end_col)
{
  float max_colour;
  Colour pixel;
  
  maths::Ray ray;
  
  ray.o = eye_;
  
  //the aa point
  maths::Point3D sp;
  maths::Point3D ray_dir;
  
  for (std::size_t r = start_row; r < end_row; ++r) {
    for (std::size_t c = start_col; c < end_col; ++c) {
      pixel = { 0,0,0 }; // reset colour
      for (int j{ 0 }; j < vp.num_samples_; ++j) {
	
	sp = vp.sampler_ptr_->sampleUnitSquare();
	
	ray_dir.set_x( c - 0.5f  * vp.x_resolution_ + sp.X() );
	ray_dir.set_y(r - 0.5f  * vp.y_resolution_ + sp.Y() );
	
	
	//distance of one away from view  plane
	ray.d = ray_direction(ray_dir);
	
	pixel += w.tracer_ptr->trace_ray(ray, 0);
      }
      
      pixel /= vp.num_samples_;
      
      // check out of gamute
      max_colour = std::max(std::max(pixel.r, pixel.g), pixel.b);
      if (max_colour > 1.0f) {
	pixel.r /= max_colour;
	pixel.g /= max_colour;
	pixel.b /= max_colour;
      }
      
      output_image[c + (vp.x_resolution_ - 1 - r) * vp.y_resolution_] = pixel;
    }
  }
}

void PinHole::render_scene(std::string out_file, World& w,
			   [[maybe_unused]] int num_slabs,
			   [[maybe_unused]] bool multi )
{
  std::vector<rgb_t> output_image;
  ViewPlane vp(w.vp);
  
  output_image.assign(vp.x_resolution_ * vp.y_resolution_, w.background_colour); 
  get_image(vp, w, std::ref(output_image), 0, 0, vp.x_resolution_, vp.y_resolution_);

  
  save_to_bmp(out_file, vp.x_resolution_, vp.y_resolution_, output_image);
}



maths::Vector PinHole::ray_direction(const maths::Point3D& p) {
  //atlas::math::Vector v = glm::normalize();
  maths::Vector v = p.X() * u_ + p.Y() * v_ - d_ * w_;
  v.Normalize();
  return v;
}
