#ifndef demo_01_tracer_h__
#define demo_01_tracer_h__

#include "../LibKRT/krt_tracer.h"
#include "../LibKRT/krt_world.h"
#include "../LibKRT/krt_ray.h"
#include "../LibKRT/krt_color_rgb.h"

class Demo01Tracer : public krt::Tracer
{
public:
    Demo01Tracer();
    Demo01Tracer(std::shared_ptr<krt::World> _world_ptr);
    virtual ~Demo01Tracer();
    virtual krt::RGBColor trace_ray(const krt::Ray& ray) const override;
};

#endif // demo_01_tracer_h__
