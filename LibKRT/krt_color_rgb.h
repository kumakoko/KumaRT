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
 * \file krt_color_rgb.h
 * \date 2018/12/26 16:34
 *
 * \author www.xionggf.com
 * Contact: sun_of_lover@sina.com
 *
 * \brief
 *
 * TODO: 颜色类
 *
 * \note
*/
#ifndef krt_color_rgb_h__
#define krt_color_rgb_h__

#include "krt_tools_macro.h"

namespace krt
{
    class RGBColor
    {
    public:
        float   red_, green_, blue_;
    public:
        RGBColor();                                     // default constructor
        RGBColor(float c);                                  // constructor
        RGBColor(float r, float g, float b);                // constructor
        RGBColor(const RGBColor& c);                        // copy constructor
        ~RGBColor();                                    // destructor

        RGBColor& operator= (const RGBColor& rhs);

        KRT_INLINE RGBColor operator+ (const RGBColor& c) const
        {
            return (RGBColor(red_ + c.red_, green_ + c.green_, blue_ + c.blue_));
        }

        KRT_INLINE RGBColor& operator+= (const RGBColor& c)
        {
            red_ += c.red_; green_ += c.green_; blue_ += c.blue_;
            return (*this);
        }

        KRT_INLINE RGBColor operator* (const float a) const
        {
            return (RGBColor(red_ * a, green_ * a, blue_ * a));
        }

        KRT_INLINE RGBColor& operator*= (const float a)
        {
            red_ *= a; green_ *= a; blue_ *= a;
            return (*this);
        }

        KRT_INLINE RGBColor operator/ (const float a) const
        {
            return (RGBColor(red_ / a, green_ / a, blue_ / a));
        }

        KRT_INLINE RGBColor& operator/= (const float a)
        {
            red_ /= a; green_ /= a; blue_ /= a;
            return (*this);
        }

        KRT_INLINE RGBColor operator* (const RGBColor& c) const
        {
            return (RGBColor(red_ * c.red_, green_ * c.green_, blue_ * c.blue_));
        }

        KRT_INLINE bool operator== (const RGBColor& c) const
        {
            return (red_ == c.red_ && green_ == c.green_ && blue_ == c.blue_);
        }

        /****************************************
        *  Average
        *  @return  KRT_INLINE float
        *  @see
        *  @note 将各颜色分量相加后除以3，返回
        ****************************************/
        KRT_INLINE float Average() const
        {
            return (red_ + green_ + blue_) / 3.0f;
        }

        /****************************************
        *  Powc
        *  @param   float p
        *  @return  krt::RGBColor
        *  @see
        *  @note 将各颜色分量进行一次幂运算操作，指数为p
        ****************************************/
        RGBColor Powc(float p) const;
    };

    KRT_INLINE RGBColor operator* (const float a, const RGBColor& c)
    {
        return (RGBColor(a * c.red_, a * c.green_, a * c.blue_));
    }
}

#endif // krt_color_rgb_h__