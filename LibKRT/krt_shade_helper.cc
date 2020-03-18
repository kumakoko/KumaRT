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
#include "krt_world.h"
#include "krt_material.h"
#include "krt_shade_helper.h"


namespace krt
{
    ShadeHelper::ShadeHelper()
    {
    }

    ShadeHelper::ShadeHelper(bool hit_an_object, const RGBColor& rgb, const glm::dvec3& hit_point, const glm::dvec3& local_hit_point,
        const glm::dvec3& normal, const Ray& ray, int depth, float ray_parameter, std::shared_ptr<World> w, std::shared_ptr<Material> material) :
        hit_an_object_(hit_an_object), color_(rgb), hit_point_(hit_point), local_hit_point_(local_hit_point), normal_(normal), ray_(ray), depth_(depth),
        ray_parameter_(ray_parameter), world_(w), material_(material)
    {
    }

    ShadeHelper::ShadeHelper(ShadeHelper&& rhs)
    {
        this->hit_an_object_ = rhs.hit_an_object_;
        this->color_ = rhs.color_;
        this->hit_point_ = rhs.hit_point_;
        this->local_hit_point_ = rhs.local_hit_point_;
        this->normal_ = rhs.normal_;
        this->ray_ = rhs.ray_;
        this->depth_ = rhs.depth_;
        this->ray_parameter_ = rhs.ray_parameter_;
        this->world_ = rhs.world_;
        this->material_ = rhs.material_;
        rhs.world_.reset();
        rhs.material_.reset();
    }

    ShadeHelper::ShadeHelper(const ShadeHelper& rhs)
    {
        this->hit_an_object_ = rhs.hit_an_object_;
        this->color_ = rhs.color_;
        this->hit_point_ = rhs.hit_point_;
        this->local_hit_point_ = rhs.local_hit_point_;
        this->normal_ = rhs.normal_;
        this->ray_ = rhs.ray_;
        this->depth_ = rhs.depth_;
        this->ray_parameter_ = rhs.ray_parameter_;
        this->world_ = rhs.world_;
        this->material_ = rhs.material_;
    }

    ShadeHelper::~ShadeHelper()
    {
        world_.reset();
        material_.reset();
    }
}
