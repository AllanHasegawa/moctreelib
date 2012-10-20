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
#include <stdio.h>

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
    light_diffuse_pos_[0] = 15.f;
    light_diffuse_pos_[0] = 0.f;
    light_diffuse_pos_[0] = 1.f;

    glClearColor(0.f, 0.f, 0.f, 1.0f);

    glClearDepth(1.0);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient_);
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

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  //glRotatef(rot_, 0.0f, 1.0f, 0.0f);
  MarchingCubes* mc = MarchingCubes::CreateMarchingCubes();
  mc->GetTemplate(0, 0, 0, 0, 0, 0, 1, 0)->Render();
  mc->GetTemplate(0, 0, 0, 0, 0, 1, 0, 0)->Render();
  mc->GetTemplate(0, 0, 1, 0, 0, 0, 0, 0)->Render();
  mc->GetTemplate(0, 0, 0, 0, 0, 0, 0, 0)->Render();

  /*for (std::vector<Triangle>::iterator i = mesh_.begin(); i != mesh_.end();
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
                 100.0f);

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
  moctree_ = new moctree::ClassicOctree<int>(16);
  moctree_data_ = 1;

  for (int z = 0; z < 2; z++) {
    for (int y = 0; y < 2; y++) {
      for (int x = 0; x < 2; x++) {
        moctree_->InsertCell(x, y, z, &moctree_data_);
      }
    }
  }
}

void CanvasWindow::CreateMesh() {
  MarchingCubes* mc = MarchingCubes::CreateMarchingCubes();

  int size = 16;
  bool corners[8][8];

  for (int z = 0; z < size; z += 2) {
    for (int y = 0; y < size; y += 2) {
      for (int x = 0; x < size; x += 2) {
        printf("Meshing: %d/%d/%d\n", x, y, z);
        moctree::MOctreeCell<int> c = moctree_->GetCell(x, y, z);
        if (c.data_ == NULL) {
          continue;
        }

        // all corners belongs to the "outside"
        for (int i = 0; i < 8; i++) {
          for (int j = 0; j < 8; j++) {
            corners[i][j] = false;
          }
        }
        // center corners belongs to the "inside"
        for (int i = 0; i < 8; i++) {
          corners[i][7 - i] = true;
        }

        for (int n_z = 1; n_z > -2; n_z--) {
          for (int n_y = -1; n_y < 2; n_y++) {
            for (int n_x = -1; n_x < 2; n_x++) {
              if (n_z == 0 && n_y == 0 && n_x == 0) {
                continue;
              }
              moctree::MOctreeCell<int> n_c;
              try {
                n_c = moctree_->GetNeighbor(c, x + n_x, y + n_y, z + n_z);
                if (n_c.data_ == NULL) {
                  continue;
                }

                if (n_z == 1) {
                  if (n_y == -1) {
                    if (n_x == -1) {
                      corners[0][0] = true;
                    } else if (n_x == 0) {
                      corners[0][1] = true;
                      corners[1][0] = true;
                    } else if (n_x == 1) {
                      corners[1][0] = true;
                    }
                  } else if (n_y == 0) {
                    if (n_x == -1) {
                      corners[0][2] = true;
                      corners[2][0] = true;
                    } else if (n_x == 0) {
                      corners[0][3] = true;
                      corners[1][2] = true;
                      corners[2][1] = true;
                      corners[3][0] = true;
                    } else if (n_x == 1) {
                      corners[1][3] = true;
                      corners[3][1] = true;
                    }
                  } else if (n_y == 1) {
                    if (n_x == -1) {
                      corners[2][2] = true;
                    } else if (n_x == 0) {
                      corners[2][3] = true;
                      corners[3][2] = true;
                    } else if (n_x == 1) {
                      corners[3][3] = true;
                    }
                  }  // n_z == 1
                } else if (n_z == 0) {
                  if (n_y == -1) {
                    if (n_x == -1) {
                      corners[0][4] = true;
                      corners[4][0] = true;
                    } else if (n_x == 0) {
                      corners[0][5] = true;
                      corners[1][4] = true;
                      corners[4][1] = true;
                      corners[5][0] = true;
                    } else if (n_x == 1) {
                      corners[1][5] = true;
                      corners[5][1] = true;
                    }
                  } else if (n_y == 0) {
                    if (n_x == -1) {
                      corners[0][6] = true;
                      corners[2][4] = true;
                      corners[4][2] = true;
                      corners[6][0] = true;
                    } else if (n_x == 0) {
                      //corners[0][1] = true;
                      //corners[1][0] = true;
                    } else if (n_x == 1) {
                      corners[1][7] = true;
                      corners[3][5] = true;
                      corners[5][3] = true;
                      corners[7][1] = true;
                    }
                  } else if (n_y == 1) {
                    if (n_x == -1) {
                      corners[2][6] = true;
                      corners[6][2] = true;
                    } else if (n_x == 0) {
                      corners[2][7] = true;
                      corners[3][6] = true;
                      corners[6][3] = true;
                      corners[7][2] = true;
                    } else if (n_x == 1) {
                      corners[3][7] = true;
                      corners[7][3] = true;
                    }
                  }  // n_z == 0
                } else if (n_z == -1) {
                  if (n_y == -1) {
                    if (n_x == -1) {
                      corners[4][4] = true;
                    } else if (n_x == 0) {
                      corners[4][1] = true;
                      corners[5][0] = true;
                    } else if (n_x == 1) {
                      corners[5][1] = true;
                    }
                  } else if (n_y == 0) {
                    if (n_x == -1) {
                      corners[4][6] = true;
                      corners[6][4] = true;
                    } else if (n_x == 0) {
                      corners[4][7] = true;
                      corners[5][6] = true;
                      corners[6][5] = true;
                      corners[7][4] = true;
                    } else if (n_x == 1) {
                      corners[5][7] = true;
                      corners[7][5] = true;
                    }
                  } else if (n_y == 1) {
                    if (n_x == -1) {
                      corners[6][6] = true;
                    } else if (n_x == 0) {
                      corners[6][7] = true;
                      corners[7][6] = true;
                    } else if (n_x == 1) {
                      corners[7][7] = true;
                    }
                  }
                }
                int c_i = 0;
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
                        t.Translate(c_x - 0.5, c_y - 0.5, -c_z + 0.5);
                        //t.Translate(x * 4, y * 4, z * 4);
                        mesh_.push_back(t);
                      }
                    }
                  }
                }
              } catch (std::exception& e) {
              }
            }
          }
        }

      }
    }
  }
}
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
