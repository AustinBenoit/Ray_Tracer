#ifndef WORLD_HPP
#define WORLD_HPP

#include "Colour/colour.hpp"
#include "GeometricObject/geometricobject.hpp"
#include "Maths/maths.hpp"
#include "ShadeRec/shaderec.hpp"
#include "BMP/bitmap_image.hpp"
#include "Camera/camera.hpp"
#include "ViewPlane/viewplane.hpp"

class Camera;
class Light;
class Tracer;

class World {
public:
    // Data
    Colour       background_colour;
    ViewPlane    vp;
    Camera* camera_ptr;
    Tracer* tracer_ptr;
    Light* amb_light_ptr;

    //Vectors to hold everything in the world
    std::vector<std::shared_ptr<Light>>         lights;
    std::vector<GeometricObj*>                  objs;

public:
  //Constructors and functions
  
  World() {}
  
  void build();
  
  void add_obj(GeometricObj* obj);

  void add_light(Light* light);
  
  bool hit_colour(maths::Ray ray, ShadeRec& trace_data) const;
  
  void render_ortho_scene(std::string out_file);

  void set_camera(Camera* c_ptr);
};
#endif
