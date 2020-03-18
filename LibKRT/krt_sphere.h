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

#include "krt_geometry_object.h"
#include "krt_shade_helper.h"
#include "krt_tools_macro.h"

namespace krt
{
    class Sphere : public GeometricObject 
    {
    public:
        /*********************************************************
        
        @return 
        @see function  
        @note           
        @attention      
        @bug            
        @warning        
        *********************************************************/
        Sphere(); 

        /*********************************************************
        
        @param  const glm::dvec3 & center
        @param  double r
        @return 
        @see function  
        @note           
        @attention      
        @bug            
        @warning        
        *********************************************************/
        Sphere(const glm::dvec3& center, double r);

        /*********************************************************
        
        @param  const Sphere & sphere
        @return 
        @see function  
        @note           
        @attention      
        @bug            
        @warning        
        *********************************************************/
        Sphere(const Sphere& sphere);

        /*********************************************************
        
        @param  Sphere & & sphere
        @return 
        @see function  
        @note           
        @attention      
        @bug            
        @warning        
        *********************************************************/
        Sphere(Sphere&& sphere);

        virtual GeometricObjectSPtr clone() const;

        virtual	~Sphere(void);

        Sphere& operator = (const Sphere& sphere);

        KRT_INLINE void Sphere::set_center(const glm::dvec3& c)
        {
            center_ = c;
        }

        KRT_INLINE void set_center(const double x, const double y, const double z)
        {
            center_.x = x;
            center_.y = y;
            center_.z = z;
        }

        KRT_INLINE void set_radius(const double r) 
        {
            radius_ = r;
        }

        virtual bool hit(const Ray& ray, double& t, ShadeHelper& s) const override;

    private:

        glm::dvec3 	center_;   			// center coordinates as a point  
        double 		radius_;				// the radius 

        static const double kEpsilon;   // for shadows and secondary rays
    };




}

#endif // krt_sphere_h__