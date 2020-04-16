#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "includes.hpp"

class Material
{
public:
    virtual ~Material() = default;

    virtual  rgb_t shade(ShadeRec& sr) = 0;
};

#endif
