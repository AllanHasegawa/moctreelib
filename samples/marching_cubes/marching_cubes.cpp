#include <wx/wx.h>
#include <wx/glcanvas.h>

#include <CanvasWindow.h>


class MyApp: public wxApp
{
    virtual bool OnInit();
    wxGLCanvas * MyGLCanvas;
};


IMPLEMENT_APP(MyApp)


bool MyApp::OnInit()
{
    wxFrame *frame = new wxFrame((wxFrame *)NULL, -1,  wxT("MOctree Marching Cubes Sample"), wxPoint(50,50), wxSize(800,600));
    new CanvasWindow(frame);

    frame->Show(TRUE);
    return TRUE;
}
