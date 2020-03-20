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
 * \file krt_pinhole_camera.h
 * \date 2020/03/18 12:52
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

#ifndef krt_pinhole_camera_h__
#define krt_pinhole_camera_h__

#include "krt_tools_macro.h"
#include "krt_camera.h"

namespace krt
{
    class Pinhole : public Camera
    {
    public:

        Pinhole();

        Pinhole(const Pinhole& ph);

        virtual std::shared_ptr<Object> Clone() const override;

        virtual Pinhole& operator= (const Pinhole& rhs);

        virtual ~Pinhole();

        KRT_INLINE void set_view_distance(float _d) 
        {
            d = _d;
        }

        KRT_INLINE void set_zoom(float zoom_factor) 
        {
            zoom = zoom_factor;
        }

        glm::dvec3 get_direction(const glm::dvec2& p) const;
     
        virtual void render_scene(World* w) override;

    private:
        /** * @brief 摄像机到视平面的距离  */
        double d;

        /** * @brief 视口的宽高比  */
        float zoom;

    };


}

#endif // krt_pinhole_camera_h__
