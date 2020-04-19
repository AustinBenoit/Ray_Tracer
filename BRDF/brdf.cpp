#include "brdf.hpp"
#include "includes.hpp"

Colour PerfectSpecular::fn([[maybe_unused]] ShadeRec const& sr,
			   [[maybe_unused]] maths::Vector const& reflected,
			   [[maybe_unused]] maths::Vector const& incoming) const {
  return { 0,0,0 };
}

Colour PerfectSpecular::rho([[maybe_unused]] ShadeRec const& sr,
			    [[maybe_unused]] maths::Vector const& reflected) const {
  return{ 0,0,0 };
}

Colour PerfectSpecular::sample_f(ShadeRec const& sr,
				 maths::Vector const& wo,
				 maths::Vector& wi) const { 
  float ndotwo = maths::Vector::Dot(sr.normal, wo);
  wi = -1.0f * wo + 2.0f * sr.normal * ndotwo;
  return((specular_colour_ * specular_reflection_  / (maths::Vector::Dot(sr.normal, wi))));
}

Colour Lambertian::fn([[maybe_unused]] ShadeRec const& sr,
		      [[maybe_unused]] maths::Vector const& reflected,
		      [[maybe_unused]] maths::Vector const& incoming) const
{
  return diffuse_colour_ * diffuse_reflection_ * ( 1.0f / PI_F);
}

Colour Lambertian::rho([[maybe_unused]] ShadeRec const& sr,
		       [[maybe_unused]] maths::Vector const& reflected) const
{
  return diffuse_colour_ * diffuse_reflection_;
}


Colour GlossySpecular::fn([[maybe_unused]] ShadeRec const& sr,
        [[maybe_unused]] maths::Vector const& reflected,
        [[maybe_unused]] maths::Vector const& incoming) const
    {
        Colour l{ 0,0,0 };
        float ndotinc = maths::Vector::Dot(sr.normal, incoming);
        maths::Vector r { -1.0f * incoming + 2.0f * sr.normal * ndotinc };
        float rdotout = maths::Vector::Dot(r, reflected);
        if (rdotout > 0.0f) {
            l = specular_reflection_ * std::pow(rdotout, exps_) * specular_colour_;
        }
        return l;
    }

Colour GlossySpecular::rho([[maybe_unused]] ShadeRec const& sr,
        [[maybe_unused]] maths::Vector const& reflected) const
    {
        return { 0,0,0 };
    }
