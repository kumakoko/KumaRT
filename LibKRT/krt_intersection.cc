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
#include "krt_math.h"

namespace krt
{
    // This constructor initializes to deterministic values
    // in case some code forgets to initialize something.
    Intersection::Intersection() : distanceSquared(1.0e+20), point(0), surfaceNormal(0), solid(nullptr), context(nullptr), tag("")
    {
    }

    Intersection& Intersection::operator =(const Intersection& rhs)
    {
        this->distanceSquared = rhs.distanceSquared;
        this->point = rhs.point;
        this->surfaceNormal = rhs.surfaceNormal;
        this->solid = rhs.solid;
        //const void* context;
        this->tag = rhs.tag;
    }

    int Intersection::PickClosestIntersection(const std::vector<Intersection>& list,Intersection& intersection)
    {
        // We pick the closest intersection, but we return
        // the number of intersections tied for first place
        // in that contest.  This allows the caller to 
        // check for ambiguities in cases where that matters.

        const size_t count = list.size();
        switch (count)
        {
        case 0:
            // No intersection is available.
            // We leave 'intersection' unmodified.
            // The caller must check the return value 
            // to know to avoid using 'intersection'.
            return 0;

        case 1:
            // There is exactly one intersection
            // in the given direction, so there is 
            // no need to think very hard; just use it!
            intersection = list[0];
            return 1;

        default:
            // There are 2 or more intersections, so we need
            // to find the closest one, and look for ties.
            IntersectionList::const_iterator iter = list.begin();
            IntersectionList::const_iterator end = list.end();
            IntersectionList::const_iterator closest = iter;
            int tieCount = 1;
            for (++iter; iter != end; ++iter)
            {
                const double diff = iter->distanceSquared - closest->distanceSquared;
                if (fabs(diff) < EPSILON)
                {
                    // Within tolerance of the closest so far, 
                    // so consider this a tie.
                    ++tieCount;
                }
                else if (diff < 0.0)
                {
                    // This new intersection is definitely closer 
                    // to the vantage point.
                    tieCount = 1;
                    closest = iter;
                }
            }
            intersection = *closest;

            // The caller may need to know if there was an ambiguity,
            // so report back the total number of closest intersections.
            return tieCount;
        }
    }
}