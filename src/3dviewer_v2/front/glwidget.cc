/*!
\file
\brief Исходный файл с реализацией функций отрисовки 3D-модели.

Данный файл содержит в себе реализацию
функций, используемых в проекте 3DViewer.
*/

#include "glwidget.h"

namespace s21 {

Glwidget::Glwidget(QWidget *parent) : QOpenGLWidget(parent) { update(); }

void Glwidget::paintGL() {
  Polygon *polyp = polygon_arr_paint_.polygons;
  glEnable(GL_DEPTH_TEST);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  if (project_parallel_ == true) {
    glOrtho(-1, 1, -1, 1, -1, 1);
    glTranslatef(0, 0, 0);
  } else {
    glFrustum(-1, 1, -1, 1, 2, 6);
    glTranslatef(0, 0, -3);
  }

  glClearColor(back_color_.redF(), back_color_.greenF(), back_color_.blueF(),
               0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (point_draw_ == true) {
    if (point_circle_ == true) {
      glEnable(GL_POINT_SMOOTH);
    } else {
      glDisable(GL_POINT_SMOOTH);
    }

    glPointSize(point_size_);
    glColor3d(vertice_color_.redF(), vertice_color_.greenF(),
              vertice_color_.blueF());

    for (int i = 0; i < (int)polygon_arr_paint_.polygon_amount; i++, polyp++) {
      vertex_in_poly_ = 0;
      for (int j = 0;
           j < (int)polygon_arr_paint_.polygons->points_in_polygon_amount;
           j++) {
        vertex_in_poly_ = *(polyp->points + j);
        glBegin(GL_POINTS);
        Vertex *pp = vertex_arr_paint_.vertexes;
        pp += vertex_in_poly_;
        glVertex3d(pp->x, pp->y, pp->z);
      }
      glEnd();
    }
  }

  polyp = polygon_arr_paint_.polygons;

  if (line_dashed_ == true) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00ff);
  } else {
    glDisable(GL_LINE_STIPPLE);
  }

  glLineWidth(line_size_);
  glColor3d(line_color_.redF(), line_color_.greenF(), line_color_.blueF());

  for (int i = 1; i <= (int)polygon_arr_paint_.polygon_amount; i++, polyp++) {
    vertex_in_poly_ = 0;
    for (int j = 0;
         j < (int)polygon_arr_paint_.polygons->points_in_polygon_amount; j++) {
      vertex_in_poly_ = *(polyp->points + j);
      glBegin(GL_LINE_LOOP);
      Vertex *pp = vertex_arr_paint_.vertexes;
      pp += vertex_in_poly_;
      glVertex3d(pp->x, pp->y, pp->z);
    }
    glEnd();
  }
}

}  // namespace s21
