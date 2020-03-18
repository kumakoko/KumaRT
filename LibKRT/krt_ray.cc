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
#include "krt_ray.h"

namespace krt 
{
	Ray::Ray(): origin_(0.0),dir_(0.0, 0.0, 1.0)
	{
	}

	Ray::Ray(const glm::dvec3& origin, const glm::dvec3& dir): origin_(origin),dir_(dir)
	{
	}

	Ray::Ray(const Ray& ray): origin_(ray.origin()),dir_(ray.direction())
	{
	}

    Ray::Ray(Ray&& rhs)
    {
        this->set_origin(rhs.origin());
        this->set_direction(rhs.direction());
    }

	Ray& Ray::operator= (const Ray& rhs)
	{
		if (this == &rhs)
			return (*this);

		this->set_origin(rhs.origin());
		this->set_direction(rhs.direction());
		return (*this);
	}

	Ray::~Ray() 
	{

	}

    glm::dvec3 Ray::GetTargetPoint(double intercept) const
    {
        return glm::dvec3(this->origin() + intercept * this->direction());
    }
}