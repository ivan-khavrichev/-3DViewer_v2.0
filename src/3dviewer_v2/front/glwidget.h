/*!
\file
\brief Заголовочный файл с объявлением функций отрисовки 3D-модели.

Данный файл содержит в себе объявление
функций, используемых в проекте 3DViewer.
*/

#ifndef CPP4_SMARTCALC_V2_3DVIEWER_V2_FRONT_GLWIDJET_H
#define CPP4_SMARTCALC_V2_3DVIEWER_V2_FRONT_GLWIDJET_H

#define GL_SILENCE_DEPRECATION

#include <QOpenGLWidget>

#include "3dviewer.h"

namespace s21 {

class Glwidget : public QOpenGLWidget {
  Q_OBJECT

 public:
  Glwidget(QWidget *parent = nullptr);

  int vertex_in_poly_ = 0, line_dashed_ = false, point_draw_ = false,
      point_circle_ = true, point_size_ = 2, line_size_ = 3,
      project_parallel_ = false;

  QColor back_color_ = QColor(236, 236, 236, 0), line_color_ = Qt::black,
         vertice_color_ = Qt::red;

  VertexArray vertex_arr_paint_;
  PolygonArray polygon_arr_paint_;

  void paintGL();
};

}  // namespace s21

#endif  // CPP4_SMARTCALC_V2_3DVIEWER_V2_FRONT_GLWIDJET_H
