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
 * \file krt_optics.h
 * \date 2019/11/11 20:47
 *
 * \author www.xionggf.com
 * Contact: sun_of_lover@sina.com
 *
 * \brief
 *
 * TODO: 用来描述光线和物体在其表面某点发生相交之后，得到的光学属性
 *
 * \note
*/
#ifndef krt_optics_h__
#define krt_optics_h__

namespace krt
{
    // class Optics describes the way a surface point interacts with light.

    class Optics
    {
    public:
        Optics();
        explicit Optics(glm::vec3 _matteColor, glm::vec3 _glossColor = glm::vec3(0.0, 0.0, 0.0), double _opacity = 1.0);
       
        // glossFactor 表面光泽度，1表示绝对光滑，0表示绝对粗糙
        void SetMatteGlossBalance(double glossFactor,const glm::dvec3& rawMatteColor,const glm::dvec3& rawGlossColor);

        void SetMatteColor(const glm::vec3& _matteColor);
        void SetGlossColor(const glm::vec3& _glossColor);
        void SetOpacity(double _opacity);

        inline  const glm::vec3& GetMatteColor() const
        {
            return matteColor;
        }
        inline const glm::vec3& GetGlossColor() const
        {
            return glossColor;
        }
        inline const double GetOpacity()    const
        {
            return opacity;
        }

    protected:
        void ValidateReflectionColor(const glm::dvec3& color) const;

    private:
        glm::vec3   matteColor;     // color, intensity of scattered reflection
        glm::vec3   glossColor;     // color, intensity of mirror reflection
        double  opacity;        // fraction 0..1 of reflected light
    };
}

#endif // krt_optics_h__