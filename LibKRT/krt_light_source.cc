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
#include "krt_lib_pch.h"
#include "krt_light_source.h"

namespace krt
{
    LightSource::LightSource(const char* name, LightSourceType lst):Object(name),type_(lst),color_(0.0f,0.0f,0.0f,1.0f)
    {
    }

    LightSource::LightSource(const std::string name, LightSourceType lst) : Object(name), type_(lst), color_(0.0f, 0.0f, 0.0f, 1.0f)
    {
    }

    LightSource::LightSource(const char* name, LightSourceType lst, const glm::vec4& color) : Object(name), type_(lst),color_(color)
    {
    }
    
    LightSource::LightSource(const std::string name, LightSourceType lst, const glm::vec4& color) : Object(name), type_(lst), color_(color) 
    {
    }

    LightSource::LightSource(const std::string name, LightSourceType lst, float r, float g, float b) : Object(name), type_(lst), color_(r, g, b, 1.0f)
    {
    }

    LightSource::LightSource(const char* name, LightSourceType lst, float r, float g, float b) : Object(name), type_(lst), color_(r,g,b,1.0f)
    {
    }

    LightSource::LightSource(const std::string name, LightSourceType lst, float r, float g, float b, float a) : Object(name), type_(lst), color_(r, g, b, a)
    {
    }
    
    LightSource::LightSource(const char* name, LightSourceType lst, float r, float g, float b, float a) : Object(name), type_(lst), color_(r, g, b, a) 
    {
    }

    LightSource::~LightSource()
    {
    }
}