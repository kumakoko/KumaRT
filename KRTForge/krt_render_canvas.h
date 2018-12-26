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
 * \file krt_render_canvas.h
 * \date 2018/12/25 10:37
 *
 * \author Xiong Xinke
 * Contact: sun_of_lover@sina.com
 *
 * \brief
 *
 * TODO: 用来显示绘制内容的画布类，这个是指上是一个可卷动的窗口
 *
 * \note
*/
#ifndef krt_render_canvas_h__
#define krt_render_canvas_h__

class RenderThread;

class RenderCanvas : public wxScrolledWindow
{
public:
    RenderCanvas(wxWindow *parent);
    virtual ~RenderCanvas(void);

    void SetImage(wxImage& image);
    wxImage GetImage(void);

    virtual void OnDraw(wxDC& dc);

    //************************************
    // Method:    StartRendering
    // FullName:  RenderCanvas::StartRendering
    // Access:    public 
    // Returns:   void
    // Qualifier:
    // Parameter: void
    //************************************
    void StartRendering(void);


    /****************************************      
    *  PauseRendering 
    *  @return  void
    *  @see   
    *  @note
    ****************************************/
    void PauseRendering();

    /****************************************      
    *  ResumeRendering 
    *  @return  void
    *  @see   
    *  @note 恢复挂起的渲染操作，继续渲染
    ****************************************/
    void ResumeRendering();

    /****************************************      
    *  OnRenderCompleted 
    *  @param   wxCommandEvent & event 
    *  @return  void
    *  @see   
    *  @note  响应渲染完毕的处理函数
    ****************************************/
    void OnRenderCompleted(wxCommandEvent& event);

    /****************************************      
    *  OnTimerUpdate 
    *  @param   wxTimerEvent & event 
    *  @return  void
    *  @see   
    *  @note 响应定时器发送过来消息的处理函数
    ****************************************/
    void OnTimerUpdate(wxTimerEvent& event);

    /****************************************      
    *  OnNewPixel 
    *  @param   wxCommandEvent & event 
    *  @return  void
    *  @see   
    *  @note 当没生成一个新的像素点时，渲染引擎发送消息过来，针对此信息刷新处理
    ****************************************/
    void OnNewPixel(wxCommandEvent& event);

protected:
    wxBitmap *m_image;
    //  World* w;

private:
    RenderThread* thread;
    wxStopWatch* timer;

    long rendered_pixel_count_;
    long pixelsToRender;
    wxTimer updateTimer;

    DECLARE_EVENT_TABLE()
};
#endif // krt_render_canvas_h__

// 画布类