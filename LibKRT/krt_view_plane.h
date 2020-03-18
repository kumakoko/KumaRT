/**************************************************************************************************************************
Copyright(C) 2014-2019 www.xionggf.com

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy,
modify, merge, publish, distribute,sublicense, and/or sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM,OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**************************************************************************************************************************/
/*!
 * \file krt_view_plane.h
 * \date 2020/03/15 22:22
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

#ifndef krt_view_plane_h__
#define krt_view_plane_h__

namespace krt
{
    class ViewPlane
    {
    public:
        inline int horizontal_image_resolution() const
        {
            return horizontal_image_resolution_;
        }

        inline void set_horizontal_image_resolution(int val)
        {
            horizontal_image_resolution_ = val;
        }

        inline int vertical_image_resolution() const
        {
            return vertical_image_resolution_;
        }

        inline void set_vertical_image_resolution(int val)
        {
            vertical_image_resolution_ = val;
        }

        inline float pixel_size() const
        {
            return pixel_size_;
        }

        inline void set_pixel_size(float val)
        {
            pixel_size_ = val;
        }

        inline int num_samples_per_pixel() const
        {
            return num_samples_per_pixel_;
        }

        inline void set_num_samples_per_pixel(int val)
        {
            num_samples_per_pixel_ = val;
        }

        inline float gamma_correction_factor() const
        {
            return gamma_correction_factor_;
        }

        inline void set_gamma_correction_factor(float val)
        {
            gamma_correction_factor_ = val;
        }

        inline float inverse_gamma_correction_factor() const
        {
            return inverse_gamma_correction_factor_;
        }

        inline void set_inverse_gamma_correction_factor(float val)
        {
            inverse_gamma_correction_factor_ = val;
        }

        inline bool show_out_of_gamut() const
        {
            return show_out_of_gamut_;
        }

        inline void set_show_out_of_gamut(bool val)
        {
            show_out_of_gamut_ = val;
        }

        ViewPlane();   								// default Constructor

        ViewPlane(const ViewPlane& vp);				// copy constructor

        ViewPlane& operator= (const ViewPlane& rhs);		// assignment operator

        ~ViewPlane();   							// destructor

    protected:
        int horizontal_image_resolution_; // horizontal image resolution 

        int vertical_image_resolution_; // vertical image resolution

        float pixel_size_; // pixel size

        int num_samples_per_pixel_; // number of samples per pixel

        float gamma_correction_factor_; // gamma correction factor

        float inverse_gamma_correction_factor_; // the inverse of the gamma correction factor

        bool show_out_of_gamut_; // display red if RGBColor out of gamut
    };

}
#endif // krt_view_plane_h__