#include "ConvexHull2D.h"


ConvexHull2D::ConvexHull2D(2DPoint points[]){
  _points_size = sizeof(points);
  _points = new Point[size];
  for (int i=0;i<_points_size;i++){
    _points[i] = points;
  }
}

int ConvexHull2D::pointsOrientation(2DPoint& pointA, 2DPoint& pointB, 2DPoint& pointC){
  Eigen::Matrix3i detMatrix {{1, pointA.x, pointA.y}, {1, pointB.x, pointB.y}, {1, pointC.x, pointC.y}};
  double determ = detMatrix.determinant();
  if (determ<0){
    return 0; //CW
  }else if(determ>0){
    return 1; //CCW
  }else{
    return 2; //Coolinear
  }
}

vector<2DPoint> ConvexHull2D::jarvisAlgorithm(){
  if (n<3) return;
  mainSortingSingleThread(_points, 0, array_size-1);
  int array_size = sizeof(_points);
  vector<2DPoint> hull_points;

  //the leftmost point is the first point after mergesort l=0 & q=0.
  int q,p;
  do{
    hull_points.push_back(_points[])
    q=(1)%array_size;
    for (int i=0;i<array_size;i++){
      if (pointsOrientation(_points[0], _points[i], _points[q])==1){
        q=i;
      }
      p=q;
    }
  }while(_points[p]!=_points[0])

  return hull_points;
}