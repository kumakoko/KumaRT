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
#include "../LibKRT/krt_tools_macro.h"
#include "krt_custom_events.h"
#include "krt_render_thread.h"
#include "krt_render_pixel.h"
#include "krt_forge_app.h"
#include "krt_render_canvas.h"

DEFINE_EVENT_TYPE(wxEVT_RENDER)
BEGIN_EVENT_TABLE(RenderCanvas, wxScrolledWindow)
EVT_COMMAND(ID_RENDER_NEWPIXEL, wxEVT_RENDER, RenderCanvas::OnNewPixel)
EVT_COMMAND(ID_RENDER_COMPLETED, wxEVT_RENDER, RenderCanvas::OnRenderCompleted)
EVT_TIMER(ID_RENDER_UPDATE, RenderCanvas::OnTimerUpdate)
END_EVENT_TABLE()

wxDECLARE_APP(RayTracingForgeApp);

RenderCanvas::RenderCanvas(wxWindow *parent):wxScrolledWindow(parent), m_image(nullptr),thread(nullptr),
    timer(nullptr), updateTimer(this, ID_RENDER_UPDATE)
{
    // Sets the background colour of the window but prevents it from being inherited by the children of this window. 
    // 设置本窗口的颜色为某指定颜色，但是它的子窗口并不继承使用这个指定颜色
    SetOwnBackgroundColour(wxColour(143, 144, 150));
}

RenderCanvas::~RenderCanvas(void)
{
    KRT_SAFE_DELETE(m_image);

    if (thread != NULL)
        thread->Delete();

    KRT_SAFE_DELETE(timer);
}

void RenderCanvas::SetImage(wxImage& image)
{
    KRT_SAFE_DELETE(m_image); // 把上一次的操作完毕的BITMAP对象清空，重新开辟一个新的对象用来进行图形显示
    m_image = new wxBitmap(image);
    /*
    SetScrollbars
    第1个参数，在水平方向上每一个“窗口卷动单元”的长度，单位是像素数
    第2个参数，在垂直方向上每一个“窗口卷动单元”的长度，单位是像素数
    第3个参数，在水平方向上有多少个“窗口卷动单元”
    第4个参数，在垂直方向上有多少个“窗口卷动单元”
    第5个参数，在水平方向上，卷动条的初始位置在哪里，即在第几个卷动单元的长度偏移位置处
    第6个参数，在垂直方向上，卷动条的初始位置在哪里，即在第几个卷动单元的长度偏移位置处
    第7个参数，为true的时候，不刷新窗口
    */
    int px_per_unit_x = 10;
    int px_per_unit_y = 10;
    int unit_x = static_cast<int>(static_cast<float>(m_image->GetWidth()) / static_cast<float>(px_per_unit_x));
    int unit_y = static_cast<int>(static_cast<float>(m_image->GetWidth()) / static_cast<float>(px_per_unit_x));
    int x_pos = 0, y_pos = 0;
    bool no_refresh = true;
    this->SetScrollbars(px_per_unit_x, px_per_unit_y, unit_x, unit_y, x_pos, y_pos, no_refresh);
    this->Refresh();
}

wxImage RenderCanvas::GetImage(void)
{
    if (m_image != nullptr)
        return m_image->ConvertToImage();

    return wxImage();
}

void RenderCanvas::OnDraw(wxDC& dc)
{
    if (m_image != nullptr && m_image->IsOk())
        wxBufferedDC bdc(&dc, *m_image);
}

void RenderCanvas::OnRenderCompleted(wxCommandEvent& event)
{
    thread = nullptr;

    if (timer != nullptr)
    {
        long interval = timer->Time();

        wxTimeSpan timeElapsed(0, 0, 0, interval);
        wxString timeString = timeElapsed.Format(wxT("Elapsed Time: %H:%M:%S"));
        wxGetApp().SetStatusText(timeString, 1);
        delete timer;
        timer = NULL;
    }
}

