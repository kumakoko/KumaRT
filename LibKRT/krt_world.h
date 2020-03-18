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
    class RenderThread;

    class World : public std::enable_shared_from_this<World>
    {
    public:
        ViewPlane   vp;
        RGBColor    background_color_;
        Tracer*     tracer_ptr;
        LightSPtr   ambient_ptr;
        CameraSPtr  camera_ptr;    
        std::vector<GeometricObjectSPtr> objects;
        std::vector<LightSPtr> lights;
        RenderThread* paintArea; 	//connection to skeleton - wxRaytracer.h
    public:
        World();
        ~World();

        KRT_INLINE void add_object(GeometricObjectSPtr object_ptr)
        {
            objects.push_back(object_ptr);
        }

        KRT_INLINE void add_light(LightSPtr light_ptr)
        {
            lights.push_back(light_ptr);
        }

        KRT_INLINE void set_ambient_light(LightSPtr light_ptr)
        {
            ambient_ptr = light_ptr;
        }

        KRT_INLINE void set_camera(CameraSPtr c_ptr)
        {
            camera_ptr = c_ptr;
        }

        virtual void build() = 0;

        void render_scene() const;

        RGBColor max_to_one(const RGBColor& c) const;

        RGBColor clamp_to_color(const RGBColor& c) const;

        void display_pixel(const int row, const int column, const RGBColor& pixel_color) const;

        ShadeHelper hit_objects(const Ray& ray);
    private:
        void delete_objects();
        void delete_lights();
    };
}

#endif // krt_world_h__