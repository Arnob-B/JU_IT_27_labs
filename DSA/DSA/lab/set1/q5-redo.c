#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int coeff;
  int exp;
  struct Node *next;
} Node;

Node *createNode(int coeff, int exp) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->coeff = coeff;
  newNode->exp = exp;
  newNode->next = NULL;
  return newNode;
}

void insertNode(Node **poly, int coeff, int exp) {
  Node *newNode = createNode(coeff, exp);
  if (*poly == NULL) {
    *poly = newNode;
  } else {
    Node *temp = *poly;
    while (temp->next != NULL) {
      temp = temp->next;
    }
    temp->next = newNode;
  }
}

Node *multiplication(Node *poly1, Node *poly2) {
  Node *result = NULL;
  Node *p1 = poly1;
  Node *p2 = poly2;

  while (p1 != NULL && p2 != NULL) {
    if (p1->exp > p2->exp) {
      insertNode(&result, p1->coeff, p1->exp);
      p1 = p1->next;
    } else if (p1->exp < p2->exp) {
      insertNode(&result, p2->coeff, p2->exp);
      p2 = p2->next;
    } else {
      int sumCoeff = p1->coeff + p2->coeff;
      if (sumCoeff != 0) {
        insertNode(&result, sumCoeff, p1->exp);
      }
      p1 = p1->next;
      p2 = p2->next;
    }
  }

  while (p1 != NULL) {
    insertNode(&result, p1->coeff, p1->exp);
    p1 = p1->next;
  }

  while (p2 != NULL) {
    insertNode(&result, p2->coeff, p2->exp);
    p2 = p2->next;
  }

  return result;
}

void printPolynomial(Node *poly) {
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
  Node *poly1 = NULL, *poly2 = NULL, *result = NULL;

  int n;
  printf("enter the number of terms : ");
  scanf("%d", &n);
  while (n--) {
    printf("enter exp  and coeff : ");
    int coeff, exp;
    scanf("%d %d", &exp, &coeff);
    insertNode(&poly1, coeff, exp);
  }
  printf("enter the number of terms : ");
  scanf("%d", &n);
  while (n--) {
    printf("enter exp  and coeff : ");
    int coeff, exp;
    scanf("%d %d", &exp, &coeff);
    insertNode(&poly2, coeff, exp);
  }

  printf("Polynomial 1: ");
  printPolynomial(poly1);

  printf("Polynomial 2: ");
  printPolynomial(poly2);

  result = multiplication(poly1, poly2);

  printf("Resultant Polynomial: ");
  printPolynomial(result);

  return 0;
}
