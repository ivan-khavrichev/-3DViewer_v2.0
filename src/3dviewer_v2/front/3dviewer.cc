/*!
\file
\brief Исходный файл с реализацией функций визуализации.

Данный файл содержит в себе реализацию
функций, используемых в проекте 3DViewer.
*/

#include "3dviewer.h"

#include "./ui_3dviewer.h"
#include "glwidget.h"
#include "sizes.h"

namespace s21 {

Viewer3D::Viewer3D(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Viewer3D) {
  ui->setupUi(this);

  choise_size_ = new Sizes();

  connect(ui->lineEdit_scaling_x, SIGNAL(textChanged(QString)), this,
          SLOT(ZoomX()));
  connect(ui->lineEdit_scaling_y, SIGNAL(textChanged(QString)), this,
          SLOT(ZoomY()));
  connect(ui->lineEdit_scaling_z, SIGNAL(textChanged(QString)), this,
          SLOT(ZoomZ()));
  connect(ui->lineEdit_scaling, SIGNAL(textChanged(QString)), this,
          SLOT(ZoomAll()));

  connect(ui->lineEdit_rotating_x, SIGNAL(textChanged(QString)), this,
          SLOT(RotationX()));
  connect(ui->lineEdit_rotating_y, SIGNAL(textChanged(QString)), this,
          SLOT(RotationY()));
  connect(ui->lineEdit_rotating_z, SIGNAL(textChanged(QString)), this,
          SLOT(RotationZ()));

  connect(ui->lineEdit_translating_x, SIGNAL(textChanged(QString)), this,
          SLOT(MoveX()));
  connect(ui->lineEdit_translating_y, SIGNAL(textChanged(QString)), this,
          SLOT(MoveY()));
  connect(ui->lineEdit_translating_z, SIGNAL(textChanged(QString)), this,
          SLOT(MoveZ()));

  connect(ui->actionOpenFile, SIGNAL(triggered()), this,
          SLOT(ActionOpenFileTriggered()));
  connect(ui->actionFormat_bmp, SIGNAL(triggered()), this, SLOT(SaveBmp()));
  connect(ui->pushButton_save_bmp, SIGNAL(clicked()), this, SLOT(SaveBmp()));
  connect(ui->actionFormat_jpeg, SIGNAL(triggered()), this, SLOT(SaveJpeg()));
  connect(ui->pushButton_save_jpeg, SIGNAL(clicked()), this, SLOT(SaveJpeg()));
  connect(ui->actionFormat_gif, SIGNAL(triggered()), this, SLOT(SaveGif()));
  connect(ui->pushButton_save_gif, SIGNAL(clicked()), this, SLOT(SaveGif()));

  connect(ui->actionEdgeTypeSolid, SIGNAL(triggered()), this,
          SLOT(ActionEdgeTypeSolidTriggered()));
  connect(ui->actionEdgeTypeDashed, SIGNAL(triggered()), this,
          SLOT(ActionEdgeTypeDashedTriggered()));
  connect(ui->actionEdgeThickness, SIGNAL(triggered()), this,
          SLOT(ActionEdgeThicknessTriggered()));
  connect(ui->actionEdgeColor, SIGNAL(triggered()), this,
          SLOT(ActionEdgeColorTriggered()));

  connect(ui->actionVerticeTypeNone, SIGNAL(triggered()), this,
          SLOT(ActionVerticeTypeNoneTriggered()));
  connect(ui->actionVerticeTypeCircle, SIGNAL(triggered()), this,
          SLOT(ActionVerticeTypeCircleTriggered()));
  connect(ui->actionVerticeTypeSquare, SIGNAL(triggered()), this,
          SLOT(ActionVerticeTypeSquareTriggered()));
  connect(ui->actionVerticeSize, SIGNAL(triggered()), this,
          SLOT(ActionVerticeSizeTriggered()));
  connect(ui->actionVerticeColor, SIGNAL(triggered()), this,
          SLOT(ActionVerticeColorTriggered()));

  connect(ui->actionBackground, SIGNAL(triggered()), this,
          SLOT(ActionBackgroundTriggered()));

  connect(ui->RadioButtonParallel, SIGNAL(toggled(bool)), this,
          SLOT(RadioButtonParallelToggled(bool)));
  connect(ui->RadioButtonCentral, SIGNAL(toggled(bool)), this,
          SLOT(RadioButtonCentralToggled(bool)));

  connect(ui->CheckBoxTranslating, SIGNAL(toggled(bool)), this,
          SLOT(CheckBoxTranslatingToggled(bool)));
  connect(ui->CheckBoxRotating, SIGNAL(toggled(bool)), this,
          SLOT(CheckBoxRotatingToggled(bool)));
  connect(ui->CheckBoxScaling, SIGNAL(toggled(bool)), this,
          SLOT(CheckBoxScalingToggled(bool)));

  connect(ui->ScrollBarTranslationX, SIGNAL(valueChanged(int)), this,
          SLOT(ScrollBarTranslationXValueChanged(int)));
  connect(ui->ScrollBarTranslationY, SIGNAL(valueChanged(int)), this,
          SLOT(ScrollBarTranslationYValueChanged(int)));
  connect(ui->ScrollBarTranslationZ, SIGNAL(valueChanged(int)), this,
          SLOT(ScrollBarTranslationZValueChanged(int)));

  connect(ui->DialRotatingX, SIGNAL(valueChanged(int)), this,
          SLOT(DialRotatingXValueChanged(int)));
  connect(ui->DialRotatingY, SIGNAL(valueChanged(int)), this,
          SLOT(DialRotatingYValueChanged(int)));
  connect(ui->DialRotatingZ, SIGNAL(valueChanged(int)), this,
          SLOT(DialRotatingZValueChanged(int)));

  connect(ui->SliderScaling, SIGNAL(valueChanged(int)), this,
          SLOT(SliderScalingValueChanged(int)));
  connect(ui->SliderScalingX, SIGNAL(valueChanged(int)), this,
          SLOT(SliderScalingXValueChanged(int)));
  connect(ui->SliderScalingY, SIGNAL(valueChanged(int)), this,
          SLOT(SliderScalingYValueChanged(int)));
  connect(ui->SliderScalingZ, SIGNAL(valueChanged(int)), this,
          SLOT(SliderScalingZValueChanged(int)));

  ReadSettings();
}

Viewer3D::~Viewer3D() { delete ui; }

void Viewer3D::ActionOpenFileTriggered() {
  file_name_ = QFileDialog::getOpenFileName(this, "Открыть файл",
                                            path_project_.append("src/models/"),
                                            "Files (*.obj)");
  if (!file_name_.isEmpty()) {
    FileOpen();
  }
}

void Viewer3D::ActionEdgeTypeSolidTriggered() {
  ui->openGLWidget->line_dashed_ = false;
  ui->openGLWidget->update();
}

void Viewer3D::ActionEdgeTypeDashedTriggered() {
  ui->openGLWidget->line_dashed_ = true;
  ui->openGLWidget->update();
}

void Viewer3D::ActionEdgeThicknessTriggered() {
  choise_size_->setModal(true);
  choise_size_->setWindowTitle("Sizes");
  if (choise_size_->exec() == QDialog::Accepted) {
    ui->openGLWidget->line_size_ = choise_size_->size_;
  }
}

void Viewer3D::ActionEdgeColorTriggered() {
  color_line_ = QColorDialog::getColor();
  if (color_line_.isValid()) {
    ui->openGLWidget->line_color_ = color_line_;
  }
  ui->openGLWidget->update();
}

void Viewer3D::ActionVerticeTypeNoneTriggered() {
  ui->openGLWidget->point_draw_ = false;
  ui->openGLWidget->update();
}

void Viewer3D::ActionVerticeTypeCircleTriggered() {
  ui->openGLWidget->point_draw_ = true;
  ui->openGLWidget->point_circle_ = true;
  ui->openGLWidget->update();
}

void Viewer3D::ActionVerticeTypeSquareTriggered() {
  ui->openGLWidget->point_draw_ = true;
  ui->openGLWidget->point_circle_ = false;
  ui->openGLWidget->update();
}

void Viewer3D::ActionVerticeSizeTriggered() {
  choise_size_->setModal(true);
  choise_size_->setWindowTitle("Sizes");
  if (choise_size_->exec() == QDialog::Accepted) {
    ui->openGLWidget->point_size_ = choise_size_->size_;
  }
}

void Viewer3D::ActionVerticeColorTriggered() {
  color_vertice_ = QColorDialog::getColor();
  if (color_vertice_.isValid()) {
    ui->openGLWidget->vertice_color_ = color_vertice_;
  }
  ui->openGLWidget->update();
}

void Viewer3D::ActionBackgroundTriggered() {
  color_background_ = QColorDialog::getColor();
  if (color_background_.isValid()) {
    ui->openGLWidget->back_color_ = color_background_;
  }
  ui->openGLWidget->update();
}

void Viewer3D::RadioButtonParallelToggled(bool checked) {
  ui->openGLWidget->project_parallel_ = checked;
  ui->openGLWidget->update();
}

void Viewer3D::RadioButtonCentralToggled(bool checked) {
  ui->openGLWidget->project_parallel_ = -1 * checked;
  ui->openGLWidget->update();
}

void Viewer3D::MoveX() {
  translation_x_ = ui->lineEdit_translating_x->text().toDouble();
  ModelTransformation();
}

void Viewer3D::ScrollBarTranslationXValueChanged(int value) {
  translation_x_ = value;
  ModelTransformation();
}

void Viewer3D::MoveY() {
  translation_y_ = ui->lineEdit_translating_y->text().toDouble();
  ModelTransformation();
}

void Viewer3D::ScrollBarTranslationYValueChanged(int value) {
  translation_y_ = value;
  ModelTransformation();
}

void Viewer3D::MoveZ() {
  translation_z_ = ui->lineEdit_translating_z->text().toDouble();
  ModelTransformation();
}

void Viewer3D::ScrollBarTranslationZValueChanged(int value) {
  translation_z_ = value;
  ModelTransformation();
}

void Viewer3D::RotationX() {
  rotating_x_ = ui->lineEdit_rotating_x->text().toDouble() * 100;
  ModelTransformation();
}

void Viewer3D::DialRotatingXValueChanged(int value) {
  rotating_x_ = -100 * value;
  ModelTransformation();
}

void Viewer3D::RotationY() {
  rotating_y_ = ui->lineEdit_rotating_y->text().toDouble() * 100;
  ModelTransformation();
}

void Viewer3D::DialRotatingYValueChanged(int value) {
  rotating_y_ = -100 * value;
  ModelTransformation();
}

void Viewer3D::RotationZ() {
  rotating_z_ = ui->lineEdit_rotating_z->text().toDouble() * 100;
  ModelTransformation();
}

void Viewer3D::DialRotatingZValueChanged(int value) {
  rotating_z_ = -100 * value;
  ModelTransformation();
}

void Viewer3D::ZoomX() {
  scaling_x_ = ui->lineEdit_scaling_x->text().toDouble() * 100;
  ModelTransformation();
}

void Viewer3D::SliderScalingXValueChanged(int value) {
  scaling_x_ = value;
  ModelTransformation();
}

void Viewer3D::ZoomY() {
  scaling_y_ = ui->lineEdit_scaling_y->text().toDouble() * 100;
  ModelTransformation();
}

void Viewer3D::SliderScalingYValueChanged(int value) {
  scaling_y_ = value;
  ModelTransformation();
}

void Viewer3D::ZoomZ() {
  scaling_z_ = ui->lineEdit_scaling_z->text().toDouble() * 100;
  ModelTransformation();
}

void Viewer3D::SliderScalingZValueChanged(int value) {
  scaling_z_ = value;
  ModelTransformation();
}

void Viewer3D::ZoomAll() {
  scaling_x_ = scaling_y_ = scaling_z_ =
      ui->lineEdit_scaling->text().toDouble() * 100;
  ModelTransformation();
}

void Viewer3D::SliderScalingValueChanged(int value) {
  scaling_x_ = scaling_y_ = scaling_z_ = scaling_all_ = value;
  ModelTransformation();
}

void Viewer3D::LocationChange(double change_x, double change_y, double change_z,
                              Vertex coordinate, TransformationType type) {
  coordinate.x = change_x / 100;
  coordinate.y = change_y / 100;
  coordinate.z = change_z / 100;
  controller_.Transformation(type, coordinate);
  ui->openGLWidget->vertex_arr_paint_ = controller_.GetVertexArray();
}

void Viewer3D::ModelTransformation() {
  for (size_t i = 0; i < vertex_arr_start_.vertex_amount; i++) {
    vertex_arr_.vertexes[i].x = vertex_arr_start_.vertexes[i].x;
    vertex_arr_.vertexes[i].y = vertex_arr_start_.vertexes[i].y;
    vertex_arr_.vertexes[i].z = vertex_arr_start_.vertexes[i].z;
  }

  LocationChange(scaling_x_, scaling_y_, scaling_z_, values_,
                 TransformationType::Scaling);
  LocationChange(translation_x_, translation_y_, translation_z_, values_,
                 TransformationType::Translation);
  LocationChange(rotating_x_, rotating_y_, rotating_z_, values_,
                 TransformationType::Rotation);

  ui->openGLWidget->update();
}

void Viewer3D::CheckBoxTranslatingToggled(bool checked) {
  if (checked == true) {
    translation_x_ = translation_y_ = translation_z_ = 0;
    SetTranslationDefault();
    ModelTransformation();
  }
}

void Viewer3D::CheckBoxRotatingToggled(bool checked) {
  if (checked == true) {
    rotating_x_ = rotating_y_ = rotating_z_ = 0;
    SetTranslationDefault();
    ModelTransformation();
  }
}

void Viewer3D::CheckBoxScalingToggled(bool checked) {
  if (checked == true) {
    scaling_x_ = scaling_y_ = scaling_z_ = 100;
    SetScalingDefault();
    ModelTransformation();
  }
}

void Viewer3D::SetAllDefault() {
  SetTranslationDefault();
  SetRotatingDefault();
  SetScalingDefault();

  ui->CheckBoxTranslating->setChecked(false);
  ui->CheckBoxRotating->setChecked(false);
  ui->CheckBoxScaling->setChecked(false);
}

void Viewer3D::SetTranslationDefault() {
  ui->lineEdit_translating_x->setText("");
  ui->lineEdit_translating_y->setText("");
  ui->lineEdit_translating_z->setText("");

  ui->ScrollBarTranslationX->setValue(0);
  ui->ScrollBarTranslationY->setValue(0);
  ui->ScrollBarTranslationZ->setValue(0);
}

void Viewer3D::SetRotatingDefault() {
  ui->lineEdit_rotating_x->setText("");
  ui->lineEdit_rotating_y->setText("");
  ui->lineEdit_rotating_z->setText("");

  ui->DialRotatingX->setValue(0);
  ui->DialRotatingY->setValue(0);
  ui->DialRotatingZ->setValue(0);
}

void Viewer3D::SetScalingDefault() {
  ui->lineEdit_scaling_x->setText("");
  ui->lineEdit_scaling_y->setText("");
  ui->lineEdit_scaling_z->setText("");
  ui->lineEdit_scaling->setText("");

  ui->SliderScalingX->setValue(100);
  ui->SliderScalingY->setValue(100);
  ui->SliderScalingZ->setValue(100);
  ui->SliderScaling->setValue(100);
}

void Viewer3D::WriteSettings() {
  QSettings settings("Soft1", "3DViewer_v2");

  settings.beginGroup("3DViewer");

  settings.setValue("file_name_", file_name_);
  settings.setValue("path_project_", path_project_);

  settings.setValue("start_scaling", ui->CheckBoxScaling->isChecked());
  settings.setValue("start_rotating", ui->CheckBoxRotating->isChecked());
  settings.setValue("start_translating", ui->CheckBoxTranslating->isChecked());

  settings.setValue("lineEdit_scaling", ui->lineEdit_scaling->text());
  settings.setValue("scaling_all_", scaling_all_);

  settings.setValue("lineEdit_scaling_x", ui->lineEdit_scaling_x->text());
  settings.setValue("scaling_x_", scaling_x_);
  settings.setValue("lineEdit_scaling_y", ui->lineEdit_scaling_y->text());
  settings.setValue("scaling_y_", scaling_y_);
  settings.setValue("lineEdit_scaling_z", ui->lineEdit_scaling_z->text());
  settings.setValue("scaling_z_", scaling_z_);

  settings.setValue("lineEdit_rotating_x", ui->lineEdit_rotating_x->text());
  settings.setValue("rotating_x_", rotating_x_);
  settings.setValue("lineEdit_rotating_y", ui->lineEdit_rotating_y->text());
  settings.setValue("rotating_y_", rotating_y_);
  settings.setValue("lineEdit_rotating_z", ui->lineEdit_rotating_z->text());
  settings.setValue("rotating_z_", rotating_z_);

  settings.setValue("lineEdit_translation_x",
                    ui->lineEdit_translating_x->text());
  settings.setValue("translation_x_", translation_x_);
  settings.setValue("lineEdit_translation_y",
                    ui->lineEdit_translating_y->text());
  settings.setValue("translation_y_", translation_y_);
  settings.setValue("lineEdit_translation_z",
                    ui->lineEdit_translating_z->text());
  settings.setValue("translation_z_", translation_z_);

  settings.endGroup();

  settings.beginGroup("Glwidget");

  settings.setValue("line_dashed_", ui->openGLWidget->line_dashed_);
  settings.setValue("line_size_", ui->openGLWidget->line_size_);
  settings.setValue("line_color_", ui->openGLWidget->line_color_);

  settings.setValue("point_draw_", ui->openGLWidget->point_draw_);
  settings.setValue("point_circle_", ui->openGLWidget->point_circle_);
  settings.setValue("point_size_", ui->openGLWidget->point_size_);
  settings.setValue("vertice_color_", ui->openGLWidget->vertice_color_);

  settings.setValue("back_color_", ui->openGLWidget->back_color_);

  settings.setValue("project_parallel_", ui->openGLWidget->project_parallel_);

  settings.endGroup();
}

void Viewer3D::ReadSettings() {
  QSettings settings("Soft1", "3DViewer_v2");

  settings.beginGroup("Glwidget");

  ui->openGLWidget->line_dashed_ = settings.value("line_dashed_").toInt();
  ui->openGLWidget->line_size_ = settings.value("line_size_").toInt();
  ui->openGLWidget->line_color_ = settings.value("line_color_").value<QColor>();

  ui->openGLWidget->point_draw_ = settings.value("point_draw_").toInt();
  ui->openGLWidget->point_circle_ = settings.value("point_circle_").toInt();
  ui->openGLWidget->point_size_ = settings.value("point_size_").toInt();
  ui->openGLWidget->vertice_color_ =
      settings.value("vertice_color_").value<QColor>();

  ui->openGLWidget->back_color_ = settings.value("back_color_").value<QColor>();

  ui->openGLWidget->project_parallel_ =
      settings.value("project_parallel_").toInt();

  settings.endGroup();

  settings.beginGroup("3DViewer");

  file_name_ = settings.value("file_name_").value<QString>();
  path_project_ = settings.value("path_project_").value<QString>();
  if (file_name_.isEmpty()) {
    FirstOpen();
  } else {
    FileOpen();
  }

  ui->CheckBoxScaling->setChecked(settings.value("start_scaling").toBool());
  ui->CheckBoxRotating->setChecked(settings.value("start_rotating").toBool());
  ui->CheckBoxTranslating->setChecked(
      settings.value("start_translating").toBool());

  scaling_all_ = settings.value("scaling_all_").toDouble();

  if (scaling_all_ != 0) {
    ui->lineEdit_scaling->setText(
        settings.value("lineEdit_scaling").toString());
    ui->SliderScaling->setValue(settings.value("scaling_all_").toInt());
    ui->lineEdit_scaling_x->setText(
        settings.value("lineEdit_scaling_x").toString());
    ui->SliderScalingX->setValue(settings.value("scaling_x_").toInt());
    ui->lineEdit_scaling_y->setText(
        settings.value("lineEdit_scaling_y").toString());
    ui->SliderScalingY->setValue(settings.value("scaling_y_").toInt());
    ui->lineEdit_scaling_z->setText(
        settings.value("lineEdit_scaling_z_").toString());
    ui->SliderScalingZ->setValue(settings.value("scaling_z_").toInt());
  } else {
    ui->SliderScaling->setValue(100);
    ui->SliderScalingX->setValue(100);
    ui->SliderScalingY->setValue(100);
    ui->SliderScalingZ->setValue(100);
  }

  ui->lineEdit_rotating_x->setText(
      settings.value("lineEdit_rotating_x").toString());
  ui->DialRotatingX->setValue(settings.value("rotating_x_").toInt() / -100);
  ui->lineEdit_rotating_y->setText(
      settings.value("lineEdit_rotating_y").toString());
  ui->DialRotatingY->setValue(settings.value("rotating_y_").toInt() / -100);
  ui->lineEdit_rotating_z->setText(
      settings.value("lineEdit_rotating_z").toString());
  ui->DialRotatingZ->setValue(settings.value("rotating_z_").toInt() / -100);

  ui->lineEdit_translating_x->setText(
      settings.value("lineEdit_translation_x").toString());
  ui->ScrollBarTranslationX->setValue(settings.value("translation_x_").toInt());
  ui->lineEdit_translating_y->setText(
      settings.value("lineEdit_translation_y").toString());
  ui->ScrollBarTranslationY->setValue(settings.value("translation_y_").toInt());
  ui->lineEdit_translating_z->setText(
      settings.value("lineEdit_translation_z").toString());
  ui->ScrollBarTranslationZ->setValue(settings.value("translation_z_").toInt());

  settings.endGroup();
}

void Viewer3D::closeEvent(QCloseEvent *event) {
  QMessageBox save_settings;
  QAbstractButton *yes = save_settings.addButton("Да", QMessageBox::YesRole);
  QAbstractButton *no = save_settings.addButton("Нет", QMessageBox::NoRole);
  save_settings.setText("Сохранить настройки?");
  save_settings.exec();
  if (save_settings.clickedButton() == yes) {
    WriteSettings();
    event->accept();
  } else if (save_settings.clickedButton() == no) {
    SetAllDefault();
    event->accept();
  }
}

void Viewer3D::FirstOpen() {
  std::string absolute_path = QDir::currentPath().toStdString();

  int index_find = absolute_path.find("src", 0);

  path_project_ = QString::fromStdString(absolute_path.erase(index_find));

  absolute_path.append("src/models/cube.obj");

  file_name_ = QString::fromStdString(absolute_path);
  ui->openGLWidget->back_color_ = QColor(236, 236, 236, 0);

  if (file_name_.isNull() == false) {
    FileOpen();
  }
}

void Viewer3D::FileOpen() {
  QByteArray ba = file_name_.toLocal8Bit();
  str_file_name_ = ba.data();

  controller_.ReadObjFile(str_file_name_);

  if (controller_.GetReadingResult() == true) {
    ui->openGLWidget->vertex_arr_paint_ = controller_.GetVertexArrayStart();
    ui->openGLWidget->polygon_arr_paint_ = controller_.GetPolygonArray();
    ui->openGLWidget->update();

    ui->label_file->setText(QFileInfo(file_name_).fileName());
    ui->label_number_vertices->setText(
        QString::number(controller_.GetPointsAmount()));
    ui->label_number_edges->setText(
        QString::number(controller_.GetEdgesAmount()));

    SetAllDefault();
  }
}

void Viewer3D::SaveBmp() {
  QPixmap screen_bmp = ui->openGLWidget->grab();
  QImage bmp = screen_bmp.toImage();
  QPainter painter(&bmp);
  ui->openGLWidget->render(&painter);
  painter.end();
  QString path_bmp = QFileDialog::getSaveFileName(
      this, "Save screen", path_project_.append("src/"), "Images (*.bmp)");
  if (path_bmp.isNull() == false) {
    bmp.save(path_bmp, "BMP");
  }
}

void Viewer3D::SaveJpeg() {
  QPixmap screen_jpeg = ui->openGLWidget->grab();
  QImage jpeg = screen_jpeg.toImage();
  QPainter painter(&jpeg);
  ui->openGLWidget->render(&painter);
  painter.end();
  QString path_jpeg = QFileDialog::getSaveFileName(
      this, "Save screen", path_project_.append("src/"), "Images (*.jpeg)");
  if (path_jpeg.isNull() == false) {
    jpeg.save(path_jpeg, "JPEG");
  }
}

void Viewer3D::SaveGif() {
  gif_ = new QGifImage();
  gif_timer_ = new QTimer(this);
  gif_->setDefaultDelay(gif_interval_);
  connect(gif_timer_, SIGNAL(timeout()), this, SLOT(RecordingGif()));
  gif_timer_->start(gif_interval_);
  QTimer::singleShot(5000, this, SLOT(FinishRecording()));
}

void Viewer3D::RecordingGif() {
  QImage frame = ui->openGLWidget->grab().toImage();
  gif_->addFrame(frame, gif_interval_);
}

void Viewer3D::FinishRecording() {
  gif_timer_->stop();
  QString path_gif = QFileDialog::getSaveFileName(
      this, "Save screen", path_project_.append("src/"), "Images (*.gif)");
  if (path_gif.isNull() == false) {
    gif_->save(path_gif);
  }
}

}  // namespace s21
