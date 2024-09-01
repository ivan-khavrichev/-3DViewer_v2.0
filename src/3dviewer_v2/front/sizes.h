/*!
\file
\brief Заголовочный файл с объявлением функций класса окна выбора размера.

Данный файл содержит в себе объявление
функций, используемых в проекте 3DViewer.
*/

#ifndef CPP4_SMARTCALC_V2_3DVIEWER_V2_FRONT_SIZES_H
#define CPP4_SMARTCALC_V2_3DVIEWER_V2_FRONT_SIZES_H

#include <QAbstractButton>
#include <QDialog>

namespace Ui {
class Sizes;
}

namespace s21 {

class Sizes : public QDialog {
  Q_OBJECT

 public:
  explicit Sizes(QWidget *parent = nullptr);
  ~Sizes();
  Ui::Sizes *ui;
  int size_;

 private slots:

  void SliderSizeValueChanged(int value);
};

}  // namespace s21

#endif  // CPP4_SMARTCALC_V2_3DVIEWER_V2_FRONT_SIZES_H
