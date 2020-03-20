﻿/**************************************************************************************************************************
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
 * \file krt_material.h
 * \date 2018/12/26 17:29
 *
 * \author www.xionggf.com
 * Contact: sun_of_lover@sina.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/
#ifndef krt_flat_color_material_h__
#define krt_flat_color_material_h__

#include "krt_material.h"
#include "krt_color_rgb.h"

namespace krt
{
	class ShadeHelper;
	class RGBColor;

    class FlatColorMaterial: public Material
	{
	public:
        FlatColorMaterial(float r, float g, float b);

        FlatColorMaterial(const char* name,float r,float g,float b);

        FlatColorMaterial(const std::string& name, float r, float g, float b);

        FlatColorMaterial(const FlatColorMaterial& rhs);

        FlatColorMaterial(FlatColorMaterial&& rhs);

		virtual ~FlatColorMaterial();

		virtual RGBColor shade(ShadeHelper& sr);

        virtual std::shared_ptr<Object> Clone() const override;

        FlatColorMaterial& operator= (const FlatColorMaterial& rhs);
    private:
        RGBColor color_;
	};

	typedef std::shared_ptr<FlatColorMaterial> FlatColorMaterialSPtr;
}

#endif // krt_flat_color_material_h__

