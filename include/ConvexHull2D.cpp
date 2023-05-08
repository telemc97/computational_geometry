#include "ConvexHull2D.h"

ConvexHull2D::ConvexHull2D(vector<Point2D>& points){
  for (int i=0;i<points.size();i++){
    _points.push_back(points[i]);
  }
  if (_points.size()>3){
    jarvisAlgorithm();
  }
}

//0:CW, 1:CCW, 2:Coolinear 
int ConvexHull2D::pointsOrientation(Point2D& pointA, Point2D& pointB, Point2D& pointC){
  Eigen::Matrix3i detMatrix;
  detMatrix <<1, pointA.x, pointA.y, 1, pointB.x, pointB.y, 1, pointC.x, pointC.y;
  int det_eval = (pointB.y - pointA.y) * (pointC.x - pointB.x) - (pointB.x - pointA.x) * (pointC.y - pointB.y);
  int determ = detMatrix.determinant();
  if (determ<0){
    return 0;
  }else if (determ>0){
    return 1;
  }else{
    return 2;
  }
}

void ConvexHull2D::jarvisAlgorithm(){
  // mainSortingSingleThread(_points, 0, array_size-1);
  int l=0;
  for (int i=1;i<_points.size();i++){
    if(_points[i].x<_points[l].x){
      l=i;
    }
  }
  int p=l;
  int q;
  do{
    _hull_points.push_back(_points[p]);
    q=(p+1)%_points.size();
    for (int i=0;i<_points.size();i++){
      if (pointsOrientation(_points[p], _points[i], _points[q])==0){
        q=i;
      }
    }
    p=q;
  }while(p!=l);
}

vector<Point2D> ConvexHull2D::getHullLines(){
  return _hull_points;
}