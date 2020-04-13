#include "Maths/maths.hpp"
#include <iostream>


int main(){

  maths::Point3D p1 (2.0f, 3.0f, 4.0f);
  std::cout<<p1.x() <<" "<<p1.y() << " " << p1.z() << std::endl;

    maths::Vector v1(2.0f, 3.0f, 4.0f);
    maths::Vector v2(5.0f, 6.0f, 7.0f);
    maths::Vector v3 = maths::Vector::cross(v1, v2);
    std::cout<< v3.x() <<" "<< v3.y() <<" " << v3.z() <<std::endl;
}

