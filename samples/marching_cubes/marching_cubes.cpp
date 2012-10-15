#include <stdio.h>

#include <wx/wx.h>
#include <wx/glcanvas.h>

#include <CanvasWindow.h>

class MyApp : public wxApp {
 private:
  virtual bool OnInit();
  CanvasWindow * canvas_window_;
  wxFrame* frame_;
};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit() {

  printf("Initializing MOctree Marching Cubes Sample..\n");

  wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
  frame_ = new wxFrame((wxFrame *) NULL, -1,
                               wxT("MOctree Marching Cubes Sample"),
                               wxPoint(50, 50), wxSize(800, 600));
  canvas_window_ = new CanvasWindow(frame_);
  sizer->Add(canvas_window_, 1, wxEXPAND);

  frame_->SetSizer(sizer);
  frame_->SetAutoLayout(true);
  frame_->Show(TRUE);
  return TRUE;
}
