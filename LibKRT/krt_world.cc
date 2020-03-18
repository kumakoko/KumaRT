// this file contains the definition of the World class

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

namespace krt
{
    // -------------------------------------------------------------------- default constructor

    // tracer_ptr is set to nullptr because the build functions will always construct the appropriate tracer
    // ambient_ptr is set to a default ambient light because this will do for most scenes
    // camera_ptr is set to nullptr because the build functions will always have to construct a camera
    // and set its parameters

    World::World(void) : background_color_(0.0f, 0.0f, 0.0f),
        tracer_ptr(nullptr),
        ambient_ptr(/*new Ambient*/),
        camera_ptr(nullptr)
    {
    }

    World::~World(void)
    {
        if (tracer_ptr)
        {
            delete tracer_ptr;
            tracer_ptr = nullptr;
        }

        ambient_ptr.reset();
        camera_ptr.reset();

        delete_objects();
        delete_lights();
    }


    //------------------------------------------------------------------ render_scene

    // This uses orthographic viewing along the zw axis

    void World::render_scene(void) const
    {
        RGBColor	pixel_color;
        Ray			ray;
        int 		hres = vp.horizontal_image_resolution();
        int 		vres = vp.vertical_image_resolution();
        float		s = vp.pixel_size();
        float		zw = 100.0;				// hardwired in

        ray.set_direction(glm::dvec3(0, 0, -1));

        for (int r = 0; r < vres; r++)			// up
        {
            for (int c = 0; c <= hres; c++)
            {	// across 					
                ray.set_origin(glm::dvec3(s * (c - hres / 2.0 + 0.5), s * (r - vres / 2.0 + 0.5), zw));
                pixel_color = tracer_ptr->trace_ray(ray);
                display_pixel(r, c, pixel_color);
            }
        }
    }


    // ------------------------------------------------------------------ clamp

    RGBColor World::max_to_one(const RGBColor& c) const
    {
        float max_value = std::max(c.red_, std::max(c.green_, c.blue_));
        return max_value > 1.0 ? c / max_value : c;
    }


    // ------------------------------------------------------------------ clamp_to_color
    // Set color to red if any component is greater than one

    RGBColor World::clamp_to_color(const RGBColor& raw_color) const
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


    void World::display_pixel(const int row, const int column, const RGBColor& raw_color) const
    {
        RGBColor mapped_color;

        if (vp.show_out_of_gamut())
            mapped_color = clamp_to_color(raw_color);
        else
            mapped_color = max_to_one(raw_color);

        if (vp.gamma_correction_factor() != 1.0)
            mapped_color = mapped_color.Powc(vp.inverse_gamma_correction_factor());

        //have to start from max y coordinate to convert to screen coordinates
        int x = column;
        int y = vp.vertical_image_resolution() - row - 1;

        //paintArea->setPixel(x, y, (int)(mapped_color.r * 255),
        //    (int)(mapped_color.g * 255),
        //    (int)(mapped_color.b * 255));
    }

    // ----------------------------------------------------------------------------- hit_objects

    ShadeHelper World::hit_objects(const Ray& ray)
    {
        //shared_from_this
        ShadeHelper	sr;
        sr.set_world(shared_from_this());

        double		t;
        glm::dvec3 normal;// Normal normal;
        glm::dvec3 local_hit_point;
        double		tmin = HUGE_VALUE;
        int 		num_objects = objects.size();

        for (int j = 0; j < num_objects; j++)
        {
            if (objects[j]->hit(ray, t, sr) && (t < tmin))
            {
                sr.set_hit_an_object(true);
                tmin = t;
                sr.set_material(objects[j]->get_material());
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

    void World::delete_objects(void)
    {
        int num_objects = objects.size();

        for (int j = 0; j < num_objects; j++)
        {
            objects[j].reset();
        }

        objects.erase(objects.begin(), objects.end());
    }

    void World::delete_lights(void)
    {
        int num_lights = lights.size();

        for (int j = 0; j < num_lights; j++)
        {
            lights[j].reset();
        }

        lights.erase(lights.begin(), lights.end());
    }

}