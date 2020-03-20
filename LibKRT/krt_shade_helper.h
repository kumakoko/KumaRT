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
 * \file krt_shade_helper.h
 * \date 2018/12/26 17:19
 *
 * \author www.xionggf.com
 * Contact: sun_of_lover@sina.com
 *
 * \brief 
 *
 * TODO: 存储光线跟踪器所需的信息，并且对光线-物体相交点进行着色操作
 *
 * \note
*/
#ifndef krt_shade_helper_h__
#define krt_shade_helper_h__

#include "krt_color_rgb.h"
#include "krt_ray.h"
#include "krt_tools_macro.h"

namespace krt
{
    class Material;
    class World;

	class ShadeHelper
	{
	public:
        ShadeHelper();

		ShadeHelper(bool hit_an_object,const RGBColor& rgb,const glm::dvec3& hit_point, const glm::dvec3& local_hit_point,
            const glm::dvec3& normal,const Ray& ray, int depth,float ray_parameter,std::shared_ptr<World> w, std::shared_ptr<Material> material);

        ShadeHelper(ShadeHelper&& rhs);

        ShadeHelper(const ShadeHelper& rhs);

		~ShadeHelper();

        KRT_INLINE bool hit_an_object() const
        {
            return hit_an_object_;
        }
        
        KRT_INLINE void set_hit_an_object(bool val)
        {
            hit_an_object_ = val;
        }
        
        KRT_INLINE krt::RGBColor color() const
        {
            return color_;
        }
        
        KRT_INLINE void set_color(krt::RGBColor val)
        { 
            color_ = val;
        }
        
        KRT_INLINE glm::dvec3 hit_point() const
        { 
            return hit_point_;
        }
        
        KRT_INLINE void set_hit_point(glm::dvec3 val)
        {
            hit_point_ = val; 
        }
        
        KRT_INLINE glm::dvec3 local_hit_point() const
        { 
            return local_hit_point_;
        }
        
        KRT_INLINE void set_local_hit_point(glm::dvec3 val)
        { 
            local_hit_point_ = val;
        }
        
        KRT_INLINE glm::dvec3 normal() const
        {
            return normal_;
        }
        
        KRT_INLINE void set_normal(glm::dvec3 val)
        {
            normal_ = val;
        }
        
        KRT_INLINE krt::Ray ray() const
        {
            return ray_; 
        }
        
        KRT_INLINE void set_ray(krt::Ray val)
        { 
            ray_ = val; 
        }
        
        KRT_INLINE int depth() const
        { 
            return depth_;
        }
        
        KRT_INLINE void set_depth(int val)
        { 
            depth_ = val;
        }
        
        KRT_INLINE double ray_parameter() const
        { 
            return ray_parameter_;
        }
        
        KRT_INLINE void set_ray_parameter(double val)
        { 
            ray_parameter_ = val;
        }
        
        KRT_INLINE std::shared_ptr<krt::World> world() const
        { 
            return world_; 
        }
        
        KRT_INLINE void set_world(std::shared_ptr<krt::World> val)
        { 
            world_ = val; 
        }
        
        KRT_INLINE std::shared_ptr<krt::Material> material() const
        {
            return material_;
        }
        
        KRT_INLINE void set_material(std::shared_ptr<krt::Material> val)
        {
            material_ = val;
        }
    private:
        bool hit_an_object_;		// Did the ray hit an object?  
        RGBColor color_;
        glm::dvec3  hit_point_;			// World coordinates of intersection
        glm::dvec3  local_hit_point_;	// World coordinates of hit point on generic object (used for texture transformations)
        glm::dvec3  normal_;				// Normal at hit point
        Ray ray_;				// Required for specular highlights and area lights
        int depth_;				// recursion depth
        double ray_parameter_;					// ray parameter
        std::shared_ptr<World>  world_;					// World reference
        std::shared_ptr<Material> material_;		// Pointer to the nearest object's material      
	};
}

#endif // krt_shade_helper_h__

