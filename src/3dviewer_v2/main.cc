#include <QApplication>

#include "front/3dviewer.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  QLocale::setDefault(QLocale::c());

  s21::Viewer3D w;
  w.show();
  return a.exec();
}
