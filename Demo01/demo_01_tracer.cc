#include "../LibKRT/krt_lib_pch.h"
#include "../LibKRT/krt_shade_helper.h"
#include "demo_01_tracer.h"

Demo01Tracer::Demo01Tracer() : krt::Tracer()
{
}

Demo01Tracer::Demo01Tracer(std::shared_ptr<krt::World> _world_ptr) : krt::Tracer(_world_ptr)
{
}

Demo01Tracer::~Demo01Tracer()
{
    world_ptr_.reset();
}

krt::RGBColor Demo01Tracer::trace_ray(const krt::Ray& ray) const
{
    krt::ShadeHelper sr(world_ptr_->HitObjects(ray));
   
    if (sr.hit_an_object())
    {
        return sr.material()->shade(sr);
    }
    else
    {
        return world_ptr_->background_color();
    }
}