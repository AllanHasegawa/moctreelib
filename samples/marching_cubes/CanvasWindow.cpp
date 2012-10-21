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

#include <ctime>
#include <stdio.h>

#include <wx/wx.h>
#include <wx/glcanvas.h>

#include <moctree/classic/ClassicOctree.h>
#include <moctree/MOctreeCell.h>

#include <MCTemplate.h>
#include <MarchingCubes.h>

CanvasWindow::CanvasWindow(wxFrame *parent)
    : pending_setup_(true),
      wxGLCanvas(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                 wxFULL_REPAINT_ON_RESIZE) {
  int argc = 1;
  char* argv[1] = { wxString((wxTheApp->argv)[0]).char_str()};

  gl_context_ = new wxGLContext(this);

  SetBackgroundStyle(wxBG_STYLE_CUSTOM);

  SetupOctree();
  CreateMesh();
}

CanvasWindow::~CanvasWindow() {
  delete gl_context_;
}

void CanvasWindow::OnPaintit(wxPaintEvent& WXUNUSED(event)) {
  wxGLCanvas::SetCurrent(*gl_context_);
  wxPaintDC(this);
  if (pending_setup_) {
    light_ambient_[0] = 0.2f;
    light_ambient_[1] = 0.2f;
    light_ambient_[2] = 0.2f;
    light_ambient_[3] = 1.f;

    light_diffuse_[0] = 1.f;
    light_diffuse_[1] = 1.f;
    light_diffuse_[2] = 1.f;
    light_diffuse_[3] = 1.f;

    light_diffuse_pos_[0] = 0.f;
    light_diffuse_pos_[0] = 100.f;
    light_diffuse_pos_[0] = 0.f;
    light_diffuse_pos_[0] = 1.f;

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glClearDepth(1.0);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient_);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse_);
    glLightfv(GL_LIGHT1, GL_POSITION, light_diffuse_pos_);
    //glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    SetupOpenGLProjection();

    rot_ = 0;
    pending_setup_ = false;
  } else {
    Render();
    SwapBuffers();
  }
}

void CanvasWindow::Update(const double& delta_time) {
  Refresh(false);

  camera_.Update(delta_time);

  rot_ += 0.1 * delta_time;
}

void CanvasWindow::Render() {
  camera_.Render();

  //glTranslatef(0, 0, 50);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  //MarchingCubes* mc = MarchingCubes::CreateMarchingCubes();

  //mc->GetTemplate(0, 0, 33, 0, 0, 0, 0, 0)->Render();
  /*
   printf("%d\n", mc->CornersToIndex(0, 0, 1, 1, 0, 0, 1, 1));
   glTranslatef(1, 0, 0);
   mc->GetTemplate(0, 0, 1, 1, 0, 0, 1, 1)->Render();
   glTranslatef(1, 0, 0);
   mc->GetTemplate(0, 0, 1, 1, 0, 0, 1, 1)->Render();
   glTranslatef(1, 0, 0);
   mc->GetTemplate(0, 0, 1, 0, 0, 0, 1, 0)->Render();
   glTranslatef(0, 1, 0);
   mc->GetTemplate(1, 0, 1, 0, 1, 0, 0, 0)->Render();
   glTranslatef(0, 0, -1);
   mc->GetTemplate(1, 0, 0, 0, 0, 0, 0, 0)->Render();
   */
  for (std::vector<Triangle>::iterator i = mesh_.begin(); i != mesh_.end();
      i++) {
    i->Render();
  }
  /*


   glPushMatrix();
   mc->GetTemplate(0, 1, 0, 0, 1, 1, 1, 0)->Render();
   glPopMatrix();

   glPushMatrix();
   //mc->GetTemplate(1, 1, 1, 1, 0, 0, 1, 1)->Render();
   glPopMatrix();

   glPushMatrix();
   //mc->GetTemplate(0, 0, 0, 0, 1, 1, 0, 0)->Render();
   glPopMatrix();

   glPushMatrix();
   //mc->GetTemplate(0, 0, 0, 0, 0, 0, 1, 1)->Render();
   glPopMatrix();
   /*
   glPushMatrix();
   mc->GetTemplate(0, 0, 0, 0, 1, 0, 0, 0)->Render();
   glPopMatrix();

   glPushMatrix();
   mc->GetTemplate(0, 0, 0, 0, 0, 1, 0, 0)->Render();
   glPopMatrix();

   glPushMatrix();
   mc->GetTemplate(0, 0, 0, 0, 0, 0, 1, 0)->Render();
   glPopMatrix();

   glPushMatrix();
   mc->GetTemplate(0, 0, 0, 0, 0, 0, 0, 1)->Render();
   glPopMatrix();

   /*
   *
   */
  glFlush();
}

