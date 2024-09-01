/*!
\file
\brief Исходный файл, содержащий код для тестирования корректности работы
основных функций.

Требуемое покрытие - 80%.
*/
#include <gtest/gtest.h>

#include "3dviewer_v2/back/3dviewer.h"

using namespace std;
using namespace s21;

TEST(TestViewer, truncated_tetrahedron_success) {
  string filename = "models/truncated-tetrahedron.obj";

  Controller controller(filename);
  ASSERT_TRUE(controller.GetReadingResult());

  VertexArray vertex_arr_ans;
  PolygonArray polygon_arr_ans;
  vertex_arr_ans.vertex_amount = 12;
  polygon_arr_ans.polygon_amount = 20;
  polygon_arr_ans.edges_amount = 30;

  vertex_arr_ans.vertexes = new Vertex[vertex_arr_ans.vertex_amount];
  polygon_arr_ans.polygons = new Polygon[polygon_arr_ans.polygon_amount];
  Vertex* pp_a = vertex_arr_ans.vertexes;
  Polygon* polyp = polygon_arr_ans.polygons;

  (pp_a + 0)->x = 1.6666666;
  (pp_a + 0)->y = 5.552925;
  (pp_a + 0)->z = 7.5426464;

  (pp_a + 1)->x = 3.3333333;
  (pp_a + 1)->y = 2.6661737;
  (pp_a + 1)->z = 7.5426464;

  (pp_a + 2)->x = 1.6664362;
  (pp_a + 2)->y = 3.6282907;
  (pp_a + 2)->z = 10.264490;

  (pp_a + 3)->x = 3.3335638;
  (pp_a + 3)->y = 4.5908065;
  (pp_a + 3)->z = 12.987463;

  (pp_a + 4)->x = 8.3335640;
  (pp_a + 4)->y = 3.6282907;
  (pp_a + 4)->z = 10.26449;

  (pp_a + 5)->x = 6.6666665;
  (pp_a + 5)->y = 2.6661737;
  (pp_a + 5)->z = 7.5426464;

  (pp_a + 6)->x = 6.6664360;
  (pp_a + 6)->y = 4.5908065;
  (pp_a + 6)->z = 12.987463;

  (pp_a + 7)->x = 5.0000000;
  (pp_a + 7)->y = 9.402193;
  (pp_a + 7)->z = 10.26449;

  (pp_a + 8)->x = 6.6666665;
  (pp_a + 8)->y = 8.439676;
  (pp_a + 8)->z = 7.5426464;

  (pp_a + 9)->x = 3.3333333;
  (pp_a + 9)->y = 8.439676;
  (pp_a + 9)->z = 7.5426464;

  (pp_a + 10)->x = 8.3333330;
  (pp_a + 10)->y = 5.552925;
  (pp_a + 10)->z = 7.5426464;

  (pp_a + 11)->x = 5.0000000;
  (pp_a + 11)->y = 7.477159;
  (pp_a + 11)->z = 12.987463;

  Vertex max_xyz;
  Vertex min_xyz;
  Vertex* v_ans = vertex_arr_ans.vertexes;
  max_xyz.x = v_ans->x;
  max_xyz.y = v_ans->y;
  max_xyz.z = v_ans->z;

  min_xyz.x = v_ans->x;
  min_xyz.y = v_ans->y;
  min_xyz.z = v_ans->z;

  for (size_t i = 1; i <= vertex_arr_ans.vertex_amount; i++, v_ans++) {
    if (max_xyz.x <= v_ans->x) max_xyz.x = v_ans->x;
    if (max_xyz.y <= v_ans->y) max_xyz.y = v_ans->y;
    if (max_xyz.z <= v_ans->z) max_xyz.z = v_ans->z;

    if (min_xyz.x >= v_ans->x) min_xyz.x = v_ans->x;
    if (min_xyz.y >= v_ans->y) min_xyz.y = v_ans->y;
    if (min_xyz.z >= v_ans->z) min_xyz.z = v_ans->z;
  }

  Vertex center_xyz_ans;
  Vertex diff_max_min_ans;

  diff_max_min_ans.x = max_xyz.x - min_xyz.x;
  diff_max_min_ans.y = max_xyz.y - min_xyz.y;
  diff_max_min_ans.z = max_xyz.z - min_xyz.z;

  double max_diff =
      fmax(fmax(diff_max_min_ans.x, diff_max_min_ans.y), diff_max_min_ans.z);

  double scal = 1 / max_diff;
  center_xyz_ans.x = min_xyz.x + (max_xyz.x - min_xyz.x) / 2;
  center_xyz_ans.y = min_xyz.y + (max_xyz.y - min_xyz.y) / 2;
  center_xyz_ans.z = min_xyz.z + (max_xyz.z - min_xyz.z) / 2;

  for (size_t i = 0; i < vertex_arr_ans.vertex_amount; i++, v_ans++) {
    (pp_a + i)->x -= center_xyz_ans.x;
    (pp_a + i)->y -= center_xyz_ans.y;
    (pp_a + i)->z -= center_xyz_ans.z;

    (pp_a + i)->x *= scal;
    (pp_a + i)->y *= scal;
    (pp_a + i)->z *= scal;
  }

  for (size_t i = 0; i < 20; i++) {
    (polyp + i)->points = new int[3];
    (polyp + i)->points_in_polygon_amount = 3;
  }
  (polyp + 0)->points[0] = 0;
  (polyp + 0)->points[1] = 1;
  (polyp + 0)->points[2] = 2;

  (polyp + 1)->points[0] = 3;
  (polyp + 1)->points[1] = 2;
  (polyp + 1)->points[2] = 4;

  (polyp + 2)->points[0] = 4;
  (polyp + 2)->points[1] = 2;
  (polyp + 2)->points[2] = 1;

  (polyp + 3)->points[0] = 4;
  (polyp + 3)->points[1] = 1;
  (polyp + 3)->points[2] = 5;

  (polyp + 4)->points[0] = 4;
  (polyp + 4)->points[1] = 6;
  (polyp + 4)->points[2] = 3;

  (polyp + 5)->points[0] = 7;
  (polyp + 5)->points[1] = 8;
  (polyp + 5)->points[2] = 9;

  (polyp + 6)->points[0] = 5;
  (polyp + 6)->points[1] = 1;
  (polyp + 6)->points[2] = 10;

  (polyp + 7)->points[0] = 10;
  (polyp + 7)->points[1] = 1;
  (polyp + 7)->points[2] = 0;

  (polyp + 8)->points[0] = 10;
  (polyp + 8)->points[1] = 0;
  (polyp + 8)->points[2] = 8;

  (polyp + 9)->points[0] = 8;
  (polyp + 9)->points[1] = 0;
  (polyp + 9)->points[2] = 9;

  (polyp + 10)->points[0] = 5;
  (polyp + 10)->points[1] = 10;
  (polyp + 10)->points[2] = 4;

  (polyp + 11)->points[0] = 10;
  (polyp + 11)->points[1] = 8;
  (polyp + 11)->points[2] = 4;

  (polyp + 12)->points[0] = 4;
  (polyp + 12)->points[1] = 8;
  (polyp + 12)->points[2] = 7;

  (polyp + 13)->points[0] = 4;
  (polyp + 13)->points[1] = 7;
  (polyp + 13)->points[2] = 6;

  (polyp + 14)->points[0] = 6;
  (polyp + 14)->points[1] = 7;
  (polyp + 14)->points[2] = 11;

  (polyp + 15)->points[0] = 0;
  (polyp + 15)->points[1] = 2;
  (polyp + 15)->points[2] = 9;

  (polyp + 16)->points[0] = 9;
  (polyp + 16)->points[1] = 2;
  (polyp + 16)->points[2] = 7;

  (polyp + 17)->points[0] = 7;
  (polyp + 17)->points[1] = 2;
  (polyp + 17)->points[2] = 3;

  (polyp + 18)->points[0] = 7;
  (polyp + 18)->points[1] = 3;
  (polyp + 18)->points[2] = 11;

  (polyp + 19)->points[0] = 11;
  (polyp + 19)->points[1] = 3;
  (polyp + 19)->points[2] = 6;

  ASSERT_EQ(controller.GetPointsAmount(), vertex_arr_ans.vertex_amount);
  ASSERT_EQ(controller.GetSurfacesAmount(), polygon_arr_ans.polygon_amount);
  ASSERT_EQ(controller.GetEdgesAmount(), polygon_arr_ans.edges_amount);

  for (size_t i = 0; i < vertex_arr_ans.vertex_amount; i++) {
    ASSERT_EQ(controller.GetVertexByIndex(i).x, (pp_a + i)->x);
    ASSERT_EQ(controller.GetVertexByIndex(i).y, (pp_a + i)->y);
    ASSERT_EQ(controller.GetVertexByIndex(i).z, (pp_a + i)->z);
  }

  for (size_t i = 0; i < polygon_arr_ans.polygon_amount; i++) {
    ASSERT_EQ(controller.GetPolygonByIndex(i).points[0],
              (polyp + i)->points[0]);
    ASSERT_EQ(controller.GetPolygonByIndex(i).points[1],
              (polyp + i)->points[1]);
    ASSERT_EQ(controller.GetPolygonByIndex(i).points[2],
              (polyp + i)->points[2]);
  }
  Vertex values = {0, 0, 0};
  values.x = 0.1;
  values.z = 0.15;
  controller.Transformation(TransformationType::Translation, values);

  for (size_t i = 0; i < vertex_arr_ans.vertex_amount; i++) {
    ASSERT_NEAR(controller.GetVertexByIndex(i).x -
                    controller.GetVertexArrayStart().vertexes[i].x,
                (pp_a + i)->x + 0.1, 10E-6);
    ASSERT_NEAR(controller.GetVertexByIndex(i).y -
                    controller.GetVertexArrayStart().vertexes[i].y,
                (pp_a + i)->y, 10E-6);
    ASSERT_NEAR(controller.GetVertexByIndex(i).z -
                    controller.GetVertexArrayStart().vertexes[i].z,
                (pp_a + i)->z + 0.15, 10E-6);
  }

  values.x = 1;
  values.y = 2;
  values.z = 0.5;
  controller.ReadObjFile(filename);
  controller.Transformation(TransformationType::Scaling, values);

  for (size_t i = 0; i < vertex_arr_ans.vertex_amount; i++) {
    ASSERT_EQ(controller.GetVertexByIndex(i).x, (pp_a + i)->x);
    ASSERT_EQ(controller.GetVertexByIndex(i).y, (pp_a + i)->y * 2);
    ASSERT_EQ(controller.GetVertexByIndex(i).z, (pp_a + i)->z * 0.5);
  }

  delete[] vertex_arr_ans.vertexes;
  for (size_t i = 0; i < polygon_arr_ans.polygon_amount; i++) {
    delete[] polygon_arr_ans.polygons[i].points;
  }

  delete[] polygon_arr_ans.polygons;
}

