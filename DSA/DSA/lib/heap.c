#include<stdio.h>
void swap(int * a1,int *a2){
  int temp = *a1;
  *a1 = *a2;
  *a2 = temp;
}
void check(int * arr,int n,  int i){
  if(i*2 <=n &&  arr[i] == arr[(i*2 )-1]){
    swap(arr+i, arr + (i*2)-1);
    check(arr, n,i *2);
  }
  if(i*2 +1 <=n &&  arr[i] == arr[(i*2)]){
    swap(arr+i, arr + (i*2));
    check(arr, n,i *2 + 1);
  }
}
void heapify(int * arr, int n){
  int l = n;
  while(l>0){
    check(arr,n,l);
  }
}


int main(){
  int arr[7] = {12,3,3,4,3,2,1};
  heapify(arr,7);
  for(int i =0;i<7;i++){
    printf("%d,",arr[i]);
  }
}
