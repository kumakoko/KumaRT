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
/*!
 * \file krt_sphere.h
 * \date 2019/11/12 15:47
 *
 * \author www.xionggf.com
 * Contact: sun_of_lover
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

#ifndef krt_sphere_h__
#define krt_sphere_h__

#include "krt_solid_object.h"

namespace krt
{
    // A sphere that is more efficient than Spheroid with equal dimensions.
    class Sphere : public SolidObject
    {
    public:
        Sphere(const glm::dvec3& _center, double _radius);

        virtual void AppendAllIntersections(const glm::dvec3& vantage,const glm::dvec3& direction,IntersectionList& intersectionList) const override;

        virtual bool Contains(const glm::dvec3& point) const override;

        // The nice thing about a sphere is that rotating 
        // it has no effect on its appearance!
        virtual SolidObject& RotateX(double angleInDegrees) override;
        virtual SolidObject& RotateY(double angleInDegrees) override;
        virtual SolidObject& RotateZ(double angleInDegrees) override;

    private:
        double  radius;
    };
}

#endif // krt_sphere_h__