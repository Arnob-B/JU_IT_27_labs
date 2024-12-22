#include"./arr.c"
int partitioning(int * arr, int i ,int j ,int n){
  int k= arr[i];
  int start = i+1;
  while(i<j){
    while( arr[i]<k ){
      i++;
    }
    while(arr[j]>k){
      j--;
    }
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
  }
  int temp = arr[j];
  arr[j] = arr[start];
  arr[start] = temp;
  return j;
}
void quicksort(int *arr, int i, int j,int n){
  if(i<j){
  int p = partitioning(arr,i,j,n);
  if(p > i)quicksort(arr,i,p-1,n);
  if(p<j)quicksort(arr,p+1,j,n);
  }
}


int main(){
  int arr[] = {7,3,2,6,4,5,9};
  quicksort(arr,0,6,7);
  printArr(arr, 7);
}
