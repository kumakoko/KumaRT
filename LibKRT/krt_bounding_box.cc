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
// 包围盒
#include "krt_lib_pch.h"
#include "krt_ray.h"
#include "krt_bounding_box.h"

namespace krt
{
	BoundingBox::BoundingBox() : x0_(-1.0), x1_(1.0), y0_(-1.0), y1_(1.0), z0_(-1.0), z1_(1.0)
	{
	}

	BoundingBox::BoundingBox(const double _x0, const double _x1,const double _y0, const double _y1,const double _z0, const double _z1)
		                     : x0_(_x0), x1_(_x1), y0_(_y0), y1_(_y1), z0_(_z0), z1_(_z1)
	{
	}

	BoundingBox::BoundingBox(const glm::vec3& p0, const glm::vec3& p1)
		: x0_(p0.x), x1_(p1.x), y0_(p0.y), y1_(p1.y), z0_(p0.z), z1_(p1.z)
	{
	}

	BoundingBox::BoundingBox(const BoundingBox& bbox): x0_(bbox.x0_), x1_(bbox.x1_), y0_(bbox.y0_),
		                                               y1_(bbox.y1_), z0_(bbox.z0_), z1_(bbox.z1_)
	{
	}

	BoundingBox& BoundingBox::operator= (const BoundingBox& rhs)
	{
		if (this == &rhs)
			return (*this);

		x0_ = rhs.x0_;
		x1_ = rhs.x1_;
		y0_ = rhs.y0_;
		y1_ = rhs.y1_;
		z0_ = rhs.z0_;
		z1_ = rhs.z1_;

		return *this;
	}

	BoundingBox::~BoundingBox() 
	{
	}

	/*求射线和长方体包围盒是否相交有多种方法，比如厚板法和分离轴法
	平板层相交法可参考此网页：
	https://blog.csdn.net/xuexiaokkk/article/details/50681438?utm_source=blogxgwz6
	分离轴算法可以参考此网页：
	https://blog.csdn.net/shlkl99/article/details/73648590
	*/
	bool BoundingBox::Hit(const Ray& ray) const 
	{
		double ox = ray.origin_.x; double oy = ray.origin_.y; double oz = ray.origin_.z;
		double dx = ray.dir_.x; double dy = ray.dir_.y; double dz = ray.dir_.z;

		double tx_min, ty_min, tz_min;
		double tx_max, ty_max, tz_max;

		double a = 1.0 / dx;

		if (a >= 0)
		{
			tx_min = (x0_ - ox) * a;
			tx_max = (x1_ - ox) * a;
		}
		else
		{
			tx_min = (x1_ - ox) * a;
			tx_max = (x0_ - ox) * a;
		}

		double b = 1.0 / dy;

		if (b >= 0) 
		{
			ty_min = (y0_ - oy) * b;
			ty_max = (y1_ - oy) * b;
		}
		else 
		{
			ty_min = (y1_ - oy) * b;
			ty_max = (y0_ - oy) * b;
		}

		double c = 1.0 / dz;
		if (c >= 0)
		{
			tz_min = (z0_ - oz) * c;
			tz_max = (z1_ - oz) * c;
		}
		else 
		{
			tz_min = (z1_ - oz) * c;
			tz_max = (z0_ - oz) * c;
		}

		double t0, t1;

		if (tx_min > ty_min)
			t0 = tx_min;
		else
			t0 = ty_min;

		if (tz_min > t0)
			t0 = tz_min;

		if (tx_max < ty_max)
			t1 = tx_max;
		else
			t1 = ty_max;

		if (tz_max < t1)
			t1 = tz_max;

		return (t0 < t1 && t1 > DBL_EPSILON);
	}

	bool BoundingBox::Inside(const glm::vec3& p) const
	{
		return ((p.x > x0_ && p.x < x1_) && (p.y > y0_ && p.y < y1_) && (p.z > z0_ && p.z < z1_));
	};
}