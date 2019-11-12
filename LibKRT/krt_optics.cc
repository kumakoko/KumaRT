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
#include "krt_optics.h"

namespace krt
{
    Optics::Optics(): matteColor(glm::vec3(1.0, 1.0, 1.0)), glossColor(glm::vec3(0.0, 0.0, 0.0)), opacity(1.0)
    {
    }

    Optics::Optics(glm::vec3 _matteColor,glm::vec3 _glossColor,double _opacity)
    {
        SetMatteColor(_matteColor);
        SetGlossColor(_glossColor);
        SetOpacity(_opacity);
    }

    void Optics::ValidateReflectionColor(const glm::dvec3& color) const
    {
        // A color is valid for reflection if all its
        // components are in the range 0..1.
        // Otherwise, it is possible for multiple reflections
        // to keep "amplifying" light beyond any limit.
        if (color.r < 0.0 || color.r > 1.0)
        {
     //       throw ImagerException("Invalid red color component.");
        }

        if (color.g < 0.0 || color.g > 1.0)
        {
   //         throw ImagerException("Invalid green color component.");
        }

        if (color.b < 0.0 || color.b > 1.0)
        {
    //        throw ImagerException("Invalid blue color component.");
        }
    }

    void Optics::SetMatteColor(const glm::vec3& _matteColor)
    {
        ValidateReflectionColor(_matteColor);
        matteColor = _matteColor;
    }

    void Optics::SetGlossColor(const glm::vec3& _glossColor)
    {
        ValidateReflectionColor(_glossColor);
        glossColor = _glossColor;
    }

    void Optics::SetMatteGlossBalance(
        double glossFactor,
        const glm::dvec3& rawMatteColor,
        const glm::dvec3& rawGlossColor)
    {
        // Make sure the raw colors have realistic values.
        // Otherwise very high component values can defeat
        // the purpose of trying to balance reflected light
        // levels to realistic ranges.
        ValidateReflectionColor(rawMatteColor);
        ValidateReflectionColor(rawGlossColor);

        // glossFactor must be in the range 0..1.
        if (glossFactor < 0.0 || glossFactor > 1.0)
        {
  //          throw ImagerException("Gloss factor must be in the range 0..1");
        }

        // Scale the glossy and matte parts of reflected light 
        // so that an object does not reflect more light than hits it.
        SetMatteColor((1.0 - glossFactor) * rawMatteColor);
        SetGlossColor(glossFactor * rawGlossColor);
    }

    void Optics::SetOpacity(double _opacity)
    {
        if (_opacity < 0.0 || _opacity > 1.0)
        {
       //     throw ImagerException("Invalid opacity.");
        }
        opacity = _opacity;
    }

}