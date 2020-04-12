#include "BMP/bitmap_image.hpp"
#include <boost/geometry.hpp>
#include <boost/geometry/arithmetic/dot_product.hpp>
#include <iostream>
#include <iomanip>

// Add in typedefing for the point class

namespace bg = boost::geometry;

void save_to_bmp(std::string image_name, int height, int width, std::vector<rgb_t>& data){

bitmap_image image(width,height);

   for(unsigned int j = 0 ; j < image.height(); ++j){
     for(unsigned int i {0} ; i < image.width(); ++i){
       
       image.set_pixel(i , j , data[ i + j * image.height() ] );
     }
   }

   image.save_image(image_name);
}

class Sphere  {

	/* class for a sphere
	*
	*/

public:
  Sphere(bg::model::point<float, 3, bg::cs::cartesian>  center, float radius) :
    center_{ center },
    //radius_{ radius },
    radius_sqr_{ radius * radius }
  { }

  bool hit(bg::model::point<float, 3, bg::cs::cartesian> origin,
	   bg::model::point<float, 3, bg::cs::cartesian>  direction) const 
	{
	  boost::geometry::subtract_point(origin, center_);
	  auto o_c { origin };
	  auto a{ boost::geometry::dot_product(direction, direction) };
	  auto b{ boost::geometry::dot_product(direction, o_c) * 2 };
	  auto c{ boost::geometry::dot_product(o_c, o_c) - radius_sqr_ };
	  
	  auto roots{ b * b - (4.0f * a * c) };
	  if (roots >= 0.0f) {
			//hit
	    float t = ((-b - std::sqrt(roots)) / (2.0f * a));
	    if (t > 0.0f) {
	      return true;
	    }
			
	  }
	  return false;
	}
  
private:
  bg::model::point<float, 3, bg::cs::cartesian>  center_;
  //float radius_;
  float radius_sqr_;
};



int main(){
  std::vector<rgb_t> data;
  const int height = 600;
  const int width = 600;

  Sphere s1(bg::model::point<float, 3, bg::cs::cartesian>(300.0f, 300.0f, 0.0f), 300.0f);
  for(int j {0} ; j < height; ++j){
     for(int i {0} ; i < width; ++i){
       bg::model::point<float, 3,bg::cs::cartesian> origin
       	 ((0.0f) + (float)i +  0.5f , 0.0f + (float)j + 0.5f, 900.0f);
       
       bg::model::point<float, 3,bg::cs::cartesian> direction
	 (0.0f , 0.0f, -1.0f);
	rgb_t c{0,0,0};
	 if(s1.hit(origin, direction)){
	   c = make_colour(0,0,255);
	 }else{
	   c = make_colour(0,0,0);
	 }
	 
       data.push_back(c);
     }
   }


   save_to_bmp("output.bmp", height, width, data);
   
   return 0;

}
