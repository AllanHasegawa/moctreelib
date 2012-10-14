/*
 * Copyright (c) 2012 Allan Yoshio Hasegawa
 * 
 * Permission is hereby granted, free of charge, to any
 * person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the
 * Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall
 * be included in all copies or substantial portions of the
 * Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY
 * KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
 * OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "CanvasWindow.h"
#include <wx/wx.h>
#include <wx/glcanvas.h>

CanvasWindow::CanvasWindow(wxFrame *parent)
    : pending_setup_(true),
      wxGLCanvas(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0,
                 wxT("GLCanvas")) {
  int argc = 1;
  char* argv[1] = { wxString((wxTheApp->argv)[0]).char_str()};
}

CanvasWindow::~CanvasWindow() {
  // TODO Auto-generated destructor stub
}

void CanvasWindow::Paintit(wxPaintEvent& WXUNUSED(event)) {
  if (pending_setup_) {
    SetCurrent();
    wxPaintDC(this);
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glViewport(0, 0, (GLint) GetSize().x, (GLint) GetSize().y);

    glClearDepth(1.0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0f, (GLfloat) GetSize().x / (GLfloat) GetSize().y, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);


    pending_setup_ = false;
  } else {
    Render();
    SwapBuffers();
  }
}

void CanvasWindow::Render() {

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();
  glTranslatef(1.5f, 0.0f, -10.0f);             // Move Right And Into The Screen

  //glRotatef(1, 1.0f, 1.0f, 1.0f);            // Rotate The Cube On X, Y & Z

  glBegin(GL_QUADS);                  // Start Drawing The Cube

  glColor3f(0.0f, 1.0f, 0.0f);          // Set The Color To Green
  glVertex3f(1.0f, 1.0f, -1.0f);          // Top Right Of The Quad (Top)
  glVertex3f(-1.0f, 1.0f, -1.0f);          // Top Left Of The Quad (Top)
  glVertex3f(-1.0f, 1.0f, 1.0f);          // Bottom Left Of The Quad (Top)
  glVertex3f(1.0f, 1.0f, 1.0f);          // Bottom Right Of The Quad (Top)
  glColor3f(1.0f, 0.5f, 0.0f);          // Set The Color To Orange
  glVertex3f(1.0f, -1.0f, 1.0f);          // Top Right Of The Quad (Bottom)
  glVertex3f(-1.0f, -1.0f, 1.0f);          // Top Left Of The Quad (Bottom)
  glVertex3f(-1.0f, -1.0f, -1.0f);          // Bottom Left Of The Quad (Bottom)
  glVertex3f(1.0f, -1.0f, -1.0f);          // Bottom Right Of The Quad (Bottom)
  glColor3f(1.0f, 0.0f, 0.0f);          // Set The Color To Red
  glVertex3f(1.0f, 1.0f, 1.0f);          // Top Right Of The Quad (Front)
  glVertex3f(-1.0f, 1.0f, 1.0f);          // Top Left Of The Quad (Front)
  glVertex3f(-1.0f, -1.0f, 1.0f);          // Bottom Left Of The Quad (Front)
  glVertex3f(1.0f, -1.0f, 1.0f);          // Bottom Right Of The Quad (Front)
  glColor3f(1.0f, 1.0f, 0.0f);          // Set The Color To Yellow
  glVertex3f(1.0f, -1.0f, -1.0f);          // Bottom Left Of The Quad (Back)
  glVertex3f(-1.0f, -1.0f, -1.0f);          // Bottom Right Of The Quad (Back)
  glVertex3f(-1.0f, 1.0f, -1.0f);          // Top Right Of The Quad (Back)
  glVertex3f(1.0f, 1.0f, -1.0f);  // Top Left Of The Quad (Back)glColor3f(0.0f,0.0f,1.0f);          // Set The Color To Blue
  glVertex3f(-1.0f, 1.0f, 1.0f);          // Top Right Of The Quad (Left)
  glVertex3f(-1.0f, 1.0f, -1.0f);          // Top Left Of The Quad (Left)
  glVertex3f(-1.0f, -1.0f, -1.0f);          // Bottom Left Of The Quad (Left)
  glVertex3f(-1.0f, -1.0f, 1.0f);          // Bottom Right Of The Quad (Left)
  glColor3f(1.0f, 0.0f, 1.0f);          // Set The Color To Violet
  glVertex3f(1.0f, 1.0f, -1.0f);          // Top Right Of The Quad (Right)
  glVertex3f(1.0f, 1.0f, 1.0f);          // Top Left Of The Quad (Right)
  glVertex3f(1.0f, -1.0f, 1.0f);          // Bottom Left Of The Quad (Right)
  glVertex3f(1.0f, -1.0f, -1.0f);          // Bottom Right Of The Quad (Right)
  glEnd();                        // Done Drawing The Quad

  glFlush();
}
/*
 * wxWidget thing =X
 */BEGIN_EVENT_TABLE(CanvasWindow, wxGLCanvas) EVT_PAINT (CanvasWindow::Paintit)
END_EVENT_TABLE()
