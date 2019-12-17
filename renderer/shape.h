#ifndef SHAPE_H
#define SHAPE_H
#include "ray.h"

class Shape
{
public:
    Shape();
    ~Shape();

    virtual float intersect(Ray *ray) = 0;

private:

};

Shape::Shape()
{
}

Shape::~Shape()
{
}

#endif