void RenderCanvas::OnNewPixel(wxCommandEvent& event)
{
    /* 摘录自v3.2.1 wxWidgets文档
    A wxClientDC must be constructed if an application wishes to paint on the client area of a window from outside an EVT_PAINT() 
    handler.This should normally be constructed as a temporary stack object; don't store a wxClientDC object.
    
    1 To draw on a window from within an EVT_PAINT() handler, construct a wxPaintDC object instead.
    2 To draw on the whole window including decorations, construct a wxWindowDC object (Windows only).
    
    A wxClientDC object is initialized to use the same font and colours as the window it is associated with.
    */
    wxClientDC cdc(this); // 拿到窗口客户区的DC，

    /* 摘录自v3.2.1 wxWidgets文档
    Call this function to prepare the device context for drawing a scrolled image.
    It sets the device origin according to the current scroll position. DoPrepareDC() is called automatically within the default wxEVT_PAINT event handler, 
    so your OnDraw() override will be passed an already 'pre-scrolled' device context. However, if you wish to draw from outside of OnDraw() (e.g. from your 
    own wxEVT_PAINT handler), you must call this function yourself.
    */
    DoPrepareDC(cdc);

    /*
    wxBufferedDC的防止画面绘制时撕裂的原理是：当在这DC上绘制内容时，实质上是先绘制在一个内存缓冲区中，通常这缓冲区是由一个wxBitmap对象缩提供的。
    然后，再把这些数据copy到真正的DC中去。
    */
    wxBufferedDC bufferedDC(&cdc, *m_image); // 使用一个双缓冲dc，以解决绘制时的闪烁问题

    //iterate over all pixels in the event
    std::vector<RenderPixel*> *pixelsUpdate = reinterpret_cast<std::vector<RenderPixel*>*>(event.GetClientData());

    // 逐个逐个像素地绘制出来，每新生成一个像素点的值，就生成一个新的
    for (auto itr = pixelsUpdate->begin(); itr != pixelsUpdate->end(); itr++)
    {
        RenderPixel* pixel = *itr;
        wxPen pen(wxColour(pixel->red, pixel->green, pixel->blue));
        bufferedDC.SetPen(pen);
        bufferedDC.DrawPoint(pixel->x, pixel->y);
        this->rendered_pixel_count_++;
        delete pixel; // 绘制完一个，就删除掉一个
    }

    pixelsUpdate->clear();
    delete pixelsUpdate;
}

void RenderCanvas::PauseRendering(void)
{
    if (thread != NULL)
        thread->Pause();

    updateTimer.Stop();

    if (timer != NULL)
        timer->Pause();
}

void RenderCanvas::ResumeRendering(void)
{
    if (thread != NULL)
        thread->Resume();

    updateTimer.Start();

    if (timer != NULL)
        timer->Resume();
}

void RenderCanvas::OnTimerUpdate(wxTimerEvent& event)
{
    if (timer == NULL)
        return;

    //percent
    float completed = (float)rendered_pixel_count_ / (float)pixelsToRender;

    wxString progressString = wxString::Format(wxT("Rendering...%d%%"),
        (int)(completed * 100));
    wxGetApp().SetStatusText(progressString, 0);

    //time elapsed
    long interval = timer->Time();

    wxTimeSpan timeElapsed(0, 0, 0, interval);

    //time remaining
    float remaining = 1.0f - completed;
    long msecRemain = (long)
        (((double)interval / (completed * 100)) * 100 * remaining);

    wxTimeSpan timeRemaining(0, 0, 0, msecRemain);

    wxString timeRemainString = timeRemaining.Format(wxT(" / ETA: %H:%M:%S"));
    wxString timeString = timeElapsed.Format(wxT("Elapsed Time: %H:%M:%S"));

    //only display ETA if something has been completed
    if (msecRemain >= 0)
        wxGetApp().SetStatusText(timeString + timeRemainString, 1);
    else
        wxGetApp().SetStatusText(timeString, 1);
}

void RenderCanvas::StartRendering(void)
{
    //  w = new World();

    wxGetApp().SetStatusText(wxT("Building world..."));

    //  w->build();

    wxGetApp().SetStatusText(wxT("Rendering..."));

    rendered_pixel_count_ = 0;
    //  pixelsToRender = w->vp.hres * w->vp.vres;

        //set the background
        /*wxBitmap bitmap(w->vp.hres, w->vp.vres, -1);
        wxMemoryDC dc;
        dc.SelectObject(bitmap);
        dc.SetBackground(*wxGREY_BRUSH);
        dc.Clear();*/

        /*wxBitmap tile(bg_xpm);

        for (int x = 0; x < w->vp.hres; x += 16)
        {
            for (int y = 0; y < w->vp.vres; y += 16)
                dc.DrawBitmap(tile, x, y, FALSE);
        }*/

        /*dc.SelectObject(wxNullBitmap);

        wxImage temp = bitmap.ConvertToImage();
        SetImage(temp);*/

    updateTimer.Start(250);

    //start timer
    timer = new wxStopWatch();

    thread = new RenderThread(this/*, w*/);
    thread->Create();
    //  w->paintArea = thread;
    thread->SetPriority(20);
    thread->Run();
}