#include <stdio.h>
#define MAX 100

typedef struct {
  int row, col, value;
} SME;

int add(SME mat[], int size1, SME mat2[], int size2, SME res[]) {
  int i = 0, j = 0, k = 0;
  while (i < size1 && j < size2) {
                if (mat1[i].row < mat2[j].row || (mat1[i].row == mat2[j].row && mat1[i].col < mat2[j].col){
      res[k++] = mat1[i++];
		}
		else if (mat1[i].row > mat2[j].row || (mat1[i].row == mat2[j].row && mat1[i].col > mat2[j].col){
      res[k++] = mat2[j++];
                }
		else{
      res[k] = mat1[i];
      res[k++].value = mat1[i++].value + mat2[j++].value;
		}
  }
  while (i < size1) {
    res[k++] = mat1[i++];
  }
  while (j < size2) {
    res[k++] = mat2[j++];
  }
  return k;
}
}

void print(SME mat[], int size) {
  printf("Row\tCol\tValue\n");
  int i;
  for (i = 0; i < size; i++) {
    printf("%d\t%d\t%d\n", mat[i].row, mat[i].col, mat[i].value);
  }
}

int main() {
  SME mat1[MAX], mat2[MAX], res[MAX];
  int size1, size2, ResSize;
  printf("Enter the no. of non-zero elements in mat1: ");
  scanf("%d", &size1);
  printf("Enter the non-zero elements in mat1: ");
  int i;
  for (i = 0; i < size1; i++) {
    scanf("%d %d %d", &mat1[i].row, &mat1[i].col, &mat1[i].value);
  }
  printf("Enter the no. of non-zero elements in mat2: ");
  scanf("%d", &size2);
  for (i = 0; i < size2; i++) {
    scanf("%d %d %d", &mat2[i].row, &mat2[i].col, &mat2[i].value);
  }
  ResSize = add(mat1, size1, mat2, size2, res);
  printf("Result: ");
  print(res, ResSize);
  return 0;
}