void CanvasWindow::SetupOpenGLProjection() {

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glViewport(0, 0, (GLint) GetSize().x, (GLint) GetSize().y);

  gluPerspective(45.0f, (GLfloat) GetSize().x / (GLfloat) GetSize().y, 0.1f,
                 10000.0f);

  glMatrixMode(GL_MODELVIEW);
}

void CanvasWindow::OnResized(wxSizeEvent& evt) {

  SetupOpenGLProjection();

  Refresh();

}

void CanvasWindow::OnIdle(wxIdleEvent &event) {
  double delta_time = 1.f;
  Update(delta_time);
}

void CanvasWindow::OnMouseMoved(wxMouseEvent& event) {
  const int px = event.GetPosition().x;
  const int py = event.GetPosition().y;

  if (mouse_right_down_) {
    const int lpx = mouse_last_posistion_.x_;
    const int lpy = mouse_last_posistion_.y_;

    camera_.SetAngleDisplacement(-(py - lpy), px - lpx, 0);
  }

  mouse_last_posistion_.x_ = px;
  mouse_last_posistion_.y_ = py;

}

void CanvasWindow::OnMouseWheelMoved(wxMouseEvent& event) {

}
void CanvasWindow::OnMouseLeftDown(wxMouseEvent& event) {
  SetFocus();
}
void CanvasWindow::OnMouseLeftUp(wxMouseEvent& event) {
  SetFocus();
}
void CanvasWindow::OnMouseRightDown(wxMouseEvent& event) {
  SetFocus();
  mouse_right_down_ = true;
}
void CanvasWindow::OnMouseRightUp(wxMouseEvent& event) {
  SetFocus();
  mouse_right_down_ = false;
}
void CanvasWindow::OnMouseLeftWindow(wxMouseEvent& event) {

}

void CanvasWindow::OnKeyPressed(wxKeyEvent& event) {
  const int kc = event.GetKeyCode();

  switch (kc) {
    case WXK_PAGEUP: {
      camera_.SetYMovement(FORWARD);
      break;
    }
    case WXK_PAGEDOWN: {
      camera_.SetYMovement(BACKWARD);
      break;
    }
    case WXK_LEFT: {
      camera_.SetXMovement(BACKWARD);
      break;
    }
    case WXK_RIGHT: {
      camera_.SetXMovement(FORWARD);
      break;
    }
    case WXK_UP: {
      camera_.SetZMovement(BACKWARD);
      break;
    }
    case WXK_DOWN: {
      camera_.SetZMovement(FORWARD);
      break;
    }
    case WXK_BACK: {
      camera_.Reset();
      break;
    }
  }
}

void CanvasWindow::OnKeyReleased(wxKeyEvent& event) {
  const int kc = event.GetKeyCode();

  switch (kc) {
    case WXK_LEFT:
    case WXK_RIGHT: {
      camera_.SetXMovement(NONE);
      camera_.SetZMovement(NONE);
      break;
    }
    case WXK_UP:
    case WXK_DOWN: {
      camera_.SetXMovement(NONE);
      camera_.SetZMovement(NONE);
      break;
    }
  }
  camera_.SetYMovement(NONE);
}

