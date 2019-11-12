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
 * \file krt_math.h
 * \date 2019/11/12 15:24
 *
 * \author www.xionggf.com
 * Contact: sun_of_lover@sina.com
 *
 * \brief 数学相关的库文件
 *
 * TODO: long description
 *
 * \note
*/
#ifndef krt_math_h__
#define krt_math_h__

namespace krt
{
    const double PI = 3.141592653589793238462643383279502884;

    // EPSILON is a tolerance value for floating point roundoff error.
    // It is used in many calculations where we want to err
    // on a certain side of a threshold, such as determining
    // whether or not a point is inside a solid or not,
    // or whether a point is at least a minimum distance
    // away from another point.
    const double EPSILON = 1.0e-6;

    inline double RadiansFromDegrees(double degrees)
    {
        return degrees * (PI / 180.0);
    }
}

#endif // krt_math_h__
