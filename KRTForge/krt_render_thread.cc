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
#include "krt_forge_pch.h"
#include "krt_render_pixel.h"
#include "krt_render_canvas.h"
#include "krt_custom_events.h"
#include "krt_render_thread.h"


void RenderThread::setPixel(int x, int y, int red, int green, int blue)
{

	pixels.push_back(new RenderPixel(x, y, red, green, blue));

	if (timer->Time() - lastUpdateTime > 40)
		NotifyCanvas();

	TestDestroy();
}

void RenderThread::NotifyCanvas()
{
	lastUpdateTime = timer->Time();

	//copy rendered pixels into a new vector and reset
	auto pixelsUpdate = new std::vector<RenderPixel*>(pixels);
	pixels.clear();

	wxCommandEvent e(wxEVT_RENDER, ID_RENDER_NEWPIXEL);

	// 在work线程中往主线程传递数据时，使用SetClientData函数，在work线程中，new出数据
	// 在主线程中，delete这些数据。
	e.SetClientData(pixelsUpdate);

	/*
	Post an event to be processed later.
	
	This function is similar to QueueEvent() but can't be used to post events from worker threads for the event objects with
	wxString fields (i.e. in practice most of them) because of an unsafe use of the same wxString object which happens because
	the wxString field in the original event object and its copy made internally by this function share the same string buffer 
	internally. Use QueueEvent() to avoid this.
	
	A copy of event is made by the function, so the original can be deleted as soon as function returns (it is common that the 
	original is created on the stack). This requires that the wxEvent::Clone() method be implemented by event so that it can be 
	duplicated and stored until it gets processed.
	*/
	canvas->GetEventHandler()->AddPendingEvent(e);
}

void RenderThread::OnExit()
{
	NotifyCanvas();

	// work线程结束了，发送一个“渲染结束”的自定义事件到主线程
	wxCommandEvent e(wxEVT_RENDER, ID_RENDER_COMPLETED); 
	canvas->GetEventHandler()->AddPendingEvent(e);
	canvas->GetParent()->GetEventHandler()->AddPendingEvent(e);
}

void *RenderThread::Entry()
{
	lastUpdateTime = 0;
	timer = new wxStopWatch();

	//world->render_scene(); //for bare bones ray tracer only
//	world->camera_ptr->render_scene(*world);

	return nullptr;
}
