/*! \mainpage Главная страница документации проекта 3DViewer
 *
 * \section project_sec Задание
 *
 * Разработать программу для визуализации каркасной модели в трехмерном
 * пространстве,<br> позволяющую производить аффинные преобразования и
 * соответствующую ряду критериев.
 *
 * \subsection devs_sec Разработчики
 *
 * steffani: реализация преобразований, документация, тестирование.<br>
 * timberly: фронтэнд, приведение кода к гугл-стилю
 *
 * \subsection Примечание
 * Иконки взяты с сайта www.flaticon.com
 */
#ifndef CPP4_SMARTCALC_V2_3DVIEWER_V2_BACK_MODEL_H
#define CPP4_SMARTCALC_V2_3DVIEWER_V2_BACK_MODEL_H

#include "3dviewer.h"
#define PI 3.14159265358979323846  ///< число пи

namespace s21 {

/// @brief Структура, задающая точку (вершину) модели по координатам
struct Vertex {
  double x = 0;  ///< координата точки по оси X
  double y = 0;  ///< координата точки по оси Y
  double z = 0;  ///< координата точки по оси Z
};

/// @brief Структура, задающая поверхность (полигон) по точкам
struct Polygon {
  int *points = nullptr;                ///< номера точек
  size_t points_in_polygon_amount = 0;  ///< число точек в полигоне
};

/// @brief Структура, задающая массив точек (вершин)
struct VertexArray {
  Vertex *vertexes =
      nullptr;  ///< указатель на массив точек,задаваемый структурой point
  size_t vertex_amount = 0;  ///< количество точек в массиве
};

/// @brief Структура, задающая массив поверхностей (полигонов) по точкам
struct PolygonArray {
  Polygon *polygons = nullptr;  ///< полигон
  size_t polygon_amount = 0;  ///< число полигонов в модели
  size_t edges_amount = 0;    ///< число граней в модели
};

/// @brief Структура, задающая тип требуемого преобразования: перемещение,
/// вращение или трансформация
enum class TransformationType {
  Translation,  ///< перемещение
  Rotation,     ///< вращение
  Scaling       ///< масштабирование
};

class Model {
  friend class Controller;

 public:
  Model() {}

  ~Model() {}

  /*!
  Метод, реализующий задание начальных значений всем параметрам.
  */
  void Init();

  /*!
  Метод, реализующий все операции обработки obj-файла.
  \param [filename] строка с названием файла
  \result 0 - успешное завершение, 1 - неудачное.
  */
  void ReadObjFile(const std::string filename);

  /*!
  Метод, реализующий различные аффнитивные преобразования obj-файла.
  Построчно считывая координаты точек из файла, проводит требуемое
  преобразование и записывает координаты точек обратно в файл. \param [type] тип
  требуемого преобразования: перемещение, вращение или трансформация \param
  [values] структура, задающая значения преобразований по 3 координатным осям
  */
  void Transformation(const TransformationType type, const Vertex values);

  /*!
  Метод, возвращающий результат считывания из obj-файла
  \result 0 - успешное завершение, 1 - неудачное.
  */
  bool GetReadingResult() { return reading_result_; };

  /*!
  Метод, возвращающий количество вершин модели
  \result число вершин.
  */
  size_t GetPointsAmount() { return vertex_arr_.vertex_amount; };

  /*!
  Метод, возвращающий количество полиголов модели
  \result число полигонов.
  */
  size_t GetSurfacesAmount() { return polygon_arr_.polygon_amount; };

  /*!
  Метод, возвращающий количество граней модели
  \result число граней.
  */
  size_t GetEdgesAmount() { return polygon_arr_.edges_amount; };

  /*!
  Метод, возвращающий структуру массива вершин
  \result массив вершин.
  */
  VertexArray GetVertexArray() { return vertex_arr_; };

  /*!
  Метод, возвращающий структуру массива вершин при начальном считывания
  \result массив вершин.
  */
  VertexArray GetVertexArrayStart() { return vertex_arr_start_; };

  /*!
  Метод, возвращающий структуру массива полигонов
  \result массив полигонов.
  */
  PolygonArray GetPolygonArray() { return polygon_arr_; };

  /*!
  Метод, возвращающий элемент массива вершин по индексу
  \result массив вершин.
  */
  Vertex GetVertexByIndex(const size_t index) {
    return vertex_arr_.vertexes[index];
  };

  /*!
  Метод, возвращающий элемент массива полигонов по индексу
  \result массив полигонов.
  */
  Polygon GetPolygonByIndex(const size_t index) {
    return polygon_arr_.polygons[index];
  };

 private:
  /*!
  Результат считывания
  */
  bool reading_result_ = false;

  /*!
  Максимальная строка
  */
  const size_t max_length_ = 512;

  /*!
  Изначальный масштаб
  */
  double value_scale_ = 0.5;

  /*!
  Массив вершин модели
  */
  VertexArray vertex_arr_;

  /*!
  Первоначальный массив вершин модели
  */
  VertexArray vertex_arr_start_;

  /*!
  Массив полигонов модели
  */
  PolygonArray polygon_arr_;

