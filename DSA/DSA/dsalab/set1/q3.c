#include <stdio.h>
#include <stdlib.h>

struct Node {
  int coeff;
  int exp;
  struct Node *next;
};

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

struct Node *addPolynomials(struct Node *poly1, struct Node *poly2) {
  struct Node *result = NULL;
  struct Node *p1 = poly1;
  struct Node *p2 = poly2;

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
  struct Node *poly1 = NULL, *poly2 = NULL, *result = NULL;

  // 3*x^7+4*x*2 + 1
  insertNode(&poly1, 3, 7);
  insertNode(&poly1, 4, 2);
  insertNode(&poly1, 1, 0);

  // 4x^6 + 2x + 5
  insertNode(&poly2, 4, 6);
  insertNode(&poly2, 2, 1);
  insertNode(&poly2, 5, 0);

  printf("Polynomial 1: ");
  printPolynomial(poly1);

  printf("Polynomial 2: ");
  printPolynomial(poly2);

  result = addPolynomials(poly1, poly2);

  printf("Resultant Polynomial: ");
  printPolynomial(result);

  return 0;
}
