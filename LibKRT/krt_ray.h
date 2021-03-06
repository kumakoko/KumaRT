﻿/**************************************************************************************************************************
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
 * \file krt_ray.h
 * \date 2018/12/26 13:35
 *
 * \author www.xionggf.com
 * Contact: sun_of_lover@sina.com
 *
 * \brief 
 *
 * TODO: 射线类
 *
 * \note 
*/
#ifndef krt_ray_h__
#define krt_ray_h__

#include "krt_tools_macro.h"

namespace krt
{
	class Ray 
	{
	public:
        KRT_INLINE const glm::dvec3& origin() const
        {
            return origin_;
        }

        KRT_INLINE glm::dvec3 origin()
        {
            return origin_;
        }

        KRT_INLINE void set_origin(glm::dvec3 val)
        {
            origin_ = val;
        }
        
        KRT_INLINE const glm::dvec3& direction() const 
        {
            return dir_; 
        }

        KRT_INLINE glm::dvec3 direction()
        {
            return dir_;
        }
        
        KRT_INLINE void set_direction(glm::dvec3 val)
        {
            dir_ = val; 
        }

        Ray();
		
        Ray(const glm::dvec3& o, const glm::dvec3& d);
		
        Ray(const Ray& ray);

        /*********************************************************
        移动构造函数，用以使用一个右值变量来构造本对象
        @param  Ray&& ray 一个右值变量
        *********************************************************/
        Ray(Ray&& ray);

        Ray& operator= (const Ray& rhs);

        ~Ray();
   
        /*********************************************************
        給定一個截距值，從origin點起，沿著dir方向，得到目標點坐標
        @param  double intercept 截距值
        @return 目標點坐標      
        *********************************************************/
        glm::dvec3 GetTargetPoint(double intercept) const;

    private:
        glm::dvec3	origin_;  	// 起点坐标 
        glm::dvec3	dir_; 		// 射线的发射方向 
    };
}

#endif // krt_ray_h__


