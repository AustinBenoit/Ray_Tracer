#include "includes.hpp"

//#include <boost/geometry.hpp>
//#include <boost/geometry/arithmetic/dot_product.hpp>
#include <iostream>
#include <iomanip>



//namespace bg = boost::geometry;

void World::build(){
  const int height = 600;
  const int width = 600;

  Sphere* s_ptr = new Sphere(maths::Point3D( 0, 90, -100 ), 100.0f);
  s_ptr->SetColour(Colour(0.0f, 0.0f, 1.0f));
  add_obj(s_ptr);

  s_ptr = new Sphere(maths::Point3D( 90, -40 , -100 ), 100.0f);
  s_ptr->SetColour(Colour(1.0f, 0.0f, 0.0f));
  add_obj(s_ptr);

  s_ptr = new Sphere(maths::Point3D( -90, -40, -100 ), 100.0f);
  s_ptr->SetColour(Colour(0.0f, 1.0f, 0.0f));
  add_obj(s_ptr);
  

  //tracer_ptr = new MultipuleObj(this);
  background_colour = Colour(1.0f, 1.0f, 1.0f);
  vp.SetResolution(width, height);
  
  vp.SetMaxDepth(4);

  

}

int main(){
  
  //std::vector<rgb_t> data;
  //const int height = 600;
  //const int width = 600;

  World w;
  w.build();

  w.render_ortho_scene("out.bmp");

  
  /*
  ShadeRec r;

  Sphere s1(maths::Point3D(300.0f, 300.0f, 0.0f), 250.0f);
  s1.SetColour({1.0f,0.0f,0.0f});
  for(int j {0} ; j < height; ++j){
     for(int i {0} ; i < width; ++i){
       maths::Vector direction(0.0f , 0.0f, -1.0f);
	if(s1.Hit(maths::Ray((0.0f) + (float)i +  0.5f , 0.0f + (float)j + 0.5f, 900.0f ,
			     0.0f , 0.0f, -1.0f ), r )) {
	  data.push_back(r.colour);
	 }else{
	  data.push_back({0,0,0});
	 }
     }
   }

   save_to_bmp("output.bmp", height, width, data);
   return 0;
  */

}
