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
 * \file krt_geometry_object.h
 * \date 2019/01/05 16:53
 *
 * \author www.xionggf.com
 * Contact: sun_of_lover@sina.com
 *
 * \brief
 *
 * TODO: 几何体基类
 *
 * \note
*/
#ifndef krt_geometry_object_h__
#define krt_geometry_object_h__

#include "krt_tools_macro.h"
#include "krt_color_rgb.h"
#include "krt_material.h"

namespace krt
{
	class Ray;
	class ShadeHelper;
	class BoundingBox;

	class GeometricObject
	{
	public:

		/****************************************
		*  GeometricObject
		*  @return
		*  @see
		*  @note
		****************************************/
		GeometricObject();

		/****************************************
		*  GeometricObject
		*  @param   const GeometricObject & object
		*  @return
		*  @see
		*  @note
		****************************************/
		GeometricObject(const GeometricObject& object);

		virtual GeometricObject* clone(void) const = 0;

		virtual ~GeometricObject();

		/****************************************      
		*  hit 
		*  @param   const Ray & ray 
		*  @param   double & t 如果射线和本几何体相交，返回射线起点到相交点的距离值
		*  @param   ShadeHelper & s 
		*  @return  bool 相交返回true，否则返回false
		*  @see   
		*  @note  求得某射线ray和本几何体是否相交
		****************************************/
		virtual bool hit(const Ray& ray, double& t, ShadeHelper& s) const = 0;

		virtual void set_material(MaterialSPtr m);

		KRT_INLINE MaterialSPtr get_material() const
		{
			return material_;
		}

		KRT_INLINE void set_color(const RGBColor& c)
		{
			color = c;
		}

		KRT_INLINE void set_color(const float r, const float g, const float b)
		{
			color.red_ = r;
			color.blue_ = b;
			color.green_ = g;
		}

		KRT_INLINE RGBColor get_color()
		{
			return color;
		}

		/****************************************      
		*  set_bounding_box 
		*  @return  void
		*  @see   
		*  @note 设置生成本几何体的包围盒
		****************************************/
		virtual void set_bounding_box();

		/****************************************      
		*  get_bounding_box 
		*  @return  krt::BoundingBox
		*  @see   
		*  @note 获取本几何体的包围盒
		****************************************/
		virtual BoundingBox get_bounding_box();

		/****************************************      
		*  add_object 
		*  @param   GeometricObject * object_ptr 
		*  @return  void
		*  @see   
		*  @note 给本object添加一个新的几何体，构建成一个复合几何体对象
		****************************************/
		virtual void add_object(GeometricObject* object_ptr);

		virtual glm::vec3 sample();

		/****************************************      
		*  PDF 
		*  @param   ShadeHelper & sr 
		*  @return  float
		*  @see   
		*  @note  返回概率密度函数值（probability density function），用于区域光照明效果
		****************************************/
		virtual float PDF(ShadeHelper& sr);

		/****************************************      
		*  get_normal 
		*  @return  glm::vec3
		*  @see   
		*  @note 返回本几何体的法线，可以用来对三角形网格进行平滑着色
		****************************************/
		virtual glm::vec3 get_normal() const;

		/****************************************      
		*  get_normal 
		*  @param   const glm::vec3 & p 
		*  @return  glm::vec3
		*  @see   
		*  @note 返回某一点p上的法线
		****************************************/
		virtual glm::vec3 get_normal(const glm::vec3& p);

	protected:
		GeometricObject&	operator= (const GeometricObject& rhs);
	protected:
		MaterialSPtr		material_;   	// mutable allows the const functions Compound::hit, Instance::hit, and RegularGrid::hit to assign to material_ptr
		RGBColor   			color;				// only used for Bare Bones ray tracing
		bool				shadows;
	};
}

#endif // krt_geometry_object_h__