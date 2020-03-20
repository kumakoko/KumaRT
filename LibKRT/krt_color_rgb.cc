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

#include "krt_lib_pch.h"
#include "krt_color_rgb.h"

namespace krt
{
	RGBColor::RGBColor(): red_(0.0f), green_(0.0f), blue_(0.0f)
	{
	}

	RGBColor::RGBColor(float c): red_(c), green_(c), blue_(c)
	{
	}

	RGBColor::RGBColor(float r, float g, float b): red_(r), green_(g), blue_(b)
	{
	}

	RGBColor::RGBColor(const RGBColor& c): red_(c.red_), green_(c.green_), blue_(c.blue_)
	{
	}

	RGBColor::~RGBColor()
	{
	}

    RGBColor::RGBColor(RGBColor&& c)
    {
        red_ = c.red_;
        green_ = c.green_;
        blue_ = c.blue_;
    }

	RGBColor& RGBColor::operator= (const RGBColor& rhs)
	{
		if (this == &rhs)
			return *this;

		red_ = rhs.red_;
        green_ = rhs.green_;
        blue_ = rhs.blue_;

		return *this;
	}

	RGBColor RGBColor::Powc(float p) const
	{
		return (RGBColor(powf(red_, p), powf(green_, p), powf(blue_, p)));
	}
}