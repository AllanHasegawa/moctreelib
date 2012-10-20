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

#ifndef MOCTREE_CANVASWINDOW_H_
#define MOCTREE_CANVASWINDOW_H_

#include <vector>

#include <wx/wx.h>
#include <wx/glcanvas.h>

#include <Triangle.h>
#include <Camera.h>
#include <Vector3.h>
#include <moctree/MOctree.h>

class CanvasWindow : public wxGLCanvas {
 public:
  CanvasWindow(wxFrame* parent);
  virtual ~CanvasWindow();
  void OnPaintit(wxPaintEvent& event);

  void OnResized(wxSizeEvent& evt);
  void OnMouseMoved(wxMouseEvent& event);
  void OnMouseWheelMoved(wxMouseEvent& event);
  void OnMouseLeftDown(wxMouseEvent& event);
  void OnMouseLeftUp(wxMouseEvent& event);
  void OnMouseRightDown(wxMouseEvent& event);
  void OnMouseRightUp(wxMouseEvent& event);
  void OnMouseLeftWindow(wxMouseEvent& event);
  void OnKeyPressed(wxKeyEvent& event);
  void OnKeyReleased(wxKeyEvent& event);
  void OnIdle(wxIdleEvent &event);

 private:
  bool pending_setup_;
  float rot_;
  wxGLContext* gl_context_;
  Camera camera_;
  Vector3 mouse_last_posistion_;
  bool mouse_right_down_;

  GLfloat light_ambient_[4];
  GLfloat light_diffuse_[4];
  GLfloat light_diffuse_pos_[4];

  moctree::MOctree<int>* moctree_;
  int moctree_data_;

  std::vector<Triangle> mesh_;

  void Update(const double& delta_time);
  void Render();
  void SetupOpenGLProjection();
  void SetupOctree();
  void CreateMesh();

 protected:
DECLARE_EVENT_TABLE()

};

#endif /* MOCTREE_CANVASWINDOW_H_ */
