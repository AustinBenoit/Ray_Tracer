#ifndef GEOMETRIC_OBJECT_H
#define GEOMETRIC_OBJECT_H

class GeometricObj {
public:
    virtual bool hit(atlas::math::Ray<atlas::math::Vector> const& ray, ShadeRec& trace_data) const = 0;

    void setColour(Colour const& col) {
            colour_ = col;
    }

    Colour getColour() const 
    {
            return colour_;
    }


    void setMaterial(std::shared_ptr<Material> const& material) {
        material_ = material;
    }

    std::shared_ptr<Material> getMaterial() const {
        return material_;
    }

    //virtual bool shadow_hit(atlas::math::Ray<atlas::math::Vector> const& ray, float& tmin) = 0;


protected:
    Colour colour_;
    std::shared_ptr<Material> material_;
};




#endif
