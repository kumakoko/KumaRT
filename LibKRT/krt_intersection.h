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
/*!
 * \file krt_intersection.h
 * \date 2019/11/11 16:42
 *
 * \author www.xionggf.com
 * Contact: sun_of_lover@sina.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

// struct Intersection provides information about a ray intersecting
// with a point on the surface of a SolidObject.
#include "krt_solid_object.h"

namespace krt
{
    class Intersection
    {
    private:
        // The square of the distance from the
        // vantage point to the intersection point.
        double distanceSquared;

        // The location of the intersection point.
        glm::vec3 point;

        // The unit vector perpendicular to the 
        // surface at the intersection point.
        glm::vec3 surfaceNormal;

        // A pointer to the solid object that the ray
        // intersected with.
        SolidObjectSPtr solid;

        // An optional tag for classes derived from SolidObject to cache 
        // arbitrary information about surface optics.  Most classes can 
        // safely leave this pointer as NULL, its default value.
        const void* context;

        // An optional tag used for debugging.
        // Anything that finds an intersection may elect to make tag point 
        // at a static string to help the programmer figure out, for example, 
        // which of multiple surfaces was involved.  This is just a char* 
        // instead of std::string to minimize overhead by eliminating dynamic
        // memory allocation.
        std::string tag;
    public:
        inline double GetDistanceSquared() const
        {
            return distanceSquared;
        }

        inline void SetDistanceSquared(double d)
        {
            distanceSquared = d;
        }

        inline const glm::dvec3& GetPoint() const
        {
            return point;
        }
        
        inline void SetPoint(const glm::dvec3& p)
        {
            point = p;
        }

        inline const glm::dvec3& GetSurfaceNormal() const
        {
            return surfaceNormal;
        }
        
        inline void SetSurfaceNormal(const glm::dvec3& n)
        {
            surfaceNormal = n;
        }

        inline void SetSolidObject(SolidObjectSPtr s)
        {
            solid = s;
        }

        inline SolidObjectSPtr GetSolidObject()
        {
            return solid;
        }

        inline void SetTag(const std::string& t)
        {
            tag = t;
        }

        inline void SetTag(const char* t)
        {
            tag = t;
        }

        inline const std::string& GetTag() const
        {
            return tag;
        }

    public:
        // This constructor initializes to deterministic values
        // in case some code forgets to initialize something.
        Intersection();

        krt::Intersection &krt::Intersection::operator =(const krt::Intersection& rhs);

        /*************************************************************
         * Method:    PickClosestIntersection
         * FullName:  krt::Intersection::PickClosestIntersection
         * Access:    public static 
         * Returns:   int
         * Parameter: const std::vector<Intersection> & list
         * Parameter: Intersection & intersection
         * Description: 从list中取出一个最靠近的相交，然后返回
        ************************************************************/
        static int PickClosestIntersection(const std::vector<Intersection>& list, Intersection& intersection);
    };
}