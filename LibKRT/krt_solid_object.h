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
 * \file krt_solid_object.h
 * \date 2019/11/11 20:23
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
#ifndef kgl_solid_object_h__
#define kgl_solid_object_h__

#include "krt_object.h"
#include "krt_optics.h"
#include "krt_substance_refraction.h"

namespace krt
{
    class Intersection;
    typedef std::vector<Intersection> IntersectionList;

    class SolidObject : public Object
    {
    public:
        SolidObject(const glm::vec3& _center = glm::vec3(0), bool _isFullyEnclosed = true);
        SolidObject(const char* name, const glm::vec3& _center = glm::vec3(0), bool _isFullyEnclosed = true);
        SolidObject(const std::string& name, const glm::vec3& _center = glm::vec3(0), bool _isFullyEnclosed = true);

        virtual ~SolidObject();

        // Appends to 'intersectionList' all the 
        // intersections found starting at the specified vantage 
        // point in the direction of the direction vector.
        /*************************************************************
         * Method:    AppendAllIntersections
         * FullName:  krt::SolidObject::AppendAllIntersections
         * Access:    virtual public
         * Returns:   void
         * Parameter: const glm::dvec3 & vantage
         * Parameter: const glm::dvec3 & direction
         * Parameter: IntersectionList & intersectionList
         * Description: 将从vantage点开始，沿着direction方向发出的光线，
         *              和本solid object发生碰撞之后，产生的intersection
         *              信息，放入到intersectionList表中
        ************************************************************/
        virtual void AppendAllIntersections(const glm::dvec3& vantage, const glm::dvec3& direction, IntersectionList& intersectionList) const = 0;

        // Searches for any intersections with this solid from the 
        // vantage point in the given direction.  If none are found, the 
        // function returns 0 and the 'intersection' parameter is left 
        // unchanged.  Otherwise, returns the positive number of 
        // intersections that lie at minimal distance from the vantage point 
        // in that direction.  Usually this number will be 1 (a unique 
        // intersection is closer than all the others) but it can be greater 
        // if multiple intersections are equally close (e.g. the ray hitting 
        // exactly at the corner of a cube could cause this function to 
        // return 3).  If this function returns a value greater than zero, 
        // it means the 'intersection' parameter has been filled in with the
        // closest intersection (or one of the equally closest intersections).
        int FindClosestIntersection(
            const glm::dvec3& vantage,
            const glm::dvec3& direction,
            Intersection &intersection) const;

        // Returns true if the given point is inside this solid object.
        // This is a default implementation that counts intersections
        // that enter or exit the solid in a given direction from the point.
        // Derived classes can often implement a more efficient algorithm
        // to override this default algorithm.
        virtual bool Contains(const glm::dvec3& point) const;

        // Returns the optical properties (reflection and refraction)
        // at a given point on the surface of this solid.
        // By default, the optical properties are the same everywhere,
        // but a derived class may override this behavior to create
        // patterns of different colors or gloss.
        // It is recommended to keep constant refractive index
        // throughout the solid, or the results may look weird.
        virtual Optics SurfaceOptics(
            const glm::dvec3& surfacePoint,
            const void *context) const
        {
            return uniformOptics;
        }

        // Returns the index of refraction of this solid.  
        // The refractive index is uniform throughout the solid.
        double GetRefractiveIndex() const
        {
            return refractiveIndex;
        }

        // The following three member functions rotate this
        // object counterclockwise around a line parallel
        // to the x, y, or z axis, as seen from the positive
        // axis direction.
        virtual SolidObject& RotateX(double angleInDegrees) = 0;
        virtual SolidObject& RotateY(double angleInDegrees) = 0;
        virtual SolidObject& RotateZ(double angleInDegrees) = 0;

        // Moves the entire solid object by the delta values dx, dy, dz.
        // Derived classes that override this method must chain to it 
        // in order to translate the center of rotation.
        virtual SolidObject& Translate(double dx, double dy, double dz);

        // Moves the center of the solid object to 
        // the new location (cx, cy, cz).
        SolidObject& Move(double cx, double cy, double cz);

        /*************************************************************
         * Method:    Move
         * FullName:  krt::SolidObject::Move
         * Access:    public
         * Returns:   krt::SolidObject& 返回本对象的引用
         * Parameter: const glm::dvec3 & newCenter 新的中心点位置
         * Description:  移动本solid color的中心点，到另一个新位置
        ************************************************************/
        SolidObject& Move(const glm::dvec3& newCenter);

        inline const glm::dvec3& Center() const
        {
            return center;
        }

        // Derived classes are allowed to report different optical
        // properties at different points on their surface(s).
        // For example, different points might have different matte
        // colors in order to depict some kind of pattern on the solid.
        // However, by default, solids have uniform optical properites
        // everywhere on their surface(s).  This method allows callers
        // that know a solid to have this default behavior to define
        // the uniform optical properties.  All writes must take place
        // before rendering starts in order to avoid weird/ugly results.
        /*************************************************************
         * Method:    SetUniformOptics
         * FullName:  krt::SolidObject::SetUniformOptics
         * Access:    public
         * Returns:   void
         * Parameter: const Optics & optics
         * Description:
        ************************************************************/
        inline void SetUniformOptics(const Optics& optics)
        {
            uniformOptics = optics;
        }

        // Helper method for solids with uniform optics (see above).
        // Defines the shiny reflection color (gloss) and
        // dull reflection color (matte), with glossFactor = 0..1
        // that balances between the two modes of reflection.
        // If glossFactor = 0, the object has a completely dull
        // surface.  If glossFactor = 1, the surface is completely
        // mirror-like.
        void SetMatteGlossBalance(
            double glossFactor,
            const glm::vec3& rawMatteColor,
            const glm::vec3& rawGlossColor);

        /*************************************************************
         * Method:    SetFullMatte
         * FullName:  krt::SolidObject::SetFullMatte
         * Access:    public
         * Returns:   void
         * Parameter: const glm::vec3 & matte_color
         * Description: 设置本solid object是完全粗糙，不产生任何的镜面高光反射
        ************************************************************/
        void SetFullMatte(const glm::vec3& matte_color);

        void SetOpacity(const double opacity)
        {
            uniformOptics.SetOpacity(opacity);
        }

        void SetRefraction(const double refraction)
        {
            SubstanceRefraction::ValidateRefraction(refraction);
            refractiveIndex = refraction;
        }

    protected:
        inline const Optics& GetUniformOptics() const
        {
            return uniformOptics;
        }

    private:
        // 本solid object所绕旋转的位置点
        glm::dvec3 center;  // The point in space about which this object rotates.

                        // By default, a solid object has uniform optical properties
                        // across its entire surface.  Unless a derived class
                        // overrides the virtual member function SurfaceOptics(),
                        // the member variable uniformOptics holds these optical
                        // properties.
        Optics uniformOptics;

        // A solid object has a uniform refractive index 
        // throughout its contained volume.
        double refractiveIndex;

        // A flag that indicates whether the Contains() method
        // should try to determine whether a point is inside this
        // solid.  If true, containment calculations proceed;
        // if false, Contains() always returns false.
        // Many derived classes will override the Contains() method
        // and therefore make this flag irrelevant.
        const bool isFullyEnclosed;

        // The following members are an optimization to minimize 
        // the overhead and fragmentation caused by repeated 
        // memory allocations creating and destroying 
        // std::vector contents.
        mutable IntersectionList cachedIntersectionList;
        mutable IntersectionList enclosureList;

       
    };

    typedef std::shared_ptr<SolidObject> SolidObjectSPtr;
}

#endif // kgl_solid_object_h__