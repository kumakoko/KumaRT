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
 * \file krt_light_source.h
 * \date 2019/11/11 16:02
 *
 * \author www.xionggf.com
 * Contact: sun_of_lover@sina.com
 *
 * \brief 
 *
 * TODO: 各种光源的基类，在KRT中，光源分为有向平行光，点光源，聚光灯光源，区域面光源四种
 *
 * \note
*/

#include "krt_object.h"

namespace krt
{
    enum LightSourceType
    {
        LST_DIRECTIONAL,    // 有向平行光
        LST_POINT,          // 聚光灯光源
        LST_SPOT,           // 聚光灯光源
        LST_AREA            // 区域面光源
    };


    class LightSource : public Object
    {
    public:
        LightSource(const char* name, LightSourceType lst);
        LightSource(const std::string name, LightSourceType lst);

        LightSource(const char* name, LightSourceType lst,const glm::vec4& color);
        LightSource(const std::string name, LightSourceType lst, const glm::vec4& color);
     
        LightSource(const std::string name, LightSourceType lst, float r,float g ,float b); 
        LightSource(const char* name, LightSourceType lst, float r, float g, float b);

        LightSource(const std::string name, LightSourceType lst, float r, float g, float b,float a);
        LightSource(const char* name, LightSourceType lst, float r, float g, float b, float a);
        virtual ~LightSource();

        virtual const glm::vec3& GetPosition() const = 0;

        virtual const glm::vec3& GetDirection() const = 0;

        inline LightSourceType GetLightSourceType() const
        {
            return type_;
        }

        inline const glm::vec4& GetColor() const
        {
            return color_;
        }

        inline void SetColor(const glm::vec4& color)
        {
            color_ = color;
        }
    private:
        LightSourceType type_;
        glm::vec4       color_;
    };
}