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
#include "krt_intersection.h"
#include "krt_solid_object.h"

namespace krt
{
    SolidObject::SolidObject(const glm::vec3& _center, bool _isFullyEnclosed):center(_center), 
                                                                              refractiveIndex(SubstanceRefraction::REFRACTION_GLASS),
                                                                              isFullyEnclosed(_isFullyEnclosed)
    {
    }

    SolidObject::SolidObject(const char* name, const glm::vec3& _center, bool _isFullyEnclosed) :Object(name),
        center(_center),refractiveIndex(SubstanceRefraction::REFRACTION_GLASS),isFullyEnclosed(_isFullyEnclosed)
    {
    }

    SolidObject::SolidObject(const std::string& name, const glm::vec3& _center, bool _isFullyEnclosed) : Object(name), center(_center),
        refractiveIndex(SubstanceRefraction::REFRACTION_GLASS),isFullyEnclosed(_isFullyEnclosed)
    {
    }

    SolidObject::~SolidObject()
    {
    }

    // Moves the center of the solid object to the 
    // location specified by the position vector newCenter.
    SolidObject& SolidObject::Move(const glm::vec3& newCenter)
    {
        Move(newCenter.x, newCenter.y, newCenter.z);
        return *this;
    }

    void SolidObject::SetMatteGlossBalance(double glossFactor,const glm::vec3& rawMatteColor,const glm::vec3& rawGlossColor)
    {
        uniformOptics.SetMatteGlossBalance(glossFactor,rawMatteColor,rawGlossColor);
    }

    void SolidObject::SetFullMatte(const glm::vec3& matte_color)
    {
        uniformOptics.SetMatteGlossBalance(
            0.0,        // glossFactor=0 indicates full matte reflection
            matte_color,
            glm::vec3(0.0f, 0.0f, 0.0f));  // irrelevant, but mass pass something
    }

    // Moves the entire solid object by the delta values dx, dy, dz.
    // Derived classes that override this method must chain to it 
    // in order to translate the center of rotation.
    SolidObject& SolidObject::Translate(double dx, double dy, double dz)
    {
        center.x += dx;
        center.y += dy;
        center.z += dz;
        return *this;
    }

    SolidObject& SolidObject::Move(double cx, double cy, double cz)
    {
        Translate(cx - center.x, cy - center.y, cz - center.z);
        return *this;
    }

    int SolidObject::FindClosestIntersection(const glm::vec3& vantage,const glm::vec3& direction,Intersection &intersection) const
    {
        cachedIntersectionList.clear();
        AppendAllIntersections(vantage, direction, cachedIntersectionList);
        return Intersection::PickClosestIntersection(cachedIntersectionList, intersection);
    }
}