#ifndef MATHS_HPP
#define MATHS_HPP

namespace maths
{

  class Point3D
  {
  private:
    float x_, y_, z_;

  public:
    Point3D();
    Point3D(float x, float y, float z);

    float x();
    float y();
    float z();

    void set_x(float x);
    void set_y(float y);
    void set_z(float z);

  };

  class Vector
  {
  private:
    float x_, y_, z_;
  public:
    Vector();
    Vector(float x, float y, float z);
    float x();
    float y();
    float z();

    void set_x(float x);
    void set_y(float y);
    void set_z(float z);
    
    void normalize();
    
    static float dot(const Vector &v1, const Vector &v2);
    static Vector cross(const Vector &v1, const Vector &v2);
  };
  /*
  class Ray : public Point3D, public Vector()
  {
  public:
    Point o;
    Vector d;
    
    Ray();
    Ray(Point3D o, Vector d);
    Ray(float ox, float oy, float oz, float dx, float dy, float dz;)

    
  };
  */
}

#endif