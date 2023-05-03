#include "ProjectHeaders.h"

int main(){
  int array_size = rand() % 10 + 10;
  2DPoint* points = new Point[array_size];
  for(int i=0; i<array_size; i++){
    points[i].x = rand() % 100;
    points[i].y = rand() % 100;
  }
  cout << "\nIntial array is \n";
  printArray(points, array_size);

  mainSortingSingleThread(points, 0, array_size-1);

  cout << "\nSorted array is \n";
  printArray(points, array_size);

  delete[] points;
  return 0;
}