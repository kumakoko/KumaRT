#include "krt_lib_pch.h"
#include "krt_ambient_light.h"

namespace krt
{
    AmbientLight::AmbientLight(const char* name) : Light(name), ls(1.0), color_(1.0)
    {
    }

    AmbientLight::AmbientLight(const std::string& name) : Light(name), ls(1.0), color_(1.0)
    {

    }

    AmbientLight::AmbientLight(const char* name, float d, const RGBColor& color) :
        Light(name), ls(d), color_(color)
    {

    }

    AmbientLight::AmbientLight(const std::string& name, float d, const RGBColor& color) :
        Light(name), ls(d), color_(color)
    {

    }

    AmbientLight::AmbientLight(): Light(),ls(1.0),color_(1.0)
    {
    }

    AmbientLight::AmbientLight(const AmbientLight& a) : Light(a),ls(a.ls),color_(a.color_)
    {
    }

    AmbientLight::AmbientLight(AmbientLight&& a):Light(a), ls(1.0), color_(1.0)
    {
    }

    std::shared_ptr<Object> AmbientLight::Clone() const
    {
        return std::make_shared<AmbientLight>(*this);
    }

    AmbientLight& AmbientLight::operator= (const AmbientLight& rhs)
    {
        if (this == &rhs)
            return (*this);

        Light::operator= (rhs);

        ls = rhs.ls;
        color_ = rhs.color_;

        return *this;
    }
																			
    AmbientLight::~AmbientLight()
    {
    }

    glm::dvec3 AmbientLight::get_direction(ShadeHelper& s)
    {
        return glm::dvec3(0.0);
    }


    // ---------------------------------------------------------------------- L

    RGBColor AmbientLight::L(ShadeHelper& sr) 
    {
        return ls * color_;
    }
}