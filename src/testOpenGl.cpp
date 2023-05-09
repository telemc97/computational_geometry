#include "ProjectHeaders.h"

int main(){
  int array_size = rand() % 10 + 10;
  vector<Point2D> points;
  for(int i=0; i<array_size; i++){
    points.push_back({rand() % 100, rand() % 100});
  }
  // points.resize(8);
  // points = {{0, 3}, {1, 1}, {2, 2}, {4, 4},{0, 0}, {1, 2}, {3, 1}, {3, 3}};

  ConvexHull2D convexHull(points);

  convexHull.jarvisAlgorithm();

  vector<Point2D> hull_points = convexHull.getHullPoints();

  ConvexHull2DOpenGL repre2D(points, hull_points);
  repre2D.render();
    return 0;
}