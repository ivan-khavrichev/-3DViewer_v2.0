/*!
\file
\brief Исходный файл с реализацией функций класса окна выбора размера.

Данный файл содержит в себе реализацию
функций, используемых в проекте 3DViewer.
*/

#include "sizes.h"

#include "ui_sizes.h"

namespace s21 {

Sizes::Sizes(QWidget *parent) : QDialog(parent), ui(new Ui::Sizes) {
  ui->setupUi(this);

  connect(ui->SliderSize, SIGNAL(valueChanged(int)), this,
          SLOT(SliderSizeValueChanged(int)));
}

Sizes::~Sizes() { delete ui; }

void Sizes::SliderSizeValueChanged(int value) {
  size_ = value;
  ui->label_size_value->setText("Величина: " + QString::number(value));
}

}  // namespace s21
