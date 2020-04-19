#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Maths/maths.hpp"
#include "BMP/bitmap_image.hpp"
#include "Colour/colour.hpp"
#include "Tracer/tracer.hpp"
#include "ViewPlane/viewplane.hpp"

// Needs:
// maths
// ShadeRec
  class Camera {
  public:
    maths::Point3D eye_, look_at_;
    maths::Vector up_, u_, v_, w_;

    void compute_uvw();
    
    virtual void render_scene
    (std::string out_file, World& w, int num_slabs, bool mult) = 0;
    
  };
  
class PinHole : public Camera {
private:
      float d_;
  
public:
    void set_eye(maths::Point3D eye) {
        eye_ = eye;
    }
    void set_lookat(maths::Point3D look) {
        look_at_ = look;
    }
    void set_view_distance(float dist) {
        d_ = dist;
    }
    void set_up(maths::Vector up) {
        up_ = up;
    }

    void get_image(ViewPlane& vp, World& w,
		   std::vector<rgb_t>& output_image,
		   std::size_t start_row, std::size_t start_col,
		   std::size_t end_row, std::size_t end_col);

    PinHole() {}

  void render_scene(std::string out_file, World& w, int num_slabs, bool multi );
  
  maths::Vector ray_direction(const maths::Point3D& p);
};

#endif
