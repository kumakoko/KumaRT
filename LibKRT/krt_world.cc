﻿// this file contains the definition of the World class

//#include "wxraytracer.h"
//
//#include "World.h"
//#include "Constants.h"
//
//// geometric objects
//
//#include "Plane.h"
//#include "Sphere.h"
//
//// tracers
//
//#include "SingleSphere.h"
//#include "MultipleObjects.h"
//#include "RayCast.h"
//
//// cameras
//
//#include "Pinhole.h"
//
//// lights
//
//#include "Directional.h"
//
//// materials
//
//#include "Matte.h"
//
//// utilities
//
//#include "glm::dvec3.h"
//#include "glm::dvec3.h"
//#include "Normal.h"
//#include "ShadeRec.h"
//#include "Maths.h"
//
//// build functions
//
//#include "BuildShadedObjects.cpp"

#include "krt_lib_pch.h"
#include "krt_world.h"
#include "krt_math.h"
#include "krt_tools_macro.h"

namespace krt
{
    // -------------------------------------------------------------------- default constructor

    // tracer_ptr is set to nullptr because the build functions will always construct the appropriate tracer
    // ambient_ptr is set to a default ambient light because this will do for most scenes
    // camera_ptr is set to nullptr because the build functions will always have to construct a camera
    // and set its parameters

    World::World() : background_color_(0.0f, 0.0f, 0.0f),tracer_(nullptr)
    {
    }

    World::World(const char* name) : Object(name), background_color_(0.0f, 0.0f, 0.0f), tracer_(nullptr)
    {
    }

    World::World(const std::string& name) : Object(name), background_color_(0.0f, 0.0f, 0.0f), tracer_(nullptr)
    {
    }

    World::~World()
    {
        ambient_light_.reset();
        main_camera_.reset();
        delete_objects();
        delete_lights();
    }

    void World::Cleanup()
    {
        KRT_SAFE_DELETE(tracer_);
    }

    //------------------------------------------------------------------ render_scene

    // This uses orthographic viewing along the zw axis

    void World::RenderScene()
    {
        RGBColor	pixel_color;
        Ray			ray;
        int 		hres = view_plane_.horizontal_image_resolution();
        int 		vres = view_plane_.vertical_image_resolution();
        float		s = view_plane_.pixel_size();
        float		zw = 100.0;				// hardwired in

        ray.set_direction(glm::dvec3(0, 0, -1));

        for (int r = 0; r < vres; r++)			// up
        {
            for (int c = 0; c < hres; c++)
            {	// across 					
                ray.set_origin(glm::dvec3(s * (c - hres / 2.0 + 0.5), s * (r - vres / 2.0 + 0.5), zw));
                pixel_color = tracer_->trace_ray(ray);
                DisplayPixel(r, c, pixel_color);
            }
        }
    }


    // ------------------------------------------------------------------ clamp

    RGBColor World::MaxToOne(const RGBColor& c) const
    {
        float max_value = std::max(c.red_, std::max(c.green_, c.blue_));
        return max_value > 1.0 ? c / max_value : c;
    }


    // ------------------------------------------------------------------ clamp_to_color
    // Set color to red if any component is greater than one

    RGBColor World::ClampToColor(const RGBColor& raw_color) const
    {
        RGBColor c(raw_color);

        if (raw_color.red_ > 1.0 || raw_color.green_ > 1.0 || raw_color.blue_ > 1.0)
        {
            c.red_ = 1.0; c.green_ = 0.0; c.blue_ = 0.0;
        }

        return (c);
    }


    // ---------------------------------------------------------------------------display_pixel
    // raw_color is the pixel color computed by the ray tracer
    // its RGB floating point components can be arbitrarily large
    // mapped_color has all components in the range [0, 1], but still floating point
    // display color has integer components for computer display
    // the Mac's components are in the range [0, 65535]
    // a PC's components will probably be in the range [0, 255]
    // the system-dependent code is in the function convert_to_display_color
    // the function SetCPixel is a Mac OS function


    void World::DisplayPixel(const int row, const int column, const RGBColor& raw_color)
    {
        RGBColor mapped_color;

        if (view_plane_.show_out_of_gamut())
            mapped_color = ClampToColor(raw_color);
        else
            mapped_color = MaxToOne(raw_color);

        if (view_plane_.gamma_correction_factor() != 1.0)
            mapped_color = mapped_color.Powc(view_plane_.inverse_gamma_correction_factor());

        //have to start from max y coordinate to convert to screen coordinates
        int x = column;
        int y = view_plane_.vertical_image_resolution() - row - 1;

        //paintArea->setPixel(x, y, (int)(mapped_color.r * 255),
        //    (int)(mapped_color.g * 255),
        //    (int)(mapped_color.b * 255));
        this->WritePixelToBuffer(x, y, (int)(mapped_color.red_ * 255), (int)(mapped_color.green_ * 255), (int)(mapped_color.blue_ * 255));
    }

    void World::WritePixelToBuffer(int x, int y, int red, int green, int blue)
    {

    }

    void World::MakePixelBuffer()
    {
    }

    void World::SavePixelToImageFile(const char* img_file)
    {
    }
    // ----------------------------------------------------------------------------- hit_objects

    ShadeHelper World::HitObjects(const Ray& ray)
    {
        //shared_from_this
        ShadeHelper	sr;
        sr.set_world(std::dynamic_pointer_cast<World>(shared_from_this()));
        double		t;
        glm::dvec3 normal;// Normal normal;
        glm::dvec3 local_hit_point;
        double		tmin = HUGE_VALUE;
        int 		num_objects = objects_.size();

        for (int j = 0; j < num_objects; j++)
        {
            if (objects_[j]->hit(ray, t, sr) && (t < tmin))
            {
                sr.set_hit_an_object(true);
                tmin = t;
                sr.set_material(objects_[j]->get_material());
                sr.set_hit_point(ray.GetTargetPoint(t));
                normal = sr.normal();
                local_hit_point = sr.local_hit_point();
            }
        }

        if (sr.hit_an_object())
        {
            sr.set_ray_parameter(tmin);
            sr.set_normal(normal);
            sr.set_local_hit_point(local_hit_point);
        }

        return sr;
    }

    // Deletes the objects in the objects array, and erases the array.
    // The objects array still exists, because it's an automatic variable, but it's empty 

    void World::delete_objects()
    {
        int num_objects = objects_.size();

        for (int j = 0; j < num_objects; j++)
        {
            objects_[j].reset();
        }

        objects_.erase(objects_.begin(), objects_.end());
    }

    void World::delete_lights()
    {
        int num_lights = lights_.size();

        for (int j = 0; j < num_lights; j++)
        {
            lights_[j].reset();
        }

        lights_.erase(lights_.begin(), lights_.end());
    }

}