void CanvasWindow::SetupOctree() {
  clock_t begin = std::clock();
  int t_size = 64;

  moctree_ = new moctree::ClassicOctree<int>(t_size);
  moctree_data_ = 1;

  Vector3 p0, p1, p2, bc, sphere;
  p0.x_ = 0;
  p0.y_ = 0;
  p0.z_ = 0;
  p1.x_ = t_size / 4;
  p1.y_ = t_size - 1;
  p1.z_ = t_size - 1;
  p2.x_ = t_size - 1;
  p2.y_ = 0;
  p2.z_ = 0;

  int n_cells = 0;

  for (double t = 0; t <= 1; t += 0.001) {
    bc.x_ = (1 - t) * ((1 - t) * p0.x_ + t * p1.x_)
        + t * ((1 - t) * p1.x_ + t * p2.x_);
    bc.y_ = (1 - t) * ((1 - t) * p0.y_ + t * p1.y_)
        + t * ((1 - t) * p1.y_ + t * p2.y_);
    bc.z_ = (1 - t) * ((1 - t) * p0.z_ + t * p1.z_)
        + t * ((1 - t) * p1.z_ + t * p2.z_);

    int radius_size = 3;
    //for (double r = 0; r < radius_size; r += 1) {
    for (double alpha = 0; alpha < 2 * M_PI; alpha += 0.3) {
      for (double beta = 0; beta < M_PI; beta += 0.3) {
        sphere.x_ = radius_size * cos(alpha) * sin(beta);
        sphere.y_ = radius_size * sin(alpha) * sin(beta);
        sphere.z_ = radius_size * cos(beta);
        moctree_->InsertCell(sphere.x_ + bc.x_, sphere.y_ + bc.y_,
                             sphere.z_ + bc.z_, &moctree_data_);
        n_cells++;
      }
    }
  }

  clock_t end = std::clock();
  printf("Octree created in %f seconds...\n",
         double(end - begin) / CLOCKS_PER_SEC);

}

