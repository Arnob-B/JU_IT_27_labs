#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
  int row, col, value;
  struct Node *next;
} Node;

void createNode(Node **root, int i, int j, int val) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->value = val;
  newNode->row = i;
  newNode->col = j;
  newNode->next = NULL;
  if (*root == NULL) {
    *root = newNode;
    return;
  }
  Node *temp = *root;
  while (temp->next != NULL) {
    temp = temp->next;
  }
  temp->next = newNode;
}
void printMat(Node *root) {
  Node *temp = root;
  int i = 0, j = 0;
  while (temp != NULL) {
    if (temp->row > i)
      i = temp->row;
    if (temp->col > j)
      j = temp->col;
    temp = temp->next;
  }
  for (int a = 0; a <= i; a++) {
    for (int b = 0; b <= j; b++) {
      Node *temp = root;
      int flag = 1;
      while (temp != NULL) {
        if (temp->row == a && temp->col == b) {
          flag = 0;
          printf("%d,", temp->value);
          break;
        }
        temp = temp->next;
      }
      if (flag)
        printf("0,");
    }
    printf("\n");
  }
}

Node *search(Node *root, int i, int j) {
  if (root == NULL)
    return NULL;
  if (root->row == i && root->col == j)
    return root;
  return search(root->next, i, j);
}
Node *addition(Node *arr1, Node *arr2) {
  Node *newNode = NULL;
  Node *temp = arr1;
  while (temp != NULL) {
    Node *otherNode = search(arr2, temp->row, temp->col);
    if (otherNode != NULL) {
      createNode(&newNode, temp->row, temp->col,
                 temp->value + otherNode->value);
    } else
      createNode(&newNode, temp->row, temp->col, temp->value);
    temp = temp->next;
  }
  temp = arr2;
  while (temp != NULL) {
    Node *otherNode = search(newNode, temp->row, temp->col);
    if (otherNode == NULL) {
      createNode(&newNode, temp->row, temp->col, temp->value);
    }
    temp = temp->next;
  }
  return newNode;
}

int main() {
  Node *root1 = NULL;
  Node *root2 = NULL;
  int n;
  printf("Enter the no of elements in the first matrix : ");
  scanf("%d", &n);
  while (n--) {
    int i, j, val;
    printf("enter the row , col , val : ");
    scanf("%d %d %d", &i, &j, &val);
    createNode(&root1, i, j, val);
  }
  printMat(root1);
  printf("Enter the no of elements in the second matrix : ");
  scanf("%d", &n);
  while (n--) {
    int i, j, val;
    printf("enter the row , col , val : ");
    scanf("%d %d %d", &i, &j, &val);
    createNode(&root2, i, j, val);
  }
  printMat(root2);
  printf("\n matrix after addition is \n");
  Node *res = addition(root1, root2);
  printMat(res);
  return 0;
}
