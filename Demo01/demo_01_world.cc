#include "../LibKRT/krt_lib_pch.h"
#include "../LibKRT/krt_sphere.h"
#include "../LibKRT/krt_plane.h"
#include "../LibKRT/krt_flat_color_material.h"
#include "svpng.h"
#include "demo_01_world.h"
#include "demo_01_tracer.h"

#include <iostream>

const int VERT_RES = 800;
const int HORI_RES = 800;

Demo01World::Demo01World()
{
}

void Demo01World::Build()
{
    view_plane_.set_vertical_image_resolution(VERT_RES);
    view_plane_.set_horizontal_image_resolution(HORI_RES);
    view_plane_.set_pixel_size(1.0);
    background_color_ = krt::RGBColor(0.0f, 0.0f, 0.0f);

    tracer_ = new Demo01Tracer(std::dynamic_pointer_cast<Demo01World>(shared_from_this()));

    std::shared_ptr<krt::Sphere> sphere = std::make_shared<krt::Sphere>("Red-Sphere");
    sphere->set_center(0, -25, 0);
    sphere->set_radius(80.0);
    sphere->set_material(std::make_shared<krt::FlatColorMaterial>(1.0f, 0.0f, 0.0f));
    this->AddGeometryObject(sphere);

    sphere = std::make_shared<krt::Sphere>("Yellow-Sphere");
    sphere->set_center(0, 30, 0);
    sphere->set_radius(60.0);
    sphere->set_material(std::make_shared<krt::FlatColorMaterial>(1.0f, 1.0f, 0.0f));
    this->AddGeometryObject(sphere);

    std::shared_ptr<krt::Plane> plane = std::make_shared<krt::Plane>("White-Plane",
        glm::dvec3(0.0,0.0,0.0), glm::dvec3(0.0, 1.0, 1.0));
    plane->set_material(std::make_shared<krt::FlatColorMaterial>(1.0f, 1.0f, 1.0f));
    this->AddGeometryObject(plane);

    pixel_buffer_.resize(VERT_RES * HORI_RES * 3);
}

std::shared_ptr<krt::Object> Demo01World::Clone() const
{
    return std::make_shared<Demo01World>(*this);
}

void Demo01World::WritePixelToBuffer(int x, int y, int red, int green, int blue)
{
    int index = y * view_plane_.vertical_image_resolution() * 3 + x * 3;
    pixel_buffer_[index+0] = (uint8_t)(red);
    pixel_buffer_[index+1] = (uint8_t)(green);
    pixel_buffer_[index+2] = (uint8_t)(blue);
}

void Demo01World::MakePixelBuffer()
{
}

void Demo01World::SavePixelToImageFile(const char* img_file)
{
    FILE *fp = fopen(img_file, "wb");
    svpng(fp, HORI_RES, VERT_RES, pixel_buffer_.data(), 0);
    fclose(fp);
}