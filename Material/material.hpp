#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "includes.hpp"

class Material
{
public:
    virtual ~Material() = default;

    virtual  Colour shade(ShadeRec& sr) = 0;
};

#endif
