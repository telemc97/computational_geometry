#include "Point.h"
#include <vector>
#include <GLFW/glfw3.h>

struct 2DPointGL{
  float x,y;
  float z = 0.0f;
};

class HullOpenGL {

  public:

  HullOpenGL(2DPoint points[], vector<2DPoint> hull_points); //Constructor to display both points and convex hull.
  HullOpenGL(2DPoint points[]); //Constructor to display only the points.

  ~HullOpenGL();

  private:

  2DPoint* _points[];
  2DPoint* _hull_points[];
  2DPointGL* _GL_points[];

  int _points_size;
  GLFWwindow* window;

  void createWindow();

  void errorCallback(int error, const char* description);

  void convertPointsCoords();

  void drawPoints();

  void drawLines();

}