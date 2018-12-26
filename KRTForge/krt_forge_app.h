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
 * \file krt_forge_app.h
 * \date 2018/12/25 10:18
 *
 * \author Administrator
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/
#ifndef krt_forge_app_h__
#define krt_forge_app_h__

using namespace std;

class RayTracingForgeFrame;
class RenderCanvas;
class RenderThread;
class RenderPixel;

class RayTracingForgeApp : public wxApp
{
public:
    virtual bool OnInit();
    virtual int OnExit();
    virtual void SetStatusText(const wxString& text, int number = 0);
private:
    RayTracingForgeFrame *frame;
    DECLARE_EVENT_TABLE()
};

class RayTracingForgeFrame : public wxFrame
{
public:
    RayTracingForgeFrame(const wxPoint& pos, const wxSize& size);

    //event handlers
    void OnQuit(wxCommandEvent& event);
    void OnOpenFile(wxCommandEvent& event);
    void OnSaveFile(wxCommandEvent& event);
    void OnRenderStart(wxCommandEvent& event);
    void OnRenderCompleted(wxCommandEvent& event);
    void OnRenderPause(wxCommandEvent& event);
    void OnRenderResume(wxCommandEvent& event);

private:
    RenderCanvas *canvas; //where the rendering takes place
    wxString currentPath; //for file dialogues
    DECLARE_EVENT_TABLE()
};

//IDs for menu items
enum
{
    Menu_File_Quit = 100,
    Menu_File_Open,
    Menu_File_Save,
    Menu_Render_Start,
    Menu_Render_Pause,
    Menu_Render_Resume
};

#endif // krt_forge_app_h__