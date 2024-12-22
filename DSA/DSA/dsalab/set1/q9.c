#include <stdio.h>
#include <stdlib.h>

int main() {
  int m;
  int n;
  printf("Enter the row and col : ");
  scanf("%d %d", &m, &n);
  int **array_2d = (int **)malloc(sizeof(int *) * m);
  printf("Enter the elements in the array : ");
  for (int i = 0; i < m; i++) {
    array_2d[i] = (int *)malloc(sizeof(int) * n);
  }
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      scanf("%d", &array_2d[i][j]);
    }
  }

  int *array_1d = (int *)malloc(sizeof(int) * m * n);

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      int index_1d = i * n + j;
      array_1d[index_1d] = array_2d[i][j];
    }
  }

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      int index_1d = i * n + j;
      printf("Element at (%d, %d) in 2D array is %d in 1D array\n", i, j,
             array_1d[index_1d]);
    }
  }

  return 0;
}
