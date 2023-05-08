#include "ConvexHull2DOpenGL.h"

ConvexHull2DOpenGL::ConvexHull2DOpenGL(vector<Point2D>& points, vector<Point2D>& hull_points){
  for(int i=0;i<points.size();i++){
    _points.push_back(points[i]);
  }
  //Move Vector "hull_points" to private array "_hull_points"
  _hull_points = hull_points;
  for (int i=0;i<hull_points.size();i++){
    _hull_points.push_back(hull_points[i]);
  }
  _GL_points = ConvexHull2DOpenGL::convertPointsCoords(_points);
  _GL_hull_points = ConvexHull2DOpenGL::convertPointsCoords(_hull_points);
}

ConvexHull2DOpenGL::ConvexHull2DOpenGL(vector<Point2D>& points){
  for(int i=0;i<points.size();i++){
    _points.push_back(points[i]);
  }
  _GL_points = ConvexHull2DOpenGL::convertPointsCoords(_points);
}

ConvexHull2DOpenGL::ConvexHull2DOpenGL(){
  ConvexHull2DOpenGL::createWindow();
  _GL_points.resize(5);
  _GL_points[0] = {0.5, 0.0, 0.0};
  _GL_points[1] = {-0.5, 0.0, 0.0};
  _GL_points[2] = {0.0, 0.5, 0.0};
  _GL_points[3] = {0.0, -0.5, 0.0};
  _GL_points[4] = {0.0, 0.0, 0.0};
  ConvexHull2DOpenGL::drawPoints(_GL_points);
}

ConvexHull2DOpenGL::~ConvexHull2DOpenGL(){
  if (_GL_window != NULL) delete _GL_window;
}

void ConvexHull2DOpenGL::render(){
  ConvexHull2DOpenGL::createWindow();
  while(!glfwWindowShouldClose(_GL_window)){
    ConvexHull2DOpenGL::initRender();
    ConvexHull2DOpenGL::drawPoints(_GL_points);
    glfwSwapBuffers(_GL_window);
    if (_GL_hull_points.size()>0){
      ConvexHull2DOpenGL::drawHullLines(_GL_hull_points);
      glfwSwapBuffers(_GL_window);
    }
    glfwPollEvents();
  }
  glfwTerminate();
}

//Set Functions
void ConvexHull2DOpenGL::setCoordNormValue(float value){
  _norm_value = value;
}

void ConvexHull2DOpenGL::setPointColor4f(float r, float g, float b, float a){
  _point_color = {r,g,b,a};
}

void ConvexHull2DOpenGL::setLineColor4f(float r, float g, float b, float a){
  _line_color = {r,g,b,a};
}

void ConvexHull2DOpenGL::setBackgroundColor(float r, float g, float b, float a){
  _background_color = {r,g,b,a};
}

int ConvexHull2DOpenGL::createWindow(){
  glfwSetErrorCallback(error_callback);
  if (!glfwInit())
      exit(EXIT_FAILURE);
  _GL_window = glfwCreateWindow(640, 480, "Convex Hull", NULL, NULL);
  if (!_GL_window){
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  glfwMakeContextCurrent(_GL_window);
  glfwSetKeyCallback(_GL_window, key_callback);
  return 0;
}

int ConvexHull2DOpenGL::drawPoints(vector<PointGL2D>& GL_points){
  glBegin(GL_POINTS);
  for (int i=0;i<GL_points.size();i++){
    glColor4f(_point_color.r, _point_color.g, _point_color.b, _point_color.a);
    glVertex3f(GL_points[i].x, GL_points[i].y, GL_points[i].z);
  }
  glEnd();
  return 0;
}

int ConvexHull2DOpenGL::drawHullLines(vector<PointGL2D>& GL_hull_points){
  glBegin(GL_LINES);
  for (int i=0;i+1<GL_hull_points.size();i+=2){
    glColor4f(_line_color.r, _line_color.g, _line_color.b, _line_color.a);
    glVertex3f(GL_hull_points[i].x, GL_hull_points[i].y, GL_hull_points[i].z);
    glVertex3f(GL_hull_points[i+1].x, GL_hull_points[i+1].y, GL_hull_points[i+1].z);
  }
  glEnd();
  return 0;
}

vector<PointGL2D> ConvexHull2DOpenGL::convertPointsCoords(const vector<Point2D>& points){
  int x_min, y_min, x_max, y_max; 
  y_min = y_max = points[0].y;
  x_min = x_max = points[0].x;

  for (int i=0;i<points.size();i++){
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

  //Find new Center based on the maxes and mins
  Point2D new_center = {0,0};
  new_center.x = ((x_max-x_min)/2)+x_min;
  new_center.y = ((y_max-y_min)/2)+y_min;

  float norm_max = 0.0f;
  //Find max distance between x_center_max and y_center_max and x_max and y_max respectivelly to use in normalization
  float x_dist = x_max - new_center.x;
  float y_dist = y_max - new_center.y;
  float norm_dist;
  if (x_dist>y_dist){
    norm_dist = x_dist;
  }else{
    norm_dist = y_dist;
  }

  //Convert the Points to have as new_center as the new origin and normalize them
  vector<PointGL2D> GL_points;
  for (int i=0;i<points.size();i++){
    GLfloat x = (_norm_value*(_points[i].x - new_center.x))/norm_dist * 1.0f;
    GLfloat y = (_norm_value*(_points[i].y - new_center.y))/norm_dist * 1.0f;
    GLfloat z = 0.0f;
    GL_points.push_back({x, y, z});
  }

  return GL_points;
}