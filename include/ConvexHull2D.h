#include <iostream>
#include "Point.h"
#include <vector>
#include <Eigen/Core>
#include <Eigen/Dense>
#include "MergeSort.h" 

using namespace std;

#define INF 10000
static Point nil = {INF, INF, 0 ,0};

class ConvexHull2D{
  public:
  ConvexHull2D(Point points[]);

  virtual ~ConvexHull2D();

  private:

  Point* _points;
  int _points_size;

  int pointsOrientation(Point& pointA, Point& pointB, Point& pointC);

  vector<Point> jarvisAlgorithm(Point _points[]);

};