TEST(TestViewer, truncated_tetrahedron_fail) {
  string filename = "models/truncated-tetrahedron1.obj";
  Controller controller(filename);
  ASSERT_FALSE(controller.GetReadingResult());
}

TEST(TestViewer, cube_1) {
  string filename = "models/cube.obj";
  Controller controller(filename);
  ASSERT_TRUE(controller.GetReadingResult());

  VertexArray vertex_arr_ans;
  PolygonArray polygon_arr_ans;
  vertex_arr_ans.vertex_amount = 8;
  polygon_arr_ans.polygon_amount = 12;
  polygon_arr_ans.edges_amount = 18;

  vertex_arr_ans.vertexes = new Vertex[vertex_arr_ans.vertex_amount];
  polygon_arr_ans.polygons = new Polygon[polygon_arr_ans.polygon_amount];
  Vertex* pp_a = vertex_arr_ans.vertexes;
  Polygon* polyp = polygon_arr_ans.polygons;

  (pp_a + 0)->x = -0.500000;
  (pp_a + 0)->y = -0.500000;
  (pp_a + 0)->z = 0.500000;

  (pp_a + 1)->x = 0.500000;
  (pp_a + 1)->y = -0.500000;
  (pp_a + 1)->z = 0.500000;

  (pp_a + 2)->x = -0.500000;
  (pp_a + 2)->y = 0.500000;
  (pp_a + 2)->z = 0.500000;

  (pp_a + 3)->x = 0.500000;
  (pp_a + 3)->y = 0.500000;
  (pp_a + 3)->z = 0.500000;

  (pp_a + 4)->x = -0.500000;
  (pp_a + 4)->y = 0.500000;
  (pp_a + 4)->z = -0.500000;

  (pp_a + 5)->x = 0.500000;
  (pp_a + 5)->y = 0.500000;
  (pp_a + 5)->z = -0.500000;

  (pp_a + 6)->x = -0.500000;
  (pp_a + 6)->y = -0.500000;
  (pp_a + 6)->z = -0.500000;

  (pp_a + 7)->x = 0.500000;
  (pp_a + 7)->y = -0.500000;
  (pp_a + 7)->z = -0.500000;

  for (size_t i = 0; i < 12; i++) {
    (polyp + i)->points = new int[3];
    (polyp + i)->points_in_polygon_amount = 3;
  }
  (polyp + 0)->points[0] = 0;
  (polyp + 0)->points[1] = 1;
  (polyp + 0)->points[2] = 2;

  (polyp + 1)->points[0] = 2;
  (polyp + 1)->points[1] = 1;
  (polyp + 1)->points[2] = 3;

  (polyp + 2)->points[0] = 2;
  (polyp + 2)->points[1] = 3;
  (polyp + 2)->points[2] = 4;

  (polyp + 3)->points[0] = 4;
  (polyp + 3)->points[1] = 3;
  (polyp + 3)->points[2] = 5;

  (polyp + 4)->points[0] = 4;
  (polyp + 4)->points[1] = 5;
  (polyp + 4)->points[2] = 6;

  (polyp + 5)->points[0] = 6;
  (polyp + 5)->points[1] = 5;
  (polyp + 5)->points[2] = 7;

  (polyp + 6)->points[0] = 6;
  (polyp + 6)->points[1] = 7;
  (polyp + 6)->points[2] = 0;

  (polyp + 7)->points[0] = 0;
  (polyp + 7)->points[1] = 7;
  (polyp + 7)->points[2] = 1;

  (polyp + 8)->points[0] = 1;
  (polyp + 8)->points[1] = 7;
  (polyp + 8)->points[2] = 3;

  (polyp + 9)->points[0] = 3;
  (polyp + 9)->points[1] = 7;
  (polyp + 9)->points[2] = 5;

  (polyp + 10)->points[0] = 6;
  (polyp + 10)->points[1] = 0;
  (polyp + 10)->points[2] = 4;

  (polyp + 11)->points[0] = 4;
  (polyp + 11)->points[1] = 0;
  (polyp + 11)->points[2] = 2;

  // max_min_vertex(&vertex_arr_answer, &maxs_a, &mins_a);
  // rescaling_and_centering(&vertex_arr_answer, maxs_a, mins_a, 0.5);
  // VertexArray vertex_arr_ans_start = vertex_arr_ans;
  ASSERT_EQ(controller.GetPointsAmount(), vertex_arr_ans.vertex_amount);
  ASSERT_EQ(controller.GetSurfacesAmount(), polygon_arr_ans.polygon_amount);
  ASSERT_EQ(controller.GetEdgesAmount(), polygon_arr_ans.edges_amount);

  for (size_t i = 0; i < vertex_arr_ans.vertex_amount; i++) {
    ASSERT_EQ(controller.GetVertexByIndex(i).x, (pp_a + i)->x);
    ASSERT_EQ(controller.GetVertexByIndex(i).y, (pp_a + i)->y);
    ASSERT_EQ(controller.GetVertexByIndex(i).z, (pp_a + i)->z);
  }
  for (size_t i = 0; i < polygon_arr_ans.polygon_amount; i++) {
    ASSERT_EQ(controller.GetPolygonByIndex(i).points[0],
              (polyp + i)->points[0]);
    ASSERT_EQ(controller.GetPolygonArray().polygons[i].points[1],
              (polyp + i)->points[1]);
    ASSERT_EQ(controller.GetPolygonByIndex(i).points[2],
              (polyp + i)->points[2]);
  }

  Vertex values = {0, 0, 0};
  values.x = 30;
  // values->y_axis = 45;
  // values->z_axis = 90;

  (pp_a + 0)->x = -0.500000;
  (pp_a + 0)->y = -0.6830125;
  (pp_a + 0)->z = 0.1830125;

  (pp_a + 1)->x = 0.500000;
  (pp_a + 1)->y = -0.6830125;
  (pp_a + 1)->z = 0.1830125;

  (pp_a + 2)->x = -0.500000;
  (pp_a + 2)->y = 0.1830125;
  (pp_a + 2)->z = 0.6830125;

  (pp_a + 3)->x = 0.500000;
  (pp_a + 3)->y = 0.1830125;
  (pp_a + 3)->z = 0.6830125;

  (pp_a + 4)->x = -0.500000;
  (pp_a + 4)->y = 0.6830125;
  (pp_a + 4)->z = -0.1830125;

  (pp_a + 5)->x = 0.500000;
  (pp_a + 5)->y = 0.6830125;
  (pp_a + 5)->z = -0.1830125;

  (pp_a + 6)->x = -0.500000;
  (pp_a + 6)->y = -0.1830125;
  (pp_a + 6)->z = -0.6830125;

  (pp_a + 7)->x = 0.500000;
  (pp_a + 7)->y = -0.1830125;
  (pp_a + 7)->z = -0.6830125;

  controller.Transformation(TransformationType::Rotation, values);

  for (size_t i = 0; i < vertex_arr_ans.vertex_amount; i++) {
    ASSERT_NEAR(controller.GetVertexByIndex(i).x, (pp_a + i)->x, 10E-6);
    ASSERT_NEAR(controller.GetVertexByIndex(i).y, (pp_a + i)->y, 10E-6);
    ASSERT_NEAR(controller.GetVertexByIndex(i).z, (pp_a + i)->z, 10E-6);
  }
  values.x = 0;
  values.y = 45;
  // values->z_axis = 90;

  (pp_a + 0)->x = -0.224145;
  (pp_a + 0)->y = -0.6830125;
  (pp_a + 0)->z = 0.482965;

  (pp_a + 1)->x = 0.482965;
  (pp_a + 1)->y = -0.6830125;
  (pp_a + 1)->z = -0.224145;

  (pp_a + 2)->x = 0.12941;
  (pp_a + 2)->y = 0.1830125;
  (pp_a + 2)->z = 0.83652;

  (pp_a + 3)->x = 0.83652;
  (pp_a + 3)->y = 0.1830125;
  (pp_a + 3)->z = 0.12941;

  (pp_a + 4)->x = -0.482965;
  (pp_a + 4)->y = 0.6830125;
  (pp_a + 4)->z = 0.224145;

  (pp_a + 5)->x = 0.224145;
  (pp_a + 5)->y = 0.6830125;
  (pp_a + 5)->z = -0.482965;

  (pp_a + 6)->x = -0.83652;
  (pp_a + 6)->y = -0.1830125;
  (pp_a + 6)->z = -0.12941;

  (pp_a + 7)->x = -0.12941;
  (pp_a + 7)->y = -0.1830125;
  (pp_a + 7)->z = -0.83652;

  delete[] vertex_arr_ans.vertexes;
  for (size_t i = 0; i < polygon_arr_ans.polygon_amount; i++) {
    delete[] polygon_arr_ans.polygons[i].points;
  }

  delete[] polygon_arr_ans.polygons;
  // delete [] bbb.vertexes;
}

TEST(TestViewer, test_fail_1) {
  string filename = "models/null.obj";
  Controller controller(filename);
  ASSERT_FALSE(controller.GetReadingResult());
}

TEST(TestViewer, test_fail_2) {
  string filename = "models/aboba.obj";
  Controller controller(filename);
  ASSERT_FALSE(controller.GetReadingResult());
}

TEST(TestViewer, test_open_close_open_close) {
  string filename = "models/cube.obj";
  string filename1 = "models/truncated-tetrahedron.obj";
  string filename2 = "models/glock.obj";
  Controller controller;
  controller.ReadObjFile(filename1);
  controller.ReadObjFile(filename2);
  controller.ReadObjFile(filename);
  ASSERT_TRUE(controller.GetReadingResult());
}

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}