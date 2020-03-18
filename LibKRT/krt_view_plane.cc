// This file contains the definition the ViewPlane class

#include "krt_lib_pch.h"
#include "krt_view_plane.h"

namespace krt
{
    ViewPlane::ViewPlane(void)
        : horizontal_image_resolution_(400),
        vertical_image_resolution_(400),
        pixel_size_(1.0),
        num_samples_per_pixel_(1),
        gamma_correction_factor_(1.0),
        inverse_gamma_correction_factor_(1.0),
        show_out_of_gamut_(false)
    {}


    ViewPlane::ViewPlane(const ViewPlane& vp)
        : horizontal_image_resolution_(vp.horizontal_image_resolution()),
        vertical_image_resolution_(vp.vertical_image_resolution()),
        pixel_size_(vp.pixel_size()),
        num_samples_per_pixel_(vp.num_samples_per_pixel()),
        gamma_correction_factor_(vp.gamma_correction_factor()),
        inverse_gamma_correction_factor_(vp.inverse_gamma_correction_factor()),
        show_out_of_gamut_(vp.show_out_of_gamut())
    {}


    ViewPlane& ViewPlane::operator= (const ViewPlane& rhs)
    {
        if (this == &rhs)
            return (*this);

        set_horizontal_image_resolution(rhs.horizontal_image_resolution());
        set_vertical_image_resolution(rhs.vertical_image_resolution());
        set_pixel_size(rhs.pixel_size());
        set_num_samples_per_pixel(rhs.num_samples_per_pixel());
        set_gamma_correction_factor(rhs.gamma_correction_factor());
        set_inverse_gamma_correction_factor(rhs.inverse_gamma_correction_factor());
        set_show_out_of_gamut(rhs.show_out_of_gamut());
        return (*this);
    }

    ViewPlane::~ViewPlane(void)
    {
    }
}