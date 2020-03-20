#include "krt_lib_pch.h"
#include "krt_world.h"
#include "krt_color_rgb.h"
#include "krt_view_plane.h"
#include "krt_ray.h"
#include "krt_pinhole_camera.h"

namespace krt
{
    Pinhole::Pinhole(void) : Camera(), d(500), zoom(1.0f)
    {
    }

    Pinhole::Pinhole(const Pinhole& c) : Camera(c), d(c.d), zoom(c.zoom)
    {
    }

    std::shared_ptr<Object> Pinhole::Clone() const
    {
        return std::make_shared<Pinhole>(*this);
    }

    Pinhole& Pinhole::operator= (const Pinhole& rhs)
    {
        if (this == &rhs)
            return *this;

        Camera::operator= (rhs);

        d = rhs.d;
        zoom = rhs.zoom;

        return *this;
    }

    Pinhole::~Pinhole(void)
    {
    }

    glm::dvec3 Pinhole::get_direction(const glm::dvec2& p) const
    {
        //Vector3D dir = p.x * u + p.y * v - d * w;
        //dir.normalize();
        return glm::normalize(p.x * basis_vector_u_ + p.y * basis_vector_v_ - d * basis_vector_w_);
    }

    void Pinhole::render_scene(World* w)
    {
        RGBColor	L;
        ViewPlane&	vp = w->view_plane();//(w.vp);
        Ray			ray;
        int 		depth = 0;
        glm::dvec2 	pp;		// sample point on a pixel    
        int n = static_cast<int>(sqrt(vp.num_samples_per_pixel()));  //int n = (int)sqrt((float)vp.num_samples);

        vp.set_pixel_size(vp.pixel_size() / zoom); //vp.s /= zoom;
        ray.set_origin(eye_); // 执行光追的射线，从摄像机的所在位置发出  // ray.o = eye;

        int v_res = vp.vertical_image_resolution();
        int h_res = vp.horizontal_image_resolution();
        int px_sz = vp.pixel_size();
        const Tracer* tracer = w->tracer();

        for (int r = 0; r < v_res; r++)			// up
        {
            for (int c = 0; c < h_res; c++)
            {		// across 					
                L = RGBColor(0.0f, 0.0f, 0.0f);

                for (int p = 0; p < n; p++)			// up pixel
                {
                    for (int q = 0; q < n; q++)
                    {	// across pixel
                        pp.x = px_sz * (c - 0.5 * h_res + (q + 0.5) / n);
                        pp.y = px_sz * (r - 0.5 * v_res + (p + 0.5) / n);
                        ray.set_direction(get_direction(pp));
                        L += tracer->trace_ray(ray, depth);
                    }
                }

                L /= vp.num_samples_per_pixel();
                L *= exposure_time_;
                w->DisplayPixel(r, c, L);
            }
        }
    }
}