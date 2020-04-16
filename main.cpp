#include "includes.hpp"

//#include <boost/geometry.hpp>
//#include <boost/geometry/arithmetic/dot_product.hpp>
#include <iostream>
#include <iomanip>



//namespace bg = boost::geometry;

void save_to_bmp(std::string image_name, int height, int width, std::vector<rgb_t>& data){

bitmap_image image(width,height);

   for(unsigned int j = 0 ; j < image.height(); ++j){
     for(unsigned int i {0} ; i < image.width(); ++i){
       
       image.set_pixel(i , j , data[ i + j * image.height() ] );
     }
   }

   image.save_image(image_name);
}


int main(){
  
  std::vector<rgb_t> data;
  const int height = 600;
  const int width = 600;

  ShadeRec r;

  Sphere s1(maths::Point3D(300.0f, 300.0f, 0.0f), 250.0f);
  s1.SetColour({255,0,0});
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

}