  /*!
  Максимумы координат модели
  */
  Vertex max_xyz_;

  /*!
  Минимумы координат модели
  */
  Vertex min_xyz_;

  /*!
  Метод, реализующий парсинг obj-файла. Вначале, открыв файл, считает
  количество вершин и полигонов, затем, начав проход по файлу сначала заполняет
  структуры массивов полигонов и вершин. Возвращает результат:
  \param [filename] строка с названием файла
  \result 0 - успешное завершение, 1 - неудачное.
  */
  bool ParsingObjFile(const std::string filename);

  /*!
  Метод, реализующий счетчик вершин и поверхностей модели
  \param [file_3d] указатель на открываемый файл
  */
  void ObjCounter(std::fstream &file_3d);

  /*!
  Метод, который выделяет память под число вершин и полигонов.
  \result 0 - успешное завершение, 1 - неудачное.
  */
  bool CreateVPArrays();

  /*!
  Метод, реализующий парсинг obj-файла по вершинам. Заполняет массив вершин
  значениями.
  \param [readed_string] считанная строка
  \param [index] индекс элемента массива
  \result 0 - успешное завершение, 1 - неудачное.
  */
  bool PointParser(char *readed_string, size_t index);

  /*!
  Метод, реализующий парсинг obj-файла по полигонам. Заполняет массив полигонов
  значениями.
  \param [readed_string] считанная строка
  \param [index] индекс элемента массива
  \result 0 - успешное завершение, 1 - неудачное.
  */
  bool SurfaceParser(char *readed_string, size_t index);

  /*!
  Метод, который заполняет временную строку.
  \param [read_str] считанная из obj-файла строка
  \param [tmp_str] временная строка, содержащая номера точек
  \param [len] длина считанной строки
  \result число точек в полигоне.
  */
  size_t WriteToTmpStr(char *read_str, char *tmp_str, const size_t len);

  /*!
  Метод, заполняющий элемент массива полигонов.
  \param [tmp_str] временная строка, содержащая номера точек
  \param [polygon] указатель на массив точек полигона
  \param [len] длина считанной строки
  */
  void FormingPolygon(char *tmp_str, Polygon *polygon, size_t length);

  // /*!
  // Функция, заполняющая все символы строки до j-го символа на нулевой символ.
  // \param [str] указатель на строку
  // \param [j] индекс символа до которого производится замена
  // */
  void StrClean(char *str, const size_t j);

  /*!
  Метод, реализующий массивы вершин и поверхностей модели
  \param [file_3d] указатель на открываемый файл
  */
  void FormingArrays(std::fstream &file_3d);

  /*!
  Функция, которая максимальные и минимальные значения координат по осяям XYZ в
  массиве вершин.
  */
  void MaxMinVertex();

  /*!
  Функция, которая обрабатывает полученные массивы вершин для центрирования и
  масштабирования, необходимых для визуализации.
  \param [value_scale] первоначальный масштаб при открытии модели
  */
  void RescalingAndCentering(const double value_scale);

  /*!
  Функция, реализующая пересчет координат точек для реализации перемещения по
  определенной оси.
  \param [point] координаты точки
  \param [first_arr] координаты точки массива первоначальных вершин
  \param [trans_values] указатель на количество вершин
  */
  void MatrixTranslation(Vertex *point, Vertex *first_arr,
                         const Vertex trans_values);

  /*!
  Функция, реализующая пересчет координат точек для реализации вращения
  относительно определенной оси.
  \param [point] координаты точки
  \param [rot_values] указатель на количество вершин
  */
  void MatrixRotation(Vertex *point, const Vertex rot_values);

  /*!
  Функция, реализующая пересчет координат точек для реализации вращения
  относительно оси X.
  \param [point] координаты точки
  \param [rot_values] указатель на количество вершин
  */
  void RotationX(Vertex *point, const Vertex rot_values);

  /*!
  Функция, реализующая пересчет координат точек для реализации вращения
  относительно оси Y.
  \param [point] координаты точки
  \param [rot_values] указатель на количество вершин
  */
  void RotationY(Vertex *point, const Vertex rot_values);

  /*!
  Функция, реализующая пересчет координат точек для реализации вращения
  относительно оси Z.
  \param [point] координаты точки
  \param [rot_values] указатель на количество вершин
  */
  void RotationZ(Vertex *point, const Vertex rot_values);

  /*!
  Функция, реализующая пересчет координат точек для реализации масштабирования
  относительно определенной оси.
  \param [point] координаты точки
  \param [scale_values] указатель на количество вершин
  */
  void MatrixScaling(Vertex *point, Vertex *first_arr,
                     const Vertex scale_values);

  /*!
  Функция, реализующая очистку памяти
  */
  void FreeMem();

  /*!
  Функция, реализующая выделение памяти под пустую строку
  */
  char *EmptyStringAlloc(size_t length);

  /*!
  Функция, реализующая копирование структуры типа vertexes.
  */
  void VertexCopy();
};

}  // namespace s21

#endif  // CPP4_SMARTCALC_V2_3DVIEWER_V2_BACK_MODEL_H_
