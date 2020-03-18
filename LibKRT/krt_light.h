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
 * \file krt_light.h
 * \date 2020/03/15 22:56
 *
 * \author www.xionggf.com
 * Contact: sun_of_lover@sina.com
 *
 * \brief 光源类的基类，作为多种光源的一个基类接口
*/

#ifndef krt_light_h__
#define krt_light_h__

#include "krt_color_rgb.h"
#include "krt_ray.h"
#include "krt_object.h"

namespace krt
{
    class ShadeHelper;

    class Light : public Object
    {
    public:
        /*********************************************************
        缺省构造函数      
        *********************************************************/
        Light();

        Light(const char* name);

        Light(const std::string& name);

        /*********************************************************
        拷贝构造函数
        @param const Light& ls 作为拷贝源的右值对象
        *********************************************************/
        Light(const Light& ls);

        /*********************************************************
        移动构造函数
        @param  Light&& ls 作为拷贝源的右值对象      
        *********************************************************/
        Light(Light&& ls);

        /*********************************************************
        重载赋值函数
        @param  const Light& rhs
        @return       
        *********************************************************/
        Light& operator= (const Light& rhs);

        /*********************************************************
        析构函数        
        *********************************************************/
        virtual ~Light();

        virtual glm::dvec3 get_direction(ShadeHelper& sr) = 0;

        virtual RGBColor L(ShadeHelper& sr);
    };

    typedef std::shared_ptr<Light> LightSPtr;
}

#endif // krt_light_h__