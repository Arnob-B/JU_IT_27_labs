#include<stdio.h>

int counter(int * arr, int n){
  int maxi = -1;
  int count= 0;
  for(int i=0;i<n;i++){
    if(i == 0) {
      maxi = arr[i];
      count++;
    }
    else{
      if(arr[i] > maxi){
        count++;
        maxi = arr[i];
      }
    }
  }
  return count;
}
int main(){
  int n = 5;
  int arr[5] = {10, 5, 11, 6, 20};
  printf("%d ",counter(arr,n));
}
