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
 * \file krt_plane.h
 * \date 2020/03/17 16:15
 *
 * \author www.xionggf.com
 * Contact: sun_of_lover@sina.com
 *
 * \brief 表征一个平面的类。使用点法式描述
*/
#ifndef krt_plane_h__
#define krt_plane_h__

#include "krt_geometry_object.h"
#include "krt_shade_helper.h"

namespace krt
{
    class Plane : public GeometricObject
    {
    public:
        Plane();

        Plane(const glm::dvec3& point, const glm::dvec3& normal);

        Plane(const Plane& plane);

        Plane(Plane&& rhs);

        virtual GeometricObjectSPtr clone() const override;

        Plane& operator= (const Plane& rhs);

        virtual ~Plane();

        virtual bool hit(const Ray& ray, double& tmin, ShadeHelper& sr) const;

    private:
        glm::dvec3 point_;   				// point through which plane passes 
        glm::dvec3 normal_;					// normal to the plane
        static const double kEpsilon;   // for shadows and secondary rays
    };

    typedef std::shared_ptr<Plane> PlaneSPtr;
}

#endif // krt_plane_h__
