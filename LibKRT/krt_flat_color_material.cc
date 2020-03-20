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
#include "krt_shade_helper.h"
#include "krt_flat_color_material.h"

namespace krt
{
    FlatColorMaterial::FlatColorMaterial(float r, float g, float b):Material("KRT-FlatColorMaterial")
	{
        color_.red_ = r;
        color_.green_ = g;
        color_.blue_ = b;
	}

    FlatColorMaterial::FlatColorMaterial(const char* name, float r, float g, float b):Material(name)
    {
        color_.red_ = r;
        color_.green_ = g;
        color_.blue_ = b;
    }

    FlatColorMaterial::FlatColorMaterial(const std::string& name, float r, float g, float b) : Material(name)
    {
        color_.red_ = r;
        color_.green_ = g;
        color_.blue_ = b;
    }

    FlatColorMaterial::FlatColorMaterial(FlatColorMaterial&& rhs)
    {
        color_ = rhs.color_;
    }

    FlatColorMaterial::FlatColorMaterial(const FlatColorMaterial& rhs)
	{
        color_ = rhs.color_;
	}

    FlatColorMaterial& FlatColorMaterial::operator= (const FlatColorMaterial& rhs)
	{
		if (this == &rhs)
			return *this;

		return *this;
	}

    FlatColorMaterial::~FlatColorMaterial()
	{
	}

	RGBColor FlatColorMaterial::shade(ShadeHelper& sr)
	{
        return color_;
	}

    std::shared_ptr<Object> FlatColorMaterial::Clone() const
    {
        return std::make_shared<FlatColorMaterial>(*this);
    }
}
