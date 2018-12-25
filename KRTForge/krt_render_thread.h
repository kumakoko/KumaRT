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
 * \file krt_render_thread.h
 * \date 2018/12/25 10:29
 *
 * \author xiong xinke
 * Contact: sun_of_lover@sina.com
 *
 * \brief 
 *
 * TODO: 用来执行渲染计算的后台线程
 *
 * \note
*/
#ifndef krt_render_thread_h__
#define krt_render_thread_h__

class RenderCanvas;
class RenderPixel;

class RenderThread : public wxThread
{
public:
	RenderThread(RenderCanvas* c/*, World* w*/) : wxThread(), /*world(w), */canvas(c) {}
	virtual void *Entry();
	virtual void OnExit();
	virtual void setPixel(int x, int y, int red, int green, int blue);

private:
	void NotifyCanvas();

	//World* world;
	RenderCanvas* canvas;

	std::vector<RenderPixel*> pixels;
	wxStopWatch* timer;
	long lastUpdateTime;
};

#endif // krt_render_thread_h__