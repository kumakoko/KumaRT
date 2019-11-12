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
 * \file krt_bounding_box.h
 * \date 2019/01/05 17:38
 *
 * \author www.xionggf.com
 * Contact: sun_of_lover@sina.com
 *
 * \brief 
 *
 * TODO: 包围盒
 *
 * \note
*/
namespace krt
{
	class Ray;

	class BoundingBox 
	{
	public:
		
		double x0_, x1_, y0_, y1_, z0_, z1_; // 包围盒的左下角和右上角的坐标值

		BoundingBox();

		BoundingBox(const double x0, const double x1,const double y0, const double y1,const double z0, const double z1);

		BoundingBox(const glm::vec3& p0, const glm::vec3& p1);

		BoundingBox(const BoundingBox& bbox);

		BoundingBox& operator= (const BoundingBox& rhs);

		~BoundingBox();

		/****************************************      
		*  Hit 
		*  @param   const Ray & ray 
		*  @return  bool 判断射线ray是否和本盒相交，是的话返回true，否返回false
		*  @see   
		*  @note 判断射线ray是否和本盒相交
		****************************************/
		bool Hit(const Ray& ray) const;

		/****************************************      
		*  Inside 
		*  @param   const glm::vec3 & p 
		*  @return  bool 判断某点p是否在本盒内，是的话返回true，否返回false
		*  @see   
		*  @note 判断某点p是否在本盒内
		****************************************/
		bool Inside(const glm::vec3& p) const;
	};
}