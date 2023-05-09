#include "ConvexHull2D.h"

ConvexHull2D::ConvexHull2D(vector<Point2D>& points){
  for (int i=0;i<points.size();i++){
    _points.push_back(points[i]);
  }
}

//0:CW, 1:CCW, -1:Coolinear 
int ConvexHull2D::CW(Point2D& pointA, Point2D& pointB, Point2D& pointC){
  Eigen::Matrix3i detMatrix;
  detMatrix <<1, pointA.x, pointA.y, 1, pointB.x, pointB.y, 1, pointC.x, pointC.y;
  int det = 0;
  det = detMatrix.determinant();
  return det;
}

int ConvexHull2D::jarvisAlgorithm(){
  if (_points.size()<3){
    perror("Convex Hull not Possible (Less than 3 Points Given)");
    return -1;
  }
  _hull_points.resize(0);
  int min_x_idx=0;
  for (int i=1;i<_points.size();i++){
    if(_points[i].x<_points[min_x_idx].x){
      min_x_idx=i;
    }
  }
  int p=min_x_idx;
  int q;
  do{
    _hull_points.push_back(_points[p]);
    q=(p+1)%_points.size();
    for (int i=0;i<_points.size();i++){
      if (CW(_points[p], _points[i], _points[q])<0){
        q=i;
      }
    }
    p=q;
  }while(p!=min_x_idx);
  return 0;
}
//ToDo: Check it doesnt work
int ConvexHull2D::quickHullFunc(Point2D& pointA, Point2D& pointB, int side){
  int max_dist_idx = -1;
  int max_dist = 0;

  for (int i=0;i<_points.size();i++){
    int temp_dist = abs(CW(pointA, pointB, _points[i]));
    int point_side;

    if (CW(pointA, pointB, _points[i])>0){
      point_side = -1;  
    }else if(CW(pointA, pointB, _points[i])<0){
      point_side = 1;
    }else{
      point_side = 0;
    }

    if (point_side == side && temp_dist > max_dist){
      max_dist_idx = i;
      max_dist = temp_dist;
    }
  }

  if (max_dist_idx == -1){
    _hull_points.push_back(pointA);
    _hull_points.push_back(pointB);
    return 0;
  }
  //Recirsive for the 2 parts derived by the _points[max_dist_idx]
  quickHullFunc(_points[max_dist_idx], pointA, -CW(_points[max_dist_idx], pointA, pointB));
  quickHullFunc(_points[max_dist_idx], pointB, -CW(_points[max_dist_idx], pointB, pointA));
  return 0;
}

int ConvexHull2D::quickHullAlgorithm(){
  if (_points.size()<3){
    perror("Convex Hull not Possible (Less than 3 Points Given)");
    return -1;
  }
  _hull_points.resize(0);
  int min_x_idx=0, max_x_idx=0;
  for (int i=1;i<_points.size();i++){
    if (_points[i].x<_points[min_x_idx].x){
      min_x_idx = i;
    }
    if (_points[i].x>_points[max_x_idx].x){
      max_x_idx = i;
    }
  }
  //quickHull call here for hull points on one side
  quickHullFunc(_points[min_x_idx], _points[max_x_idx], 1);
  //quickHull call here for hull points on the other side
  quickHullFunc(_points[min_x_idx], _points[max_x_idx], -1);
  return 0;
}

vector<Point2D> ConvexHull2D::getHullPoints(){
  return _hull_points;
}