#include <iostream>
#include "Point.h"
#include <vector>
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Core>
#include "MergeSort.h" 

using namespace std;

#define INF 10000
static Point2D nil = {INF, INF};

class ConvexHull2D{
  public:
  ConvexHull2D(vector<Point2D> points);

  vector<Point2D> getHullPoints();

  private:

  vector<Point2D> _points;
  vector<Point2D> _hull_points;

  int pointsOrientation(Point2D& pointA, Point2D& pointB, Point2D& pointC);

  void jarvisAlgorithm();

};
