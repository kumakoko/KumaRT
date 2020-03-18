/**************************************************************************************************************************
Copyright(C) 2014-2019 www.xionggf.com

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy,
modify, merge, publish, distribute,sublicense, and/or sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM,OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**************************************************************************************************************************/
#include "krt_lib_pch.h"
#include "krt_sphere.h"
#include "krt_math.h"
#include "krt_intersection.h"

namespace krt
{
    const double Sphere::kEpsilon = 0.001;

    Sphere::Sphere(): GeometricObject(),center_(0.0),radius_(1.0)
    {
    }

    Sphere::Sphere(const glm::dvec3& c, double r): GeometricObject(),center_(c),radius_(r)
    {
    
    }

    GeometricObjectSPtr Sphere::clone() const
    {
        return std::make_shared<Sphere>(*this);
    }

    Sphere::Sphere(const Sphere& sphere): 
        GeometricObject(sphere),center_(sphere.center_),radius_(sphere.radius_)
    {
    }

    Sphere::Sphere(Sphere&& sphere):
        GeometricObject(sphere),center_(sphere.center_),radius_(sphere.radius_)
    {
    }


    Sphere& Sphere::operator= (const Sphere& rhs)
    {
        if (this == &rhs)
            return (*this);

        center_ = rhs.center_;
        radius_ = rhs.radius_;
        this->color_ = rhs.color_;
        this->material_ = rhs.material_;
        this->shadows_ = rhs.shadows_;
        return *this;
    }

    Sphere::~Sphere(void)    
    {
    }

    bool Sphere::hit(const Ray& ray, double& tmin, ShadeHelper& sr) const
    {
        glm::dvec3	temp = ray.origin() - center_;
        double t = 0.0;
        double a = glm::dot(ray.direction(),ray.direction());
        double b = 2.0 * glm::dot(temp,ray.direction());
        double c = glm::dot(temp,temp) - radius_ * radius_;
        double disc = b * b - 4.0 * a * c;

        if (disc < 0.0)
        {
            return false;
        }
        else
        {
            double e = sqrt(disc);
            double denom = 2.0 * a;
            t = (-b - e) / denom;    // smaller root

            if (t > kEpsilon) 
            {
                tmin = t;
                sr.set_normal((temp + t * ray.direction()) / radius_);
                sr.set_local_hit_point(ray.origin() + t * ray.direction());
                return true;
            }

            t = (-b + e) / denom;    // larger root

            if (t > kEpsilon)
            {
                tmin = t;
                sr.set_normal((temp + t * ray.direction()) / radius_);
                sr.set_local_hit_point(ray.origin() + t * ray.direction());
                return true;
            }
        }

        return false;
    }
}