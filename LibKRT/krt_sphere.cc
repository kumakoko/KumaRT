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

    Sphere::Sphere(const glm::dvec3& _center, double _radius):SolidObject(_center),radius(_radius)
    {
        SetName("Sphere");
    }

    void Sphere::AppendAllIntersections(const glm::dvec3& vantage,const glm::dvec3& direction,IntersectionList& intersectionList) const
    {
        // Calculate the coefficients of the quadratic equation 
        //     au^2 + bu + c = 0.
        // Solving this equation gives us the value of u 
        // for any intersection points.
        // 求解得一元二次方程组的三个系数abc
        // 求出射线起点到球心的连线向量
        const glm::dvec3 displacement = vantage - Center();
        const double a = glm::length2(direction);//direction.MagnitudeSquared();
        const double b = 2.0 * glm::dot(direction, displacement); //2.0 * DotProduct(direction, displacement);
        const double c = glm::length2(displacement) - radius * radius;//displacement.MagnitudeSquared() - radius*radius;

        // Calculate the radicand of the quadratic equation solution formula.
        // The radicand must be non-negative for there to be real solutions.
        const double radicand = b*b - 4.0*a*c;
        if (radicand >= 0.0)
        {
            // There are two intersection solutions, one involving 
            // +sqrt(radicand), the other -sqrt(radicand).
            // Check both because there are weird special cases, 
            // like the camera being inside the sphere,
            // or the sphere being behind the camera (invisible).
            const double root = sqrt(radicand);
            const double denom = 2.0 * a;
            const double u[2] = {
                (-b + root) / denom,
                (-b - root) / denom
            };

            for (int i = 0; i < 2; ++i)
            {
                if (u[i] > EPSILON)
                {
                    Intersection intersection;
                    const glm::dvec3 vantageToSurface = u[i] * direction;
                    //intersection.point = vantage + vantageToSurface;
                    intersection.SetPoint(vantage + vantageToSurface);

                    // The normal vector to the surface of 
                    // a sphere is outward from the center.
                    //intersection.surfaceNormal =
                    //    (intersection.point - Center()).UnitVector();
                    intersection.SetSurfaceNormal(glm::normalize(intersection.GetPoint() - Center()));

                    /*
                    intersection.distanceSquared =
                        vantageToSurface.MagnitudeSquared();
                    */
                    intersection.SetDistanceSquared(glm::length2(vantageToSurface));

                    intersection.solid = this;
                    intersectionList.push_back(intersection);
                }
            }
        }
    }

    bool Sphere::Contains(const glm::dvec3& point) const
    {
        // Add a little bit to the actual radius to be more tolerant
        // of rounding errors that would incorrectly exclude a 
        // point that should be inside the sphere.
        const double r = radius + EPSILON;

        // A point is inside the sphere if the square of its distance 
        // from the center is within the square of the radius.
        return (point - Center()).MagnitudeSquared() <= (r * r);
    }

    // The nice thing about a sphere is that rotating 
    // it has no effect on its appearance!
    SolidObject& Sphere::RotateX(double angleInDegrees) { return *this; }
    SolidObject& Sphere::RotateY(double angleInDegrees) { return *this; }
    SolidObject& Sphere::RotateZ(double angleInDegrees) { return *this; }
};
}