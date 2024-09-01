/*!
\file
\brief Исходный файл, содержащий функции для реализации базовых преобразований
3D-модели: перемещения, вращения, масштабирования.
*/

#include "3dviewer.h"

namespace s21 {

void Model::Transformation(const TransformationType type, const Vertex values) {
  Vertex *ver = vertex_arr_.vertexes;
  Vertex *first_ver = vertex_arr_start_.vertexes;
  for (size_t i = 1; i <= vertex_arr_.vertex_amount; i++, ver++, first_ver++) {
    if (type == TransformationType::Translation) {
      MatrixTranslation(ver, first_ver, values);
    } else if (type == TransformationType::Rotation) {
      MatrixRotation(ver, values);
    } else if (type == TransformationType::Scaling) {
      MatrixScaling(ver, first_ver, values);
    }
  }
}

void Model::MatrixTranslation(Vertex *point, Vertex *first_arr,
                              const Vertex trans_values) {
  point->x += first_arr->x + trans_values.x;
  point->y += first_arr->y + trans_values.y;
  point->z += first_arr->z + trans_values.z;
}

void Model::MatrixRotation(Vertex *point, const Vertex rot_values) {
  RotationX(point, rot_values);
  RotationY(point, rot_values);
  RotationZ(point, rot_values);
}

void Model::RotationX(Vertex *point, const Vertex rot_values) {
  double rotation_varr[3] = {point->x, point->y, point->z};
  double degrees = rot_values.x * (PI / 180.0000000);

  point->y = rotation_varr[1] * cos(degrees) - rotation_varr[2] * sin(degrees);
  point->z = rotation_varr[1] * sin(degrees) + rotation_varr[2] * cos(degrees);
}

void Model::RotationY(Vertex *point, const Vertex rot_values) {
  double rotation_varr[3] = {point->x, point->y, point->z};
  double degrees = rot_values.y * (PI / 180.0000000);

  point->x = rotation_varr[0] * cos(degrees) + rotation_varr[2] * sin(degrees);
  point->z = -rotation_varr[0] * sin(degrees) + rotation_varr[2] * cos(degrees);
}

void Model::RotationZ(Vertex *point, const Vertex rot_values) {
  double rotation_varr[3] = {point->x, point->y, point->z};
  double degrees = rot_values.z * (PI / 180.0000000);

  point->x = rotation_varr[0] * cos(degrees) - rotation_varr[1] * sin(degrees);
  point->y = rotation_varr[0] * sin(degrees) + rotation_varr[1] * cos(degrees);
}

void Model::MatrixScaling(Vertex *point, Vertex *first_arr,
                          const Vertex scale_values) {
  point->x *= first_arr->x * scale_values.x / point->x;
  point->y *= first_arr->y * scale_values.y / point->y;
  point->z *= first_arr->z * scale_values.z / point->z;
}

}  // namespace s21
