#include "krt_lib_pch.h"
#include "krt_camera.h"

namespace krt
{
    Camera::Camera() :
        exposure_time_(1.0), roll_angle_(0), eye_(0, 0, 500), lookat_(0), up_(0, 1, 0),
        basis_vector_u_(1, 0, 0), basis_vector_v_(0, 1, 0), basis_vector_w_(0, 0, 1)
    {
    }

    Camera::Camera(const char* name) :Object(name), exposure_time_(1.0), roll_angle_(0), eye_(0, 0, 500), 
        lookat_(0), up_(0, 1, 0),basis_vector_u_(1, 0, 0), basis_vector_v_(0, 1, 0),basis_vector_w_(0, 0, 1)
    {
    }

    Camera::Camera(const std::string& name) : Object(name), exposure_time_(1.0), roll_angle_(0), eye_(0, 0, 500),
        lookat_(0), up_(0, 1, 0), basis_vector_u_(1, 0, 0), basis_vector_v_(0, 1, 0), basis_vector_w_(0, 0, 1)
    {
    }


    Camera::Camera(const Camera& c)
        : eye_(c.eye_),
        lookat_(c.lookat_),
        roll_angle_(c.roll_angle_),
        up_(c.up_),
        basis_vector_u_(c.basis_vector_u_),
        basis_vector_v_(c.basis_vector_v_),
        basis_vector_w_(c.basis_vector_w_),
        exposure_time_(c.exposure_time_)
    {}

    Camera::Camera(Camera&& rhs)
    {
        name_ = rhs.name_;
        eye_ = rhs.eye_;
        lookat_ = rhs.lookat_;
        roll_angle_ = rhs.roll_angle_;
        up_ = rhs.up_;
        basis_vector_u_ = rhs.basis_vector_u_;
        basis_vector_v_ = rhs.basis_vector_v_;
        basis_vector_w_ = rhs.basis_vector_w_;
        exposure_time_ = rhs.exposure_time_;
        rhs.name_.clear();
    }

    Camera& Camera::operator= (const Camera& rhs) 
    {
        if (this == &rhs)
            return *this;

        name_ = rhs.name_;
        eye_ = rhs.eye_;
        lookat_ = rhs.lookat_;
        roll_angle_ = rhs.roll_angle_;
        up_ = rhs.up_;
        basis_vector_u_ = rhs.basis_vector_u_;
        basis_vector_v_ = rhs.basis_vector_v_;
        basis_vector_w_ = rhs.basis_vector_w_;
        exposure_time_ = rhs.exposure_time_;
        return *this;
    }

    Camera::~Camera()
    {
    }


    // This computes an orthornormal basis given the view point, lookat point, and up vector

    void Camera::compute_uvw(void)
    {
        basis_vector_w_ = glm::normalize(eye_ - lookat_);// w.normalize();
        basis_vector_u_ = glm::normalize(glm::cross(up_, basis_vector_w_));//u = up ^ w; u.normalize();
        basis_vector_v_ = glm::normalize(glm::cross(basis_vector_w_, basis_vector_u_));//v = w ^ u;

        // take care of the singularity by hardwiring in specific camera orientations

        if (eye_.x == lookat_.x && eye_.z == lookat_.z && eye_.y > lookat_.y)
        { // camera looking vertically down
            basis_vector_u_ = glm::dvec3(0, 0, 1);
            basis_vector_v_ = glm::dvec3(1, 0, 0);
            basis_vector_w_ = glm::dvec3(0, 1, 0);
        }

        if (eye_.x == lookat_.x && eye_.z == lookat_.z && eye_.y < lookat_.y)
        { // camera looking vertically up
            basis_vector_u_ = glm::dvec3(1, 0, 0);
            basis_vector_v_ = glm::dvec3(0, 0, 1);
            basis_vector_w_ = glm::dvec3(0, -1, 0);
        }
    }
}