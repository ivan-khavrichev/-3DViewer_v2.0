/*!
\file
\brief Заголовочный файл с описанием функций визуализации.

Данный файл содержит в себе определения
функций, используемых в проекте 3DViewer.
*/

#ifndef CPP4_SMARTCALC_V2_3DVIEWER_V2_FRONT_3DVIEWER_H
#define CPP4_SMARTCALC_V2_3DVIEWER_V2_FRONT_3DVIEWER_H

#include <QCloseEvent>
#include <QColorDialog>
#include <QCoreApplication>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QPainter>
#include <QSettings>
#include <QTimer>
#include <QVariant>

#include "../back/3dviewer.h"
#include "QtGifImage/qgifimage.h"
#include "glwidget.h"
#include "numlineedit.h"
#include "sizes.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Viewer3D;
}
QT_END_NAMESPACE

namespace s21 {

class Viewer3D : public QMainWindow {
  Q_OBJECT

 public:
  Viewer3D(QWidget *parent = nullptr);
  ~Viewer3D();
  Sizes *choise_size_;

 protected:
  void closeEvent(QCloseEvent *event);

 private:
  Ui::Viewer3D *ui;
  QOpenGLWidget *Glwidget;

  QColor color_line_ = Qt::white, color_vertice_ = Qt::red,
         color_background_ = QColor(236, 236, 236, 0);
  QString file_name_ = "", path_project_ = "";

  std::string str_file_name_ = "";

  int gif_interval_ = 100;
  double translation_x_ = 0, translation_y_ = 0, translation_z_ = 0,
         rotating_x_ = 0, rotating_y_ = 0, rotating_z_ = 0, scaling_x_ = 100,
         scaling_y_ = 100, scaling_z_ = 100, scaling_all_ = 100;

  Vertex values_ = {0, 0, 0};
  VertexArray vertex_arr_;
  VertexArray vertex_arr_start_;
  Controller controller_;

  QGifImage *gif_ = NULL;
  QTimer *gif_timer_ = NULL;

 private slots:
  void ActionOpenFileTriggered();

  void ActionEdgeTypeSolidTriggered();
  void ActionEdgeTypeDashedTriggered();
  void ActionEdgeThicknessTriggered();
  void ActionEdgeColorTriggered();

  void ActionVerticeTypeNoneTriggered();
  void ActionVerticeTypeCircleTriggered();
  void ActionVerticeTypeSquareTriggered();
  void ActionVerticeSizeTriggered();
  void ActionVerticeColorTriggered();

  void ActionBackgroundTriggered();

  void RadioButtonParallelToggled(bool checked);
  void RadioButtonCentralToggled(bool checked);

  void MoveX();
  void MoveY();
  void MoveZ();

  void RotationX();
  void RotationY();
  void RotationZ();

  void ZoomX();
  void ZoomY();
  void ZoomZ();
  void ZoomAll();

  void LocationChange(double change_x, double change_y, double change_z,
                      Vertex coordinate, TransformationType type);
  void ModelTransformation();

  void ScrollBarTranslationXValueChanged(int value);
  void ScrollBarTranslationYValueChanged(int value);
  void ScrollBarTranslationZValueChanged(int value);

  void DialRotatingXValueChanged(int value);
  void DialRotatingYValueChanged(int value);
  void DialRotatingZValueChanged(int value);

  void SliderScalingXValueChanged(int value);
  void SliderScalingYValueChanged(int value);
  void SliderScalingZValueChanged(int value);
  void SliderScalingValueChanged(int value);

  void CheckBoxTranslatingToggled(bool checked);
  void CheckBoxRotatingToggled(bool checked);
  void CheckBoxScalingToggled(bool checked);

  void FirstOpen();
  void FileOpen();
  void SaveBmp();
  void SaveJpeg();
  void SaveGif();
  void RecordingGif();
  void FinishRecording();

  void SetAllDefault();
  void SetTranslationDefault();
  void SetRotatingDefault();
  void SetScalingDefault();

  void WriteSettings();
  void ReadSettings();
};

}  // namespace s21

#endif  // CPP4_SMARTCALC_V2_3DVIEWER_V2_FRONT_3DVIEWER_H
