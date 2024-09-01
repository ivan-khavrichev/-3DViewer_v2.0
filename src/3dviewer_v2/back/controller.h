/*!
\file
\brief Заголовочный файл с описанием функций.

Данный файл содержит в себе определения
функций, используемых в проекте 3DViewer.
*/

#ifndef CPP4_SMARTCALC_V2_3DVIEWER_V2_BACK_CONTROLLER_H
#define CPP4_SMARTCALC_V2_3DVIEWER_V2_BACK_CONTROLLER_H

#include "3dviewer.h"
#include "model.h"

namespace s21 {

class Controller {
 public:
  Controller() {}

  Controller(const std::string filename) {
    Init();
    (&viewer_model_)->ReadObjFile(filename);
  }

  ~Controller() { (&viewer_model_)->FreeMem(); }

  void Init() { (&viewer_model_)->Init(); };

  void ReadObjFile(const std::string filename) {
    Init();
    (&viewer_model_)->ReadObjFile(filename);
  }

  /*!
  Метод, возвращающий результат считывания из obj-файла
  \result 0 - успешное завершение, 1 - неудачное.
  */
  bool GetReadingResult() { return (&viewer_model_)->GetReadingResult(); };

  /*!
  Метод, возвращающий количество вершин модели
  \result число вершин.
  */
  size_t GetPointsAmount() { return (&viewer_model_)->GetPointsAmount(); };

  /*!
  Метод, возвращающий количество полиголов модели
  \result число полигонов.
  */
  size_t GetSurfacesAmount() { return (&viewer_model_)->GetSurfacesAmount(); };

  /*!
  Метод, возвращающий количество граней модели
  \result число граней.
  */
  size_t GetEdgesAmount() { return (&viewer_model_)->GetEdgesAmount(); };

  /*!
  Метод, возвращающий элемент массива вершин по индексу
  \result массив вершин.
  */
  Vertex GetVertexByIndex(const size_t index) {
    return (&viewer_model_)->GetVertexByIndex(index);
  };

  /*!
  Метод, возвращающий элемент массива полигонов по индексу
  \result массив полигонов.
  */
  Polygon GetPolygonByIndex(const size_t index) {
    return (&viewer_model_)->GetPolygonByIndex(index);
  };

  /*!
  Метод, возвращающий структуру массива вершин
  \result массив вершин.
  */
  VertexArray GetVertexArray() { return (&viewer_model_)->GetVertexArray(); };

  /*!
  Метод, возвращающий структуру массива вершин при начальном считывания
  \result массив вершин.
  */
  VertexArray GetVertexArrayStart() {
    return (&viewer_model_)->GetVertexArrayStart();
  };

  /*!
  Метод, возвращающий структуру массива полигонов
  \result массив полигонов.
  */
  PolygonArray GetPolygonArray() {
    return (&viewer_model_)->GetPolygonArray();
  };

  /*!
  Метод, реализующий различные аффнитивные преобразования obj-файла.
  Построчно считывая координаты точек из файла, проводит требуемое
  преобразование и записывает координаты точек обратно в файл. \param [type] тип
  требуемого преобразования: перемещение, вращение или трансформация \param
  [values] структура, задающая значения преобразований по 3 координатным осям
  */
  void Transformation(TransformationType type, Vertex values) {
    return (&viewer_model_)->Transformation(type, values);
  }

 private:
  /*!
  Экземпляр модели
  */
  Model viewer_model_;
};

}  // namespace s21

#endif  // CPP4_SMARTCALC_V2_3DVIEWER_V2_BACK_CONTROLLER_H
