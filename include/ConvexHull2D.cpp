#include "ConvexHull2D.h"

ConvexHull2D::ConvexHull2D(vector<Point2D>& points){
  for (int i=0;i<points.size();i++){
    _points.push_back(points[i]);
  }
  if (_points.size()>3){
    jarvisAlgorithm();
  }
}

int ConvexHull2D::pointsOrientation(Point2D& pointA, Point2D& pointB, Point2D& pointC){
  Eigen::Matrix3i detMatrix;
  detMatrix << 1, pointA.x, pointA.y, 1, pointB.x, pointB.y, 1, pointC.x, pointC.y;
  double determ = detMatrix.determinant();
  if (determ<0){
    return 0; //CW
  }else if(determ>0){
    return 1; //CCW
  }else{
    return 2; //Coolinear
  }
}

void ConvexHull2D::jarvisAlgorithm(){
  // mainSortingSingleThread(_points, 0, array_size-1);
  int l=0;
  for (int i=0;i<_points.size();i++){
    if(_points[i].x<_points[l].x){
      l=i;
    }
  }
  //the leftmost point is the first point after mergesort l=0 & q=0.
  int p=l,q;
  do{
    _hull_points.push_back(_points[p]);
    q=(p+1)%_points.size();
    for (int i=0;i<_points.size();i++){
      if (pointsOrientation(_points[p], _points[i], _points[q])==1){
        q=i;
      }
      p=q;
    }
  }while(p!=l);
}

vector<Point2D> ConvexHull2D::getHullPoints(){
  return _hull_points;
}