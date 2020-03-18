// This is the declaration of the base class Tracer
// The tracer classes have no copy constructor, assignment operator. or clone function because 
// of the world pointer, which should not be assigned or copy constructed
// See comments in the World.h file.

#ifndef krt_tracer_h__
#define krt_tracer_h__

#include "krt_ray.h"
#include "krt_color_rgb.h"

namespace krt
{
    class World;

    class Tracer
    {
    public:
        Tracer();
        Tracer(std::shared_ptr<World> _world_ptr);
        virtual ~Tracer(void);
        virtual RGBColor trace_ray(const Ray& ray) const;
        virtual RGBColor trace_ray(const Ray& ray, const int depth) const;
    protected:
        std::weak_ptr<World> world_ptr;
    };
}

#endif // krt_tracer_h__
