#include "krt_lib_pch.h"
#include "krt_tracer.h"

namespace krt
{
    Tracer::Tracer()
    {
    }

    Tracer::Tracer(std::shared_ptr<World> _world_ptr) : world_ptr_(_world_ptr)
    {
        world_ptr_ = _world_ptr;
    }

    Tracer::~Tracer() 
    {
        world_ptr_.reset();
    }

    RGBColor Tracer::trace_ray(const Ray& ray) const 
    {
        return RGBColor(0.0f,0.0f,0.0f);
    }

    RGBColor Tracer::trace_ray(const Ray& ray, const int depth) const
    {
        return RGBColor(0.0f, 0.0f, 0.0f);
    }
}