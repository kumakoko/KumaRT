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

	Ray::Ray(const Ray& ray): origin_(ray.origin_),dir_(ray.dir_)
	{
	}

	Ray& Ray::operator= (const Ray& rhs)
	{
		if (this == &rhs)
			return (*this);

		this->origin_ = rhs.origin_;
		this->dir_ = rhs.dir_;
		return (*this);
	}

	Ray::~Ray() 
	{
	}
}