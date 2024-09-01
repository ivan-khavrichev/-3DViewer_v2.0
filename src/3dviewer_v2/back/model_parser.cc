/*!
\file
\brief Исходный файл, содержащий функции для парсинга obj-файла, обработки и
структурирования считанной информации, а так же всппомогательные функции.

*/
#include "3dviewer.h"

namespace s21 {

void Model::ReadObjFile(const std::string filename) {
  if (ParsingObjFile(filename) == true) {
    reading_result_ = true;
    MaxMinVertex();
    RescalingAndCentering(value_scale_);
    VertexCopy();
  } else {
    reading_result_ = false;
  }
}

bool Model::ParsingObjFile(const std::string filename) {
  bool out = true;

  std::fstream file_3d;
  file_3d.open(filename, std::ios_base::in);
  if (file_3d.is_open()) {
    ObjCounter(file_3d);
  } else {
    out = false;
  }
  if (CreateVPArrays() == false) out = false;

  file_3d.clear();
  file_3d.seekg(0);
  FormingArrays(file_3d);
  file_3d.close();

  return out;
}

void Model::ObjCounter(std::fstream &file_3d) {
  char string_from_file[max_length_];

  while (file_3d.getline(string_from_file, max_length_)) {
    if (*string_from_file == 'v' && *(string_from_file + 1) == ' ')
      vertex_arr_.vertex_amount++;

    if (*string_from_file == 'f' && *(string_from_file + 1) == ' ')
      polygon_arr_.polygon_amount++;
  }
}

bool Model::CreateVPArrays() {
  bool out = true;
  if (vertex_arr_.vertex_amount <= 3 || polygon_arr_.polygon_amount <= 1) {
    out = false;
  } else {
    vertex_arr_.vertexes = new Vertex[vertex_arr_.vertex_amount];
    polygon_arr_.polygons = new Polygon[polygon_arr_.polygon_amount];
  }

  return out;
}

void Model::FreeMem() {
  if (vertex_arr_start_.vertexes != nullptr)
    delete[] vertex_arr_start_.vertexes;
  if (vertex_arr_.vertexes != nullptr) delete[] vertex_arr_.vertexes;
  for (size_t i = 0; i < polygon_arr_.polygon_amount; i++) {
    delete[] polygon_arr_.polygons[i].points;
  }
  if (polygon_arr_.polygons != nullptr) delete[] polygon_arr_.polygons;
}

void Model::FormingArrays(std::fstream &file_3d) {
  size_t i = 0;
  size_t j = 0;
  char string_from_file[max_length_];
  while (file_3d.getline(string_from_file, max_length_)) {
    if (PointParser(string_from_file, i) == true) i++;
    if (SurfaceParser(string_from_file, j) == true) j++;
  }
  polygon_arr_.edges_amount /= 2;
}

bool Model::PointParser(char *readed_string, size_t index) {
  if (*readed_string != 'v') return false;
  bool out = true;
  char ch = 0;
  Vertex *vertex = vertex_arr_.vertexes + index;
  if (sscanf(readed_string, "%c %lf %lf %lf", &ch, &(vertex->x), &(vertex->y),
             &(vertex->z)) != 4)
    out = false;
  return out;
}

bool Model::SurfaceParser(char *readed_string, size_t index) {
  if (*readed_string != 'f') return false;
  bool out = true;
  size_t str_len = strlen(readed_string);
  char *tmp_string = EmptyStringAlloc(str_len);
  Polygon *polygon = polygon_arr_.polygons + index;
  polygon->points_in_polygon_amount =
      WriteToTmpStr(readed_string, tmp_string, str_len) + 1;

  polygon_arr_.edges_amount += polygon->points_in_polygon_amount;

  polygon->points = new int[polygon->points_in_polygon_amount];
  FormingPolygon(tmp_string, polygon, str_len);
  delete[] tmp_string;

  return out;
}

char *Model::EmptyStringAlloc(size_t length) {
  char *out = new char[length];
  memset(out, '\0', length);
  return out;
}

void Model::FormingPolygon(char *tmp_str, Polygon *polygon, size_t length) {
  char *substr = EmptyStringAlloc(length);
  size_t j = 0;
  size_t k = 0;
  for (size_t i = 0; i < length; i++) {
    if (isdigit(tmp_str[i]) != 0) {
      substr[j] = tmp_str[i];
      j++;
    }
    if (tmp_str[i] == ' ' || tmp_str[i] == '#') {
      int tmp = 0;
      sscanf(substr, "%d", &tmp);
      tmp--;
      *(polygon->points + k) = tmp;
      StrClean(substr, j);
      j = 0;
      k++;
    }
  }
  delete[] substr;
}

void Model::StrClean(char *str, const size_t j) {
  for (size_t i = 0; i < j; i++) {
    str[i] = '\0';
  }
}

size_t Model::WriteToTmpStr(char *read_str, char *tmp_str, const size_t len) {
  size_t j = 0;
  bool push_allowed = true;
  size_t out = 0;

  for (size_t i = 2; i < len; i++) {
    if (read_str[i] == ' ') {
      push_allowed = true;
      out++;
      tmp_str[j] = read_str[i];
      j++;
    }
    if (isdigit(read_str[i]) != 0 && push_allowed == true) {
      tmp_str[j] = read_str[i];
      j++;
    }
    if (read_str[i] == '/') push_allowed = false;
  }
  tmp_str[j] = '#';
  return out;
}

void Model::MaxMinVertex() {
  Vertex *ver = vertex_arr_.vertexes;
  max_xyz_.x = ver->x;
  max_xyz_.y = ver->y;
  max_xyz_.z = ver->z;

  min_xyz_.x = ver->x;
  min_xyz_.y = ver->y;
  min_xyz_.z = ver->z;

  for (size_t i = 1; i <= vertex_arr_.vertex_amount; i++, ver++) {
    if (max_xyz_.x <= ver->x) max_xyz_.x = ver->x;
    if (max_xyz_.y <= ver->y) max_xyz_.y = ver->y;
    if (max_xyz_.z <= ver->z) max_xyz_.z = ver->z;

    if (min_xyz_.x >= ver->x) min_xyz_.x = ver->x;
    if (min_xyz_.y >= ver->y) min_xyz_.y = ver->y;
    if (min_xyz_.z >= ver->z) min_xyz_.z = ver->z;
  }
}

void Model::RescalingAndCentering(const double value_scale) {
  Vertex center_xyz;
  Vertex diff_max_min;
  Vertex *ver = vertex_arr_.vertexes;
  diff_max_min.x = max_xyz_.x - min_xyz_.x;
  diff_max_min.y = max_xyz_.y - min_xyz_.y;
  diff_max_min.z = max_xyz_.z - min_xyz_.z;

  double max_diff = fmax(fmax(diff_max_min.x, diff_max_min.y), diff_max_min.z);

  double scal = (value_scale + value_scale) / max_diff;
  center_xyz.x = min_xyz_.x + (max_xyz_.x - min_xyz_.x) / 2;
  center_xyz.y = min_xyz_.y + (max_xyz_.y - min_xyz_.y) / 2;
  center_xyz.z = min_xyz_.z + (max_xyz_.z - min_xyz_.z) / 2;

  for (size_t i = 0; i < vertex_arr_.vertex_amount; i++, ver++) {
    ver->x -= center_xyz.x;
    ver->y -= center_xyz.y;
    ver->z -= center_xyz.z;

    ver->x *= scal;
    ver->y *= scal;
    ver->z *= scal;
  }
}

void Model::VertexCopy() {
  vertex_arr_start_.vertex_amount = vertex_arr_.vertex_amount;
  vertex_arr_start_.vertexes = new Vertex[vertex_arr_.vertex_amount];
  for (size_t i = 0; i < vertex_arr_start_.vertex_amount; i++) {
    vertex_arr_start_.vertexes[i].x = vertex_arr_.vertexes[i].x;
    vertex_arr_start_.vertexes[i].y = vertex_arr_.vertexes[i].y;
    vertex_arr_start_.vertexes[i].z = vertex_arr_.vertexes[i].z;
  }
}

void Model::Init() {
  reading_result_ = false;
  value_scale_ = 0.5;
  for (size_t i = 0; i < polygon_arr_.polygon_amount; i++) {
    delete[] polygon_arr_.polygons[i].points;
  }
  polygon_arr_.edges_amount = 0;
  polygon_arr_.polygon_amount = 0;
  delete[] polygon_arr_.polygons;
  vertex_arr_.vertex_amount = 0;
  delete[] vertex_arr_.vertexes;
  delete[] vertex_arr_start_.vertexes;
}

}  // namespace s21
