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
#include "krt_render_canvas.h"
#include "krt_custom_events.h"
#include "krt_forge_app.h"
#include "../LibKRT/krt_tools_macro.h"

IMPLEMENT_APP(RayTracingForgeApp)

BEGIN_EVENT_TABLE(RayTracingForgeApp, wxApp)
END_EVENT_TABLE()

bool RayTracingForgeApp::OnInit()
{
    wxInitAllImageHandlers();
    frame = new RayTracingForgeFrame(wxPoint(200, 200), wxSize(1024, 768));
    frame->Centre();
    frame->Show(true);
    SetTopWindow(frame);
    return true;
}

int RayTracingForgeApp::OnExit()
{
    return 0;
}

void RayTracingForgeApp::SetStatusText(const wxString&  text, int number)
{
    frame->SetStatusText(text, number);
}

/******************************************************************************/
/********************* wxraytracerFrame ***************************************/
/******************************************************************************/

BEGIN_EVENT_TABLE(RayTracingForgeFrame, wxFrame)
EVT_MENU(Menu_Render_Start, RayTracingForgeFrame::OnRenderStart)
EVT_MENU(Menu_Render_Pause, RayTracingForgeFrame::OnRenderPause)
EVT_MENU(Menu_Render_Resume, RayTracingForgeFrame::OnRenderResume)
EVT_MENU(Menu_File_Save, RayTracingForgeFrame::OnSaveFile)
EVT_MENU(Menu_File_Open, RayTracingForgeFrame::OnOpenFile)
EVT_MENU(Menu_File_Quit, RayTracingForgeFrame::OnQuit)
EVT_COMMAND(ID_RENDER_COMPLETED, wxEVT_RENDER,RayTracingForgeFrame::OnRenderCompleted)
END_EVENT_TABLE()

RayTracingForgeFrame::RayTracingForgeFrame(const wxPoint& pos, const wxSize& size): 
wxFrame(static_cast<wxFrame*>(nullptr), -1, wxT("Ray Tracing Forge"), pos, size)
{
    wxMenu* menuFile = new wxMenu;
    menuFile->Append(Menu_File_Open, wxT("&Open..."));
    menuFile->Append(Menu_File_Save, wxT("&Save As..."));
    menuFile->AppendSeparator();
    menuFile->Append(Menu_File_Quit, wxT("E&xit"));
    menuFile->Enable(menuFile->FindItem(wxT("&Save As...")), false);

    wxMenu* menuRender = new wxMenu;
    menuRender->Append(Menu_Render_Start, wxT("&Start"));
    menuRender->Append(Menu_Render_Pause, wxT("&Pause"));
    menuRender->Append(Menu_Render_Resume, wxT("&Resume"));

    menuRender->Enable(menuRender->FindItem(wxT("&Start")), true);
    menuRender->Enable(menuRender->FindItem(wxT("&Pause")), false);
    menuRender->Enable(menuRender->FindItem(wxT("&Resume")), false);

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, wxT("&File"));
    menuBar->Append(menuRender, wxT("&Render"));

    SetMenuBar(menuBar);

    canvas = new RenderCanvas(this);

    CreateStatusBar();
    SetStatusText(wxT("Ready"));

    /*wxIcon icon(main_xpm);
    SetIcon(icon);*/

    wxStatusBar* statusBar = GetStatusBar();
    int widths[] = { 150,300 };
    statusBar->SetFieldsCount(2, widths);
}

void RayTracingForgeFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close();
}

