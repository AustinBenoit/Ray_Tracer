#include "objects.hpp"

int main()
{
    // the geometric objects
     Sphere s1{ {480,  400, 10}, 10, {1,.5,0} };
     Sphere s2{ {40,  80, 100}, 20, {.2,.8,.6} };
     Sphere s3{ {80,  160, 100}, 30, {.5,.4,.3} };
     Sphere s4{ {300,  300, 100}, 50, {.5,1,1} };
     Sphere s5{ {150,  450, 200}, 100, {0,1,1} };
     Sphere s6{ {480,  450, 200}, 112, {.1,.77,.55} };

     Plane p1{ {30,30,30}, {1,1,1}, {1,0,0} };
     Plane p2{ {570,30,30}, {0,1,1}, {0,0,1} };
	
     Triangle t1{ { 300,20,10 }, { 150,300, 10 }, { 450, 300, 10 }, { 1,1,1 } };


     
     // Holds everything and checks if a ray hits an object
     World scene{};
     scene.add_obj(&t1); 
     scene.add_obj(&s1);
     scene.add_obj(&s2);
     scene.add_obj(&s3);
     scene.add_obj(&s4);
     scene.add_obj(&s5);
     scene.add_obj(&s6);
     scene.add_obj(&p1);
     scene.add_obj(&p2);                                    

     constexpr std::size_t image_width{ 600 };
     constexpr std::size_t image_height{ 600 };
     constexpr Colour background{ 0,0,0 };

     atlas::math::Ray<atlas::math::Vector> ray{ {0,0,0}, {0,0,1} };
     std::vector<Colour> image{ image_height * image_width };
  
     render(scene, ray, image_width, image_height, image, background);


    saveToBMP("H:/Documents/CSC_305/Assignments/A1/out.bmp", image_width, image_height, image);

    render_aa(scene, ray, image_width, image_height, image, background, 100);
    saveToBMP("H:/Documents/CSC_305/Assignments/A1/out_aa.bmp", image_width, image_height, image);

    return 0;
}

/**
 * Saves a BMP image file based on the given array of pixels. All pixel values
 * have to be in the range [0, 1].
 *
 * @param filename The name of the file to save to.
 * @param width The width of the image.
 * @param height The height of the image.
 * @param image The array of pixels representing the image.
 */
void saveToBMP(std::string const& filename,
               std::size_t width,
               std::size_t height,
               std::vector<Colour> const& image)
{
    std::vector<unsigned char> data(image.size() * 3);

    for (std::size_t i{0}, k{0}; i < image.size(); ++i, k += 3)
    {
        Colour pixel = image[i];
        data[k + 0]  = static_cast<unsigned char>(pixel.r * 255);
        data[k + 1]  = static_cast<unsigned char>(pixel.g * 255);
        data[k + 2]  = static_cast<unsigned char>(pixel.b * 255);
    }

    stbi_write_bmp(filename.c_str(),
                   static_cast<int>(width),
                   static_cast<int>(height),
                   3,
                   data.data());
}
