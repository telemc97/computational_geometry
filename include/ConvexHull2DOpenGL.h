#include "Point.h"
#include <vector>
#include <iostream>
#include <GLFW/glfw3.h>
using namespace std;
struct PointGL2D{
  GLfloat x,y,z;
};

struct Color4f{
  float r,g,b,a;
};

class ConvexHull2DOpenGL {

  public:

  ConvexHull2DOpenGL(vector<Point2D>& points, vector<Point2D>& hull_points); //Constructor to display both points and convex hull.
  ConvexHull2DOpenGL(vector<Point2D>& points); //Constructor to display only the points.
  ConvexHull2DOpenGL(); //Constructor for Testing

  virtual ~ConvexHull2DOpenGL();

  void render();

  void setCoordNormValue(float value);

  void setPointColor4f(float r, float g, float b, float a);

  void setLineColor4f(float r, float g, float b, float a);

  void setBackgroundColor(float r, float g, float b, float a);


  private:

  GLFWwindow* _GL_window;

  int createWindow();

  static inline void error_callback(int error, const char* description){
    fputs(description, stderr);
  };

  static inline void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
      glfwSetWindowShouldClose(window, GL_TRUE);
  };

  inline int initRender(){
    glClearColor(_background_color.r, _background_color.g, _background_color.b, _background_color.a);
    glOrtho(-_norm_value, _norm_value, -_norm_value, 1.0f, -1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    return 0;
  };

  vector<PointGL2D> convertPointsCoords(const vector<Point2D>& points);

  int drawPoints(vector<PointGL2D>& GL_points);

  int drawHullLines(vector<PointGL2D>& GL_hull_points);

  vector<PointGL2D> convertPoints(vector<Point2D>& points);

  float _norm_value = 1.0f;

  Color4f _point_color = {1.0f, 1.0f, 1.0f, 1.0f};
  Color4f _line_color = {1.0f, 1.0f, 1.0f, 1.0f};
  Color4f _background_color = {0.0f, 0.0f, 0.0f, 0.0f};

  int getPointMinMax();
  Point2D _new_center = {0,0};
  float _norm_dist;

  vector<Point2D> _points;
  vector<PointGL2D> _GL_points;

  vector<Point2D> _hull_points;
  vector<PointGL2D> _GL_hull_points;
};