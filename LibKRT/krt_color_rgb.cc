#include "krt_lib_pch.h"
#include "krt_color_rgb.h"

namespace krt
{
	RGBColor::RGBColor(): red_(0.0), green_(0.0), blue_(0.0)
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

	RGBColor& RGBColor::operator= (const RGBColor& rhs)
	{
		if (this == &rhs)
			return (*this);

		red_ = rhs.red_; green_ = rhs.green_; blue_ = rhs.blue_;

		return (*this);
	}

	RGBColor RGBColor::Powc(float p) const
	{
		return (RGBColor(powf(red_, p), powf(green_, p), powf(blue_, p)));
	}

}