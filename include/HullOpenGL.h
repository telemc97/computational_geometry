#include "Point.h"
#include <vector>
#include <iostream>
#include <GLFW/glfw3.h>
using namespace std;
struct PointGL2D{
  GLfloat x,y;
  GLfloat z = 0.0f;
};

class HullOpenGL {

  public:

  HullOpenGL(vector<Point2D> points, vector<Point2D> hull_points); //Constructor to display both points and convex hull.
  HullOpenGL(vector<Point2D> points); //Constructor to display only the points.

  private:

  GLFWwindow* _GL_window;

  int createWindow();

  void errorCallback(int error, const char* description);

  vector<PointGL2D> convertPointsCoords(vector<Point2D> points);

  void drawPointsAndLines(vector<PointGL2D> GL_points);

  vector<Point2D> _points;
  vector<PointGL2D> _GL_points;

  vector<Point2D> _hull_points;
  vector<PointGL2D> _GL_hull_points;
};