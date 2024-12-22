// n * k approach

#include "./../../lib/arr.c"
#define MAX 100

void sum(int *arr, int s, int k, int *res) {
  int l = 0, h = 0;
  int maxi = arr[h];
  while (h < k) {
    if (maxi < arr[h])
      maxi = arr[h];
    h++;
  }
  h--;
  while (h < s) {
    maxi = arr[l];
    for(int i=l;i<=h;i++)maxi = maxi < arr[i] ? arr[i] : maxi;
    res[l] = maxi;
    h++;l++;
  }
}

int main() {
  int arr[] = {1, 3, -1, -3, 5, 3, 6, 7};
  int n = 8;
  int k = 3;
  int res[n - k+1];
  sum(arr, n, k, res);
  printArr(res, n - k + 1);
}
