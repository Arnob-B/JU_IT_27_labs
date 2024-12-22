// #include <math.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
  int coeff;
  int exp;
  struct Node *next;
} Node;
int myPow(int base, int exp) {
  if (exp == 0)
    return 1;
  else
    return base * myPow(base, exp - 1);
}

int evaluatePolynomial(Node *poly, int x) {
  int res = 0;
  if (poly == NULL)
    return res;
  Node *temp = poly;
  while (temp != NULL) {
    res += temp->coeff * myPow(x, temp->exp);
    temp = temp->next;
  }
  return res;
}

struct Node *createNode(int coeff, int exp) {
  struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
  newNode->coeff = coeff;
  newNode->exp = exp;
  newNode->next = NULL;
  return newNode;
}

void insertNode(struct Node **poly, int coeff, int exp) {
  struct Node *newNode = createNode(coeff, exp);
  if (*poly == NULL) {
    *poly = newNode;
  } else {
    struct Node *temp = *poly;
    while (temp->next != NULL) {
      temp = temp->next;
    }
    temp->next = newNode;
  }
}

void printPolynomial(struct Node *poly) {
  if (poly == NULL) {
    printf("0");
    return;
  }
  while (poly != NULL) {
    printf("%dx^%d", poly->coeff, poly->exp);
    poly = poly->next;
    if (poly != NULL) {
      printf(" + ");
    }
  }
  printf("\n");
}

int main() {
  struct Node *poly1 = NULL;

  int n;
  printf("enter the number of terms : ");
  scanf("%d", &n);
  while (n--) {
    printf("enter exp  and coeff : ");
    int coeff, exp;
    scanf("%d %d", &exp, &coeff);
    insertNode(&poly1, coeff, exp);
  }
  printf("Polynomial : ");
  printPolynomial(poly1);

  int x;
  printf("Enter the value of x : ");
  scanf("%d", &x);
  printf("result is: %d ", evaluatePolynomial(poly1, x));

  return 0;
}
