#pragma once

#include <atlas/math/Math.hpp>
#include <atlas/math/Ray.hpp>

#include <fmt/printf.h>
#include <stb_image.h>
#include <stb_image_write.h>

#include <vector>

#include <stdlib.h>
#include <iostream>

using namespace atlas;
using Colour = math::Vector;


void saveToBMP(std::string const& filename,
               std::size_t width,
               std::size_t height,
               std::vector<Colour> const& image);

struct ShadeRec {
	Colour colour;
	float t;
};

/* 
 * Virtual class for the geometric objects in the sence
 * TO DO: Fix it so that colour is stored here
 */


class Geometric_Obj {
public:
	virtual bool hit(atlas::math::Ray<atlas::math::Vector> const& ray, ShadeRec& trace_data) const = 0;

protected: 
};

class Sphere : public Geometric_Obj {
	/* class for a sphere
	*
	*/
public:
	 Sphere(atlas::math::Point center, float radius, Colour colour) :
		center_{ center },
		radius_{ radius },
		radius_sqr_{ radius * radius },
		colour_{ colour }
	{ }

	bool hit(atlas::math::Ray<atlas::math::Vector> const& ray, ShadeRec& trace_data) const 
	{
		auto o_c{ ray.o - center_ };
		auto a{ glm::dot(ray.d, ray.d) };
		auto b{ glm::dot(ray.d, o_c) * 2 };
		auto c{ glm::dot(o_c, o_c) - radius_sqr_ };
		auto roots{ b * b - (4.0f * a * c) };
		if (roots >= 0.0f) {
			//hit
			float t = ((-b - std::sqrt(roots)) / (2.0f * a));
			if (t > 0.0f) {
				trace_data.t = t;
				trace_data.colour = colour_;
				return true;
			}
			
		}
		return false;
	}

private:
	atlas::math::Point center_;
	float radius_;
	float radius_sqr_;
	Colour colour_;
};

class Plane : public Geometric_Obj {
public:
	 Plane(atlas::math::Point p, atlas::math::Vector n, Colour colour) :
		point_{ p },
		normal_{ n },
		colour_{ colour }
	{}


	bool hit(atlas::math::Ray<atlas::math::Vector> const& ray, ShadeRec& trace_data) const
	{
		float inter =  ( glm::dot(point_ - ray.o, normal_)) / glm::dot(ray.o , normal_) ;
		
		// if inter is zero then ray is parallel to the plane ;
		if( inter > 0.0f){
			//check if infront of screen
			//if (t > 0.0f) {
				trace_data.t = inter;
				trace_data.colour = colour_;
				return true;
			//}
		}
			return false;
	}

private:
	atlas::math::Point point_;
	atlas::math::Vector normal_;
	Colour colour_;
};

class Triangle : public Geometric_Obj{
public :
	Triangle(atlas::math::Point a, atlas::math::Point b, atlas::math::Point c, Colour colour) :
		a_{ a },
		b_{ b },
		c_{ c },
		colour_{colour}
	{
		atlas::math::Vector v1 = ( b_- a_);
		atlas::math::Vector v2 = (c_ - a_);
		normal = glm::cross(v1,v2) ;
	}

	bool hit(atlas::math::Ray<atlas::math::Vector> const& ray, ShadeRec& trace_data) const
	{

		float inter = (glm::dot(c_ - ray.o, normal)) / glm::dot(ray.o, normal);
		
		// compute hit point
		trace_data.t = ((glm::dot(a_ - ray.o, normal)) / glm::dot(normal, ray.d));
		atlas::math::Point q = ray.o + trace_data.t * ray.d;
		if ((inter * -1) > 0.0f) {
			if (glm::dot(glm::cross((b_ - a_), (q - a_)), normal) >= 0 &&
				glm::dot(glm::cross((c_ - b_), (q - b_)), normal) >= 0 &&
				glm::dot(glm::cross((a_ - c_), (q - c_)), normal) >= 0) {
				trace_data.colour = colour_;
				return true;
			}
		}
		

		return false;
	}

private:
	atlas::math::Point a_;
	atlas::math::Point b_;
	atlas::math::Point c_;
	atlas::math::Vector normal;
	Colour colour_;
};


/* 
 * Hold all of the objects of the scene 
 * hit_colour returns if the ray hit an object in the scene. Returns the colour of the closest object
 * TO DO: Fix it so that the colour returned - not great style and need to fix how the closest obj is found
 */

class World {
public:
	World() {}

	std::vector<Geometric_Obj*> objs;

	void add_obj(Geometric_Obj* obj) {
		objs.push_back(obj);
	}

	bool hit_colour(atlas::math::Ray<atlas::math::Vector> ray, ShadeRec& trace_data) const {
		bool hit = false;
		// ohh not great  :( not super sure how to do better
		float min_t = 999999;
		ShadeRec minShade;

		for (auto& obj : objs) {
			if (obj->hit(ray, minShade)) {
				if (minShade.t < min_t) {
					min_t = minShade.t;
					trace_data = minShade;
					hit = true;
				}
			}
		}
		return hit;
	}
};

/* 
 * Renders with one ray per pixel that is cented in the pixel
 */

void render (World& scene, atlas::math::Ray<atlas::math::Vector> ray,  std::size_t image_width, std::size_t image_height, std::vector<Colour>& image, Colour background)
{
	ShadeRec trace_data{};

	for (std::size_t y{ 0 }; y < image_height; ++y) {
		for (std::size_t x{ 0 }; x < image_width; ++x) {
			ray.o = { x + 0.5 , y + 0.5, 0 };

			image[x + y * image_height] = background;
			if (scene.hit_colour(ray, trace_data)) {
				image[x + y * image_height] = trace_data.colour;
			}

		}
	}

}


/* 
 * Renders the scene with random anti alisasing the caller must define how many samples per pixel they would like
 */
void render_aa(World& scene, atlas::math::Ray<atlas::math::Vector> in_ray, std::size_t image_width, std::size_t image_height, std::vector<Colour>& image, Colour background, int samples_pp) {
	ShadeRec trace_data{};


	for (std::size_t y{ 0 }; y < image_height; ++y) {
		for (std::size_t x{ 0 }; x < image_width; ++x) {
			Colour colour_avg{ 0,0,0 };
			srand(12345);
			for (int i{ 0 }; i < samples_pp; ++i) {

				in_ray.o = { x + ((float)rand() / (RAND_MAX))  , y + ((float)rand() / (RAND_MAX)), 0 };

				
				if (scene.hit_colour(in_ray, trace_data)) {
					colour_avg += trace_data.colour;
				}
				else {
					colour_avg += background;
				}
			
			}


			Colour div{ samples_pp, samples_pp, samples_pp };
			image[x + y * image_height] = colour_avg / div;
		}
	}
}
