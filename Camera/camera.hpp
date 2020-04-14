#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "../Maths/maths.hpp"

// Finish making it use the maths class

namespace camera
{

  class Camera {
  public:
    maths::Point3D eye_, look_at_;
    maths::Vector up_, u_, v_, w_;

    void compute_uvw() {
      w_ = (eye_ - look_at_);
      w_.normalize();
      u_ = glm::cross(up_, w_));
      u_.normalize();
      v_ = glm::normalize(glm::cross(w_, u_));
      
      if (areEqual(eye_.x, look_at_.x) && areEqual(eye_.z, look_at_.z) &&
	  eye_.y > look_at_.y)
        {
	  u_ = { 0.0f, 0.0f, 1.0f };
	  v_ = { 1.0f, 0.0f, 0.0f };
	  w_ = { 0.0f, 1.0f, 0.0f };
        }
      
      if (areEqual(eye_.x, look_at_.x) && areEqual(eye_.z, look_at_.z) &&
	  eye_.y < look_at_.y)
        {
	  u_ = { 1.0f, 0.0f, 0.0f };
	  v_ = { 0.0f, 0.0f, 1.0f };
	  w_ = { 0.0f, -1.0f, 0.0f };
        }
      
      
    }
    virtual void render_scene(std::string out_file, World& w, int num_slabs, bool mult) = 0;
    
  };
  */
  
  /*
  class PinHole : public Camera
  {


  };
  */

}


#endif
