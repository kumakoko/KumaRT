#include "krt_lib_pch.h"
#include "krt_light.h"
#include "krt_shade_helper.h"

namespace krt
{
    Light::Light():Object("KRT-Light")
    {
    }

    Light::Light(const char* name) :Object(name)
    {
    }

    Light::Light(const std::string& name) : Object(name)
    {
    }

    Light::Light(const Light& ls):Object(ls)
    {
    }

    Light& Light::operator= (const Light& rhs)
    {
        if (this == &rhs)
            return *this;

        return *this;
    }

    Light::~Light()
    {
    }

    Light::Light(Light&& ls):Object(ls)
    {

    }

    RGBColor Light::L(ShadeHelper& s)
    {
        return RGBColor(0.0f, 0.0f, 0.0f);
    }
}
