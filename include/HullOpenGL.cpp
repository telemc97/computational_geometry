#include "HullOpenGL.h"

HullOpenGL::HullOpenGL(vector<Point2D> points, vector<Point2D> hull_points){
  for(int i=0;i<points.size();i++){
    _points.push_back(points[i]);
  }
  //Move Vector "hull_points" to private array "_hull_points"
  _hull_points = hull_points;
  for (int i=0;i<hull_points.size();i++){
    _hull_points.push_back(hull_points[i]);
  }
  _GL_points = HullOpenGL::convertPointsCoords(_points);
  _GL_hull_points = HullOpenGL::convertPointsCoords(_hull_points);

  HullOpenGL::createWindow();
  HullOpenGL::drawPointsAndLines(_GL_points);
  HullOpenGL::drawPointsAndLines(_GL_hull_points);

}

HullOpenGL::HullOpenGL(vector<Point2D> points){
  for(int i=0;i<points.size();i++){
    _points.push_back(points[i]);
  }

  _GL_points = HullOpenGL::convertPointsCoords(_points);

  HullOpenGL::createWindow();
  HullOpenGL::drawPointsAndLines(_GL_points);
}

int HullOpenGL::createWindow(){
  if (!glfwInit()){
    std::cerr<<"Error initializing glfw";   
    return -1;
  }

  _GL_window = glfwCreateWindow(640, 480, "Convex Hull", NULL, NULL);
  if (!_GL_window)
  {
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(_GL_window);
  return 0;
}

void HullOpenGL::drawPointsAndLines(vector<PointGL2D> GL_points){
  while (!glfwWindowShouldClose(_GL_window)){
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    for (int i=0;i<GL_points.size();i++){
      glColor4f(1.0, 1.0, 1.0, 1.0);
      glVertex3f(GL_points[i].x, GL_points[i].y, GL_points[i].z);
    }
    glEnd();
    glfwSwapBuffers(_GL_window);
  }
}

void HullOpenGL::errorCallback(int error, const char* description){ 
  fprintf(stderr, "Error: %s\n", description);
}


vector<PointGL2D> HullOpenGL::convertPointsCoords(vector<Point2D> points){
  int x_max, y_max = 0;
  int x_min, y_min = 100000000;
  int points_size = points.size();
  for (int i=0;i<points_size;i++){
    if (points[i].x<x_min){
      x_min = points[i].x;
    }else if (points[i].x>x_max){
      x_max = points[i].x;
    } 
    if (points[i].y<y_min){
      y_min = points[i].y;
    }else if (points[i].y>y_max){
      y_max = points[i].y;
    } 
  }

  float norm_max = 0.0f;
  //Max value to normalize
  if (x_max>y_max){
    norm_max = (x_max-x_min)/2.0 + 10.0;
  }else{
    norm_max = (y_max-y_min)/2.0 + 10.0;
  }

  //Find new Center based on the maxes and mins
  Point2D new_center = {0,0};
  new_center.x = ((x_max-x_min)/2)+x_min;
  new_center.y = ((y_max-y_min)/2)+y_min;

  //Convert the Points to have as new_center as the new origin and normalize them
  vector<PointGL2D> GL_points;
  for (int i=0;i<points_size;i++){
    GLfloat x = (1.0f*(_points[i].x - new_center.x))/norm_max * 1.0f;
    GLfloat y = (1.0f*(_points[i].y - new_center.y))/norm_max * 1.0f;
    GL_points.push_back({x, y});
  }

  return GL_points;
}