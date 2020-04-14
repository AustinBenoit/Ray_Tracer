#include "BMP/bitmap_image.hpp"
#include "Maths/maths.hpp"

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

class Sphere  {

	/* class for a sphere
	*
	*/

public:
  Sphere(maths::Point3D center, float radius) :
    center_{ center },
    //radius_{ radius },
    radius_sqr_{ radius * radius }
  { }

  bool hit( maths::Ray ray)
	{
	  
	  maths::Vector o_c (ray.o.x() - center_.x(),
			     ray.o.y() - center_.y(),
			     ray.o.z() - center_.z());
	  
	  auto a{ maths::Vector::dot(ray.d, ray.d) };
	  auto b{ maths::Vector::dot(ray.d, o_c) * 2 };
	  auto c{ maths::Vector::dot(o_c, o_c) - radius_sqr_ };
	  
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
  maths::Point3D  center_;
  //float radius_;
  float radius_sqr_;
};



int main(){
  std::vector<rgb_t> data;
  const int height = 600;
  const int width = 600;

  Sphere s1(maths::Point3D(300.0f, 300.0f, 0.0f), 300.0f);
  for(int j {0} ; j < height; ++j){
     for(int i {0} ; i < width; ++i){
       maths::Vector direction(0.0f , 0.0f, -1.0f);
	rgb_t c{0,0,0};
	if(s1.hit(maths::Ray((0.0f) + (float)i +  0.5f , 0.0f + (float)j + 0.5f, 900.0f ,
			     0.0f , 0.0f, -1.0f ))) {
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
