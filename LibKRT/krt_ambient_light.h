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
 * \file krt_ambient_light.h
 * \date 2020/03/17 13:16
 *
 * \author www.xionggf.com
 * Contact: sun_of_lover@sina.com
 *
 * \brief 
 *
 * TODO: 
 *
 * \note
*/
#ifndef krt_ambient_light_h__
#define krt_ambient_light_h__

#include "krt_light.h"
#include "krt_shade_helper.h"
#include "krt_tools_macro.h"

namespace krt
{
    class AmbientLight : public Light
    {
    public:
        AmbientLight();

        AmbientLight(const char* name);

        AmbientLight(const std::string& name);

        AmbientLight(const char* name, float d,const RGBColor& color);

        AmbientLight(const std::string& name, float d, const RGBColor& color);

        /*********************************************************
        拷贝构造函数
        @param  const AmbientLight& a  作为拷贝源的右值对象      
        *********************************************************/
        AmbientLight(const AmbientLight& a);

        /*********************************************************
        移动构造函数
        @param  AmbientLight&& a 作为拷贝源的右值对象       
        *********************************************************/
        AmbientLight(AmbientLight&& a);

        virtual std::shared_ptr<Object> Clone() const override;

        AmbientLight& operator= (const AmbientLight& rhs);

        virtual ~AmbientLight(void);

        KRT_INLINE void scale_radiance(const float b)
        {
            ls = b;
        }

        KRT_INLINE void set_color(const float c)
        {
            color_.red_ = c; color_.green_ = c; color_.blue_ = c;
        }

        KRT_INLINE void set_color(const RGBColor& c)
        {
            color_ = c;
        }

        KRT_INLINE void set_color(const float r, const float g, const float b)
        {
            color_.red_ = r; 
            color_.green_ = g;
            color_.blue_ = b;
        }

        virtual glm::dvec3 get_direction(ShadeHelper& s);

        virtual RGBColor L(ShadeHelper& s);

    private:
        float		ls;
        RGBColor	color_;
    };




}
#endif // krt_ambient_light_h__