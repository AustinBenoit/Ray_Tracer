#include <iostream>
#include "BMP/bitmap_image.hpp"
#include <boost/version.hpp>
#include <iomanip>

void save_to_bmp(std::string image_name, int height, int width, std::vector<rgb_t>& data){

bitmap_image image(width,height);

   for(unsigned int j = 0 ; j < image.height(); ++j){
     for(unsigned int i {0} ; i < image.width(); ++i){
       
       image.set_pixel(i , j , data[ i + j * image.height() ] );
     }
   }

   image.save_image(image_name);
}


int main()
{

    std::cout << "Boost version: " 
          << BOOST_VERSION / 100000
          << "."
          << BOOST_VERSION / 100 % 1000
          << "."
          << BOOST_VERSION % 100 
          << std::endl;
    return 0;

  /*
 std::vector<rgb_t> data;

  for(int j {0} ; j < 100; ++j){
     for(int i {0} ; i < 200; ++i){
       rgb_t c = make_colour(0,0,255);
       data.push_back(c);
     }
   }


  
  save_to_bmp("output.bmp", 100, 200, data);
   
   return 0;
 std::cout<<"Hello World!\n";
  */

}

