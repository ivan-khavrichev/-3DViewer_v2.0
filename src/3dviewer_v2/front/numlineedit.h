/*!
\file
\brief Заголовочный файл с объявлением функций класса объекта поля ввода.

Данный файл содержит в себе объявление
функций, используемых в проекте 3DViewer.
*/

#ifndef CPP4_SMARTCALC_V2_3DVIEWER_V2_FRONT_NUMLINEEDIT_H
#define CPP4_SMARTCALC_V2_3DVIEWER_V2_FRONT_NUMLINEEDIT_H

#include <QInputDialog>
#include <QKeyEvent>
#include <QLineEdit>
#include <QWidget>

namespace s21 {

class Numlineedit : public QLineEdit {
  Q_OBJECT

 public:
  Numlineedit(QWidget *parent = nullptr);

 protected:
  void keyPressEvent(QKeyEvent *event) override {
    int key_ = event->key();
    if ((key_ >= Qt::Key_0 && key_ <= Qt::Key_9) || key_ == Qt::Key_Period ||
        key_ == Qt::Key_Backspace || key_ == Qt::Key_Left ||
        key_ == Qt::Key_Right || key_ == Qt::Key_Enter || key_ == Qt::Key_Minus)
      QLineEdit::keyPressEvent(event);
  };
};

}  // namespace s21

#endif  // CPP4_SMARTCALC_V2_3DVIEWER_V2_FRONT_NUMLINEEDIT_H
