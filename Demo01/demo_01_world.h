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
 * \file demo_01_world.h
 * \date 2020/03/18 16:58
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
#ifndef demo_01_world_h__
#define demo_01_world_h__

#include "../LibKRT/krt_world.h"

class Demo01World : public krt::World
{
public:
    Demo01World();
    virtual void Build() override;
    virtual std::shared_ptr<Object> Clone() const override;
    virtual void WritePixelToBuffer(int x, int y, int red, int green, int blue);
    virtual void MakePixelBuffer();
    virtual void SavePixelToImageFile(const char* img_file);
protected:
    std::vector<uint8_t> pixel_buffer_;
};

#endif // demo_01_world_h__