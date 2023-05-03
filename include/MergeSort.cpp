#include"MergeSort.h"

void mergeSingleThread(2DPoint points[], const int& left, const int& mid, const int& right){
  int const sub_array_1_size = mid - left + 1;
  int const sub_array_2_size = right - mid;

  2DPoint* left_array = new 2DPoint[sub_array_1_size];
  2DPoint* right_array = new 2DPoint[sub_array_2_size];

  for (int i=0; i<sub_array_1_size; i++){left_array[i]=points[left+i];}
  for (int j=0; j<sub_array_2_size; j++){right_array[j]=points[mid + 1 + j];}

  int index_sub_array_1=0, index_sub_array_2=0;

  int index_merged_array = left;

  while (index_sub_array_1 < sub_array_1_size && index_sub_array_2 < sub_array_2_size){
    if (left_array[index_sub_array_1].x<=right_array[index_sub_array_2].x){
      points[index_merged_array] = left_array[index_sub_array_1];
      index_sub_array_1++;
    }else{
      points[index_merged_array] = right_array[index_sub_array_2];
      index_sub_array_2++;
    }
    index_merged_array++;
  }
  while (index_sub_array_1<sub_array_1_size){
    points[index_merged_array] = left_array[index_sub_array_1];
    index_sub_array_1++;
    index_merged_array++;
  }
  while (index_sub_array_2<sub_array_2_size){
    points[index_merged_array] = right_array[index_sub_array_2];
    index_sub_array_2++;
    index_merged_array++;
  }
  delete[] left_array;
  delete[] right_array;
}

void mainSortingSingleThread(2DPoint points[], const int& begin, const int& end){
  if (begin >= end)
    return;
  int mid = begin + (end-begin)/2;
  mainSortingSingleThread(points, begin, mid);
  mainSortingSingleThread(points, mid+1, end);
  mergeSingleThread(points, begin, mid, end);
}