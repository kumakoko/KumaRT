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
#include "krt_substance_refraction.h"

namespace krt
{
    const double SubstanceRefraction::REFRACTION_VACUUM = 1.0000;
    const double SubstanceRefraction::REFRACTION_AIR = 1.0003;
    const double SubstanceRefraction::REFRACTION_ICE = 1.3100;
    const double SubstanceRefraction::REFRACTION_WATER = 1.3330;
    const double SubstanceRefraction::REFRACTION_GASOLINE = 1.3980;
    const double SubstanceRefraction::REFRACTION_GLASS = 1.5500;
    const double SubstanceRefraction::REFRACTION_SAPPHIRE = 1.7700;
    const double SubstanceRefraction::REFRACTION_DIAMOND = 2.4190;
    const double SubstanceRefraction::REFRACTION_MINIMUM = 1.0000;
    const double SubstanceRefraction::REFRACTION_MAXIMUM = 9.0000;

    void SubstanceRefraction::ValidateRefraction(double refraction)
    {
        if (refraction < REFRACTION_MINIMUM || refraction > REFRACTION_MAXIMUM)
        {
           // throw ImagerException("Invalid refractive index.");
        }
    }
}