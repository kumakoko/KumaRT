#include "krt_lib_pch.h"
#include "krt_plane.h"

namespace krt
{
    const double Plane::kEpsilon = 0.001;

    Plane::Plane(void) : GeometricObject(), point_(0.0), normal_(0, 1, 0)
    {
    }

    Plane::Plane(const glm::dvec3& point, const glm::dvec3& normal) :
        GeometricObject(), point_(point), normal_(normal)
    {
        normal_ = glm::normalize(normal_); // normal_.normalize();
    }

    Plane::Plane(Plane&& rhs):GeometricObject(rhs)
    {
        this->point_ = rhs.point_;
        this->normal_ = rhs.normal_;
    }

    Plane::Plane(const Plane& plane) :
        GeometricObject(plane), point_(plane.point_), normal_(plane.normal_)
    {
    }

    GeometricObjectSPtr Plane::clone() const
    {
        return std::make_shared<Plane>(this->point_, this->normal_);
    }

    Plane& Plane::operator = (const Plane& rhs)
    {
        if (this == &rhs)
            return *this;

        point_ = rhs.point_;
        normal_ = rhs.normal_;
        material_ = rhs.material_;
        color_ = rhs.color_;
        shadows_ = rhs.shadows_;
        return *this;
    }

    Plane::~Plane(void)
    {
    }

    bool Plane::hit(const Ray& ray, double& tmin, ShadeHelper& sr) const
    {
        // float t = (a - ray.o) * n / (ray.d * n);
        // 计算出射线和平面的交点
        double t = glm::dot((point_ - ray.origin()), normal_) / glm::dot(ray.direction(), normal_);

        if (t > kEpsilon)
        {
            tmin = t;
            sr.set_normal(normal_);
            sr.set_local_hit_point(ray.origin() + t * ray.direction());
            return true;
        }

        return false;
    }

}