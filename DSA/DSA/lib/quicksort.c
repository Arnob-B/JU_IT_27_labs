void quickSort(int *A, int p,int q){
  int x = A[p];
  int ind = p;
  for(int i =p+1;i<q; i++){
    if(A[i]>p){p = p+1;
      int temp = A[p];
      A[p] = A[i];
      A[i] = temp;
    }
  }
}
int main(){
  //partitioning with pivot x and createing the subarray

}
