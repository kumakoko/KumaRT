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
 * \file krt_camera.h
 * \date 2020/03/17 21:45
 *
 * \author www.xionggf.com
 * Contact: sun_of_lover@sina.com
 *
 * \brief 
 *
 * TODO: 
 *
 * \note
*/


// This file contains the declaration of the base class Camera
// There is no view plane distance because the fisheye and panoramic cameras don't use it
#ifndef krt_camera_h__
#define krt_camera_h__

#include "krt_object.h"
#include "krt_tools_macro.h"

namespace krt
{
    class World;

    class Camera : public Object
    {
    public:
        Camera();

        Camera(const char* name);

        Camera(const std::string& name);

        Camera(const Camera& camera);

        Camera(Camera&& camera);

        virtual ~Camera();

        virtual void render_scene(World* w) = 0;

        KRT_INLINE void set_eye(const glm::dvec3& p)
        {
            eye_ = p;
        }

        KRT_INLINE void set_eye(double x, double y, double z)
        {
            eye_.x = x; eye_.y = y; eye_.z = z;
        }

        KRT_INLINE void set_lookat(const glm::dvec3& p)
        {
            lookat_ = p;
        }

        KRT_INLINE void set_lookat(double x, double y, double z)
        {
            lookat_.x = x; lookat_.y = y; lookat_.z = z;
        }

        KRT_INLINE void set_up_vector(const glm::dvec3& u)
        {
            up_ = u;
        }

        KRT_INLINE void set_up_vector(const float x, const float y, const float z)
        {
            up_.x = x; up_.y = y; up_.z = z;
        }

        KRT_INLINE void set_roll(const float r)
        {
            roll_angle_ = r;
        }

        KRT_INLINE void set_exposure_time(const float exposure)
        {
            exposure_time_ = exposure;
        }

        void compute_uvw(void);

    protected:

        Camera& operator= (const Camera& camera);

    protected:
        float exposure_time_;

        /** * @brief 摄像机绕着其自身Z轴旋转的角度  */
        double roll_angle_;

        /** * @brief 攝像機在世界空間中的坐標值  */
        glm::dvec3 eye_;

        /** * @brief 攝像機所“盯着看”的目标点在在世界空间中的坐标值  */
        glm::dvec3 lookat_;

        /** * @brief 构成观察空间的三个正交基向量中的u向量  */
        glm::dvec3 basis_vector_u_;

        /** * @brief 构成观察空间的三个正交基向量中的v向量  */
        glm::dvec3 basis_vector_v_;

        /** * @brief 构成观察空间的三个正交基向量中的w向量  */
        glm::dvec3 basis_vector_w_;

        /** * @brief 摄像机的朝上向量值，基于世界坐标系 */
        glm::dvec3 up_;

    };

    typedef std::shared_ptr<Camera> CameraSPtr;
}

#endif // krt_camera_h__