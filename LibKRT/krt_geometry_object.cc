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
#include "krt_material.h"
#include "krt_bounding_box.h"
#include "krt_geometry_object.h"

namespace krt
{
	GeometricObject::GeometricObject(): color(0.0f,0.0f,0.0f),
		                                material_(nullptr),
		                                shadows(true)
	{
	}

	GeometricObject::GeometricObject(const GeometricObject& object): color(object.color),
		                                                             shadows(object.shadows)
	{
		this->material_ = object.material_;
	}

	GeometricObject& GeometricObject::operator= (const GeometricObject& rhs) 
	{
		if (this == &rhs)
			return (*this);

		color = rhs.color;
		material_.reset();
		material_ = rhs.material_;
		shadows = rhs.shadows;
		return *this;
	}

	GeometricObject::~GeometricObject()
	{
		material_.reset();
	}

	void GeometricObject::add_object(GeometricObject* object_ptr)
	{
	}

	glm::vec3 GeometricObject::get_normal() const
	{
		return glm::vec3(0.0f);
	}

	void GeometricObject::set_material(MaterialSPtr mPtr)
	{
		material_ = mPtr;
	}

	glm::vec3 GeometricObject::get_normal(const glm::vec3& p) {
		return glm::vec3(0.0f);
	}

	void GeometricObject::set_bounding_box() 
	{
	}

	BoundingBox GeometricObject::get_bounding_box()
	{
		return BoundingBox();
	}

	glm::vec3 GeometricObject::sample()
	{
		return glm::vec3(0.0f);
	}

	float GeometricObject::PDF(ShadeHelper& sr)
	{
		return 0.0f;
	}
}