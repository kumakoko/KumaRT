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
 * \brief 包围盒
*/
namespace krt
{
    class Ray;

    class BoundingBox
    {
    public:
        /*********************************************************
        缺省构造函数
        *********************************************************/
        BoundingBox();

        /*********************************************************
        构造函数
        @param double x0 包围盒左上角顶点坐标x
        @param double x1 包围盒左上角顶点坐标y
        @param double y0 包围盒左上角顶点坐标z
        @param double y1 包围盒右下角顶点坐标x
        @param double z0 包围盒右下角顶点坐标y
        @param double z1 包围盒右下角顶点坐标z
        *********************************************************/
        BoundingBox(double x0, double x1, double y0, double y1, double z0, double z1);

        /*********************************************************
        构造函数
        @param  const glm::dvec3 & p0 包围盒左上角顶点坐标
        @param  const glm::dvec3 & p1 包围盒右下角顶点坐标
        *********************************************************/
        BoundingBox(const glm::dvec3& p0, const glm::dvec3& p1);

        /*********************************************************
        拷贝构造函数
        @param  const BoundingBox & bbox 作为数据源的对象
        *********************************************************/
        BoundingBox(const BoundingBox& bbox);

        /*********************************************************
        移动构造函数
        @param  BoundingBox&& rhs 作为数据源的右值对象
        *********************************************************/
        BoundingBox(BoundingBox&& rhs);

        /*********************************************************
        重载赋值函数
        @param  const BoundingBox & rhs 作为数据源的对象
        *********************************************************/
        BoundingBox& operator = (const BoundingBox& rhs);

        /*********************************************************
        析构函数
        *********************************************************/
        ~BoundingBox();

        /****************************************
        *  Hit
        *  @param   const Ray & ray 用来检测的射线
        *  @return  bool 判断射线ray是否和本盒相交，是的话返回true，否返回false
        *  @see
        *  @note 判断射线ray是否和本盒相交
        ****************************************/
        bool Hit(const Ray& ray) const;

        /****************************************
        *  Inside
        *  @param   const glm::vec3 & p 待判断的点
        *  @return  bool 判断某点p是否在本盒内，是的话返回true，否返回false
        *  @see
        *  @note 判断某点p是否在本盒内
        ****************************************/
        bool Inside(const glm::vec3& p) const;
    public:
        /** * @brief 包围盒的左下角和右上角的坐标值  */
        double x0_, x1_, y0_, y1_, z0_, z1_; // 
    };
}