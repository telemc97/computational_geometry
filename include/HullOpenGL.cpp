#include "HullOpenGL.h"

HullOpenGL::HullOpenGL(2DPoint points[], vector<2DPoint> hull_points){
  _points_size = sizeof(points);
  _points = new 2DPoint[_points_size];
  for(int i=0;i<_points_size;i++){
    _points[i] = points[i];
  }
  //Move Vector hull_points to private array _hull_points
  _hull_points = new 2DPoint[hull_points.size()]
  for (int i=0;i<hull_points.size();i++){
    _hull_points[i] = hull_points[i];
  }

  if (!glfwInit()){
  std::cerr<<"Error initializing glfw";   
      return -1;
  }

  HullOpenGL::createWindow();
  HullOpenGL::convertPointsCoords()
  HullOpenGL::drawPoints()
}

HullOpenGL::HullOpenGL(2DPoint points[]){
  _points_size = sizeof(points);
  _points = new 2DPoint[_points_size];
  for(int i=0;i<_points_size;i++){
    _points[i] = points[i];
  }

  if (!glfwInit()){
  std::cerr<<"Error initializing glfw";   
      return -1;
  }
  HullOpenGL::convertPointsCoords();

  HullOpenGL::createWindow();
  
  HullOpenGL::drawPoints();
}

HullOpenGL::~HullOpenGL(){
  delete[] _points;
  delete[] _GL_points;
}

void HullOpenGL::createWindow(){
  if (!glfwInit())
    return -1;

  window = glfwCreateWindow(640, 480, "Convex Hull", NULL, NULL);
  if (!window)
  {
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
}

void HullOpenGL::drawPoints(){
  while (!glfwWindowShouldClose(window)){
    glClearColor(1.0,1.0,1.0,0);
    glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS)
    for (int i=0;i<_points_size;i++){
      glVertex3f(_GL_points[i].x, _GL_points[i].y, _GL_points[i].z)
    }
    glEnd();
    glutSwapBuffers();
  }
}

void HullOpenGL::drawLines(){
  while (!glfwWindowShouldClose(window)){
    glClearColor(1.0,1.0,1.0,0);
    glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS)
    for (int i=0;i<_points_size;i++){
      glVertex3f(_GL_points[i].x, _GL_points[i].y, _GL_points[i].z)
    }
    glEnd();
    glutSwapBuffers();
  }
}

void HullOpenGL::errorCallback(int error, const char* description){ 
  fprintf(stderr, "Error: %s\n", description);
}


void HullOpenGL::convertPointsCoords(){

  for (int i=0;i<_points_size;i++){
    if (_points[i].x<x_min){
      x_min = _points[i].x;
    }else if (_points[i].x>x_max){
      x_max = _points[i].x;
    } 
    if (_points[i].y<y_min){
      y_min = _points[i].y;
    }else if (_points[i].y>y_max){
      y_max = _points[i].y;
    } 
  }
  int _x_max, _y_max = 0;
  int _x_min, _y_min = 100000000;
  
  //Max value to normalize
  int x_max_norm = (x_max-x_min)/2 + 10;
  int y_max_norm = (y_max-y_min)/2 + 10;

  //Find new Center based on the maxes and mins
  2DPoint new_center = {0,0};
  new_center.x = ((x_max-x_min)/2)+x_min;
  new_center.y = ((y_max-y_min)/2)+y_min;

  //Convert the Points to have as new_center as the new origin and normalize them
  _GL_points = new 2DPointGL[_points_size];
  for (int i=0;i<_points_size;i++){
    _GL_points[i].x = (1.0*(_points[i].x - new_center.x))/x_max_norm * 1.0;
    _GL_points[i].y = (1.0*(_points[i].y - new_center.y))/y_max_norm * 1.0;
  }


}

