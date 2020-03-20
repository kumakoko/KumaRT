/*!
 * \file krt_world.h
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


// This file contains the declaration of the class World
// The World class does not have a copy constructor or an assignment operator, for the followign reasons:

// 1 	There's no need to copy construct or assign the World
// 2 	We wouldn't want to do this anyway, because the world can contain an arbitray amount of data
// 3 	These operations wouldn't work because the world is self-referencing:
//	 	the Tracer base class contains a pointer to the world. If we wrote a correct copy constructor for the 
// 	  	Tracer class, the World copy construtor would call itself recursively until we ran out of memory. 
#ifndef krt_world_h__
#define krt_world_h__

#include "krt_tools_macro.h"
#include "krt_view_plane.h"
#include "krt_color_rgb.h"
#include "krt_camera.h"
#include "krt_geometry_object.h"
#include "krt_tracer.h"
#include "krt_light.h"
#include "krt_shade_helper.h"

namespace krt
{
    class World : public Object
    {
    public:
        KRT_INLINE RGBColor background_color() const
        {
            return background_color_;
        }

        World();

        World(const char* name);

        World(const std::string& name);

        ~World();

        virtual void Cleanup();

        KRT_INLINE void add_object(GeometricObjectSPtr object_ptr)
        {
            objects_.push_back(object_ptr);
        }

        KRT_INLINE void add_light(LightSPtr light_ptr)
        {
            lights_.push_back(light_ptr);
        }

        KRT_INLINE void set_ambient_light(LightSPtr light_ptr)
        {
            ambient_light_ = light_ptr;
        }

        KRT_INLINE void set_camera(CameraSPtr c_ptr)
        {
            main_camera_ = c_ptr;
        }

        virtual void build() = 0;

        void render_scene();

        RGBColor max_to_one(const RGBColor& c) const;

        RGBColor clamp_to_color(const RGBColor& c) const;

        void display_pixel(const int row, const int column, const RGBColor& pixel_color);


        /*********************************************************
        把屏幕坐标系(x,y)对应的像素点的颜色值写入到缓冲区种
        @param  int x
        @param  int y
        @param  int red
        @param  int green
        @param  int blue
        *********************************************************/
        virtual void WritePixelToBuffer(int x, int y, int red, int green, int blue);

        virtual void MakePixelBuffer();

        virtual void SavePixelToImageFile(const char* img_file);

        ShadeHelper hit_objects(const Ray& ray);

        KRT_INLINE ViewPlane& view_plane()
        {
            return view_plane_;
        }

        KRT_INLINE const ViewPlane& view_plane() const
        {
            return view_plane_;
        }

        KRT_INLINE const Tracer* tracer() const
        {
            return tracer_;
        }

        KRT_INLINE Tracer* tracer()
        {
            return tracer_;
        }

    protected:
        void delete_objects();
        void delete_lights();
    protected:
        /** * @brief 视平面  */
        ViewPlane view_plane_;

        /** * @brief 缺省的背景色  */
        RGBColor background_color_;

        /** * @brief 光线追踪器  */
        Tracer* tracer_;

        /** * @brief 默认的环境光  */
        LightSPtr ambient_light_;

        /** * @brief 默认的主摄像机  */
        CameraSPtr main_camera_;
        
        /** * @brief 场景中的几何体对象  */
        std::vector<GeometricObjectSPtr> objects_;

        /** * @brief 场景中的光源  */
        std::vector<LightSPtr> lights_;
    };
}

#endif // krt_world_h__