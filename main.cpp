#include <iostream>
#include <iomanip>

#include "GeometricObject/geometricobject.hpp"
#include "ViewPlane/viewplane.hpp"
#include "Colour/colour.hpp"
#include "World/world.hpp"
#include "Material/material.hpp"
#include "Lights/lights.hpp"

void World::build(){
  const int height = 600;
  const int width = 600;

  Sphere* s_ptr = new Sphere(maths::Point3D( 0, 85, -50 ), 100.0f);
  s_ptr->SetColour(colours::RED);
  s_ptr->setMaterial(std::make_shared<Reflective>
                     (0.7f, 0.3f, colours::RED, 0.5f, colours::WHITE, 50.0f,
                     colours::WHITE, .8f));
  add_obj(s_ptr);

  s_ptr = new Sphere(maths::Point3D( 95, -85 , -100 ), 100.0f);
  s_ptr->SetColour(Colour(colours::BLUE));
  //s_ptr->setMaterial(std::make_shared<Matte>(0.9f, 0.1f, Colour{ 0, 1, 0 }));
  s_ptr->setMaterial(std::make_shared<Reflective>
                    (0.7f, 0.3f, colours::BLUE, 0.5f, colours::WHITE, 50.0f,
                    colours::WHITE, .8f));
  add_obj(s_ptr);

  s_ptr = new Sphere(maths::Point3D( -95, -85, -100 ), 100.0f);
  s_ptr->SetColour(colours::LIME_GREEN);
  s_ptr->setMaterial(std::make_shared<Reflective>
  (0.7f, 0.3f, colours::LIME_GREEN, 0.5f, colours::WHITE, 50.0f,
  colours::WHITE, .8f));
  add_obj(s_ptr);
  

  tracer_ptr = new MultipuleObj(this);
  background_colour = Colour(1.0f, 1.0f, 1.0f);
  vp.SetResolution(width, height);
  
  vp.SetMaxDepth(1);
    
  amb_light_ptr = new Ambient();
  amb_light_ptr->setColour({ 1, 1, 1 });
  amb_light_ptr->scaleRadiance(1.0f);

  lights.push_back(
      std::make_shared<PointLight>(PointLight{ {0, 300, 300} }));
  lights[0]->setColour({ 1, 1, 1 });
  lights[0]->scaleRadiance(1.5f);
  
  
  PinHole* pinhole_ptr = new PinHole;
  pinhole_ptr->set_eye(maths::Point3D{ 0,0,600 });
  pinhole_ptr->set_lookat(maths::Point3D{ 0,0,0 });
  pinhole_ptr->set_view_distance(500.0f);
  pinhole_ptr->set_up(maths::Vector{ 0,1,0 });
  pinhole_ptr->compute_uvw();
  set_camera(pinhole_ptr);
  
}

int main(){
  World w;
  w.build();
  w.render_ortho_scene("out.bmp");
  w.camera_ptr->render_scene("out_pinhole.bmp", w, 64, false);
  

}