void CanvasWindow::CreateMesh() {
  clock_t begin = std::clock();
  MarchingCubes* mc = MarchingCubes::CreateMarchingCubes();

  int size = moctree_->size();

  printf("Creating Corners Matrix...\n");
  // +2 == Border
  // Each cell is displaced +1 in each axis
  //bool corners[size + 2][size + 2][size + 2];
  bool ***corners;
  corners = new bool**[size + 2];
  for (int i = 0; i < size + 2; i++) {
    corners[i] = new bool*[size + 2];
    for (int j = 0; j < size + 2; j++) {
      corners[i][j] = new bool[size + 2];
    }
  }
  for (int x = 0; x < size + 2; x++) {
    for (int y = 0; y < size + 2; y++) {
      for (int z = 0; z < size + 2; z++) {
        corners[x][y][z] = false;
      }
    }
  }

  // EACH OCTREE CELL == 1 CORNER!
  moctree::MOctreeCell<int> o_cell = moctree_->GetCell(0, 0, 0);

  int x = 0;
  int y = 0;
  int z = 0;
  int d_x = 1;
  int d_y = 1;

  for (int z = 0; z < size - 1; z++) {
    // if o_cell.z_ is power of two
    /*if (!(((int) (o_cell.z_ - 1)) & (int) (o_cell.z_))) {
      printf("Meshing: (%d/%d)\n", o_cell.z_, size);
    }*/
    while (true) {
      while (true) {
        corners[x + 1][y + 1][z + 1] = o_cell.data_ != NULL;
        x += d_x;
        if (x >= 0 && x < size) {
          o_cell = moctree_->GetNeighbor(o_cell, d_x, 0, 0);
        } else {
          d_x *= -1;
          x += d_x;
          break;
        }
      }
      y += d_y;
      if (y >= 0 && y < size) {
        o_cell = moctree_->GetNeighbor(o_cell, 0, d_y, 0);
      } else {
        d_y *= -1;
        y += d_y;
        break;
      }
    }
    o_cell = moctree_->GetNeighbor(o_cell, 0, 0, 1);
  }

  clock_t end = std::clock();
  printf("Corners Matrix created in %f seconds...\n",
         double(end - begin) / CLOCKS_PER_SEC);

  begin = std::clock();

  // Corners Matrix To Mesh
  for (int z = 0; z < size + 1; z += 1) {
    for (int y = 0; y < size + 1; y += 1) {
      for (int x = 0; x < size + 1; x += 1) {
        MCTemplate *cube = mc->GetTemplate(corners[x][y][z],
                                           corners[x + 1][y][z],
                                           corners[x][y + 1][z],
                                           corners[x + 1][y + 1][z],
                                           corners[x][y][z + 1],
                                           corners[x + 1][y][z + 1],
                                           corners[x][y + 1][z + 1],
                                           corners[x + 1][y + 1][z + 1]);
        if (cube == NULL) {
          /*printf("FUUUUUUUUU %d %d %d %d %d %d %d %d\n", corners[x][y][z],
                 corners[x + 1][y][z], corners[x][y + 1][z],
                 corners[x + 1][y + 1][z], corners[x][y][z + 1],
                 corners[x + 1][y][z + 1], corners[x][y + 1][z + 1],
                 corners[x + 1][y + 1][z + 1]);*/
          continue;
        }
        for (int t_n = 0; t_n < cube->n_triangles_; t_n++) {
          Triangle t = cube->triangles_[t_n];
          t.Translate(x * 1.0, y * 1.0, z * (-1.0));
          mesh_.push_back(t);
        }
      }
    }
  }
  end = std::clock();
  printf("Mesh completed in %f seconds with %d triangles...\n",
         double(end - begin) / CLOCKS_PER_SEC, mesh_.size());
}
/*
 *
 * int c_i = 0;
 for (int c_z = 0; c_z < 2; c_z++) {
 for (int c_y = 0; c_y < 2; c_y++) {
 for (int c_x = 0; c_x < 2; c_x++) {
 int ti = 0;
 MCTemplate *cube = mc->GetTemplate(corners[c_i][ti++],
 corners[c_i][ti++],
 corners[c_i][ti++],
 corners[c_i][ti++],
 corners[c_i][ti++],
 corners[c_i][ti++],
 corners[c_i][ti++],
 corners[c_i][ti++]);
 c_i++;
 for (int t_n = 0; t_n < cube->n_triangles_; t_n++) {
 Triangle t = cube->triangles_[t_n];
 printf("%d %d %d\n", x, y, z);
 t.Translate(-c_x + 0.5, -c_y + 0.5, c_z - 0.5);
 //t.Translate(x * 4, y * 4, z * 4);
 mesh_.push_back(t);
 }
 }
 }
 }
 */
/*
 * wxWidget events link =X
 */  //
BEGIN_EVENT_TABLE(CanvasWindow, wxGLCanvas)
//
EVT_MOUSEWHEEL (CanvasWindow::OnMouseWheelMoved)  //
EVT_MOTION(CanvasWindow::OnMouseMoved)//
EVT_LEFT_DOWN(CanvasWindow::OnMouseLeftDown)//
EVT_LEFT_UP(CanvasWindow::OnMouseLeftUp)//
EVT_RIGHT_DOWN(CanvasWindow::OnMouseRightDown)//
EVT_RIGHT_UP(CanvasWindow::OnMouseRightUp)//
EVT_LEAVE_WINDOW(CanvasWindow::OnMouseLeftWindow)//
EVT_KEY_DOWN(CanvasWindow::OnKeyPressed)//
EVT_KEY_UP(CanvasWindow::OnKeyReleased)//
EVT_PAINT (CanvasWindow::OnPaintit)//
EVT_SIZE(CanvasWindow::OnResized)//
EVT_IDLE(CanvasWindow::OnIdle)//
END_EVENT_TABLE()
//