void RayTracingForgeFrame::OnSaveFile(wxCommandEvent& WXUNUSED(event))
{
    wxString caption = wxT("Save File");

    wxString wildcard = wxT("BMP files (*.bmp)|*.bmp|"
        "PNG files (*.png)|*.png|"
        "JPEG files (*.jpg)|*.jpg|"
        "TIFF files (*.tif)|*.tif");

    wxString defaultDir = wxEmptyString;
    wxString defaultFilename = wxT("render.bmp");

    wxFileDialog dialog(this, caption, defaultDir, defaultFilename, wildcard,
        wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    dialog.SetPath(currentPath);

    if (dialog.ShowModal() == wxID_OK)
    {
        currentPath = dialog.GetPath();

        wxImage theImage = canvas->GetImage();
        theImage.SaveFile(currentPath);
    }
}

void RayTracingForgeFrame::OnOpenFile(wxCommandEvent& WXUNUSED(event))
{
    wxString caption = wxT("Choose a file");

    wxString wildcard = wxT("BMP files (*.bmp)|*.bmp|"
        "PNG files (*.png)|*.png|"
        "JPEG files (*.jpg)|*.jpg|"
        "TIFF files (*.tif)|*.tif");

    wxString defaultDir = wxEmptyString;
    wxString defaultFilename = wxEmptyString;

    wxFileDialog dialog(this, caption, defaultDir, defaultFilename, wildcard,
        wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    dialog.SetPath(currentPath);

    if (dialog.ShowModal() == wxID_OK)
    {
        currentPath = dialog.GetPath();
        wxImage* theImage = new wxImage();
        theImage->LoadFile(currentPath);

        if (!theImage->IsOk())
        {
            delete theImage;
            wxMessageBox(wxT("Sorry, could not load file."));
        }
        else
        {
            canvas->SetImage(*theImage);
            wxMenu* menuFile = GetMenuBar()->GetMenu(0);
            menuFile->Enable(menuFile->FindItem(wxT("&Save As...")), TRUE);
        }
    }
}

void RayTracingForgeFrame::OnRenderStart(wxCommandEvent& WXUNUSED(event))
{
    wxMenu* menu = GetMenuBar()->GetMenu(1);
    menu->Enable(menu->FindItem(wxT("&Start")), false);
    menu->Enable(menu->FindItem(wxT("&Pause")), true);
    menu->Enable(menu->FindItem(wxT("&Resume")), false);

    canvas->StartRendering();

    wxMenu* menuFile = GetMenuBar()->GetMenu(0);
    menuFile->Enable(menuFile->FindItem(wxT("&Open...")), false);
    menuFile->Enable(menuFile->FindItem(wxT("&Save As...")), true);
}

void RayTracingForgeFrame::OnRenderCompleted(wxCommandEvent& event)
{
    wxMenu* menu = GetMenuBar()->GetMenu(1);
    menu->Enable(menu->FindItem(wxT("&Start")), true);
    menu->Enable(menu->FindItem(wxT("&Pause")), false);
    menu->Enable(menu->FindItem(wxT("&Resume")), false);

    wxMenu* menuFile = GetMenuBar()->GetMenu(0);
    menuFile->Enable(menuFile->FindItem(wxT("&Open...")), true);

    wxGetApp().SetStatusText(wxT("Rendering complete"));
}

void RayTracingForgeFrame::OnRenderPause(wxCommandEvent& event)
{
    wxMenu* menu = GetMenuBar()->GetMenu(1);
    menu->Enable(menu->FindItem(wxT("&Start")), false);
    menu->Enable(menu->FindItem(wxT("&Pause")), false);
    menu->Enable(menu->FindItem(wxT("&Resume")), true);

    canvas->PauseRendering();

    wxGetApp().SetStatusText(wxT("Rendering paused"));
}

void RayTracingForgeFrame::OnRenderResume(wxCommandEvent& event)
{
    wxMenu* menu = GetMenuBar()->GetMenu(1);
    menu->Enable(menu->FindItem(wxT("&Start")), false);
    menu->Enable(menu->FindItem(wxT("&Pause")), true);
    menu->Enable(menu->FindItem(wxT("&Resume")), false);

    canvas->ResumeRendering();

    wxGetApp().SetStatusText(wxT("Rendering..."));
}
