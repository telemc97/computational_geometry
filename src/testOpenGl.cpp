#include "ProjectHeaders.h"

void printPointArray(vector<Point2D>& points){
  for(Point2D point : points){
    cout << '(' << point.x << ',' << point.y << ')';
  } 
}

int main(){
  int array_size = rand() % 10 + 10;
  vector<Point2D> points;
  for(int i=0; i<array_size; i++){
    points.push_back({rand() % 100, rand() % 100});
  }
  cout << "\nArray of Points: \n";
  printPointArray(points);

  ConvexHull2D convexHull(points);

  vector<Point2D> hull_points = convexHull.getHullPoints();

  ConvexHull2DOpenGL repre2D(points, hull_points);
  repre2D.render();
    return 0;
}