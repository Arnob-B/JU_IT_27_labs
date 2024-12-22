#include <stdio.h>
// #include <stdlib.h>
struct Term {
  int coeff;
  int exp;
};

void multiplyPolynomials(struct Term poly1[], int n1, struct Term poly2[],
                         int n2, struct Term result[], int *res_size) {
  *res_size = 0;

  for (int i = 0; i < n1; i++) {
    for (int j = 0; j < n2; j++) {
      int coeff = poly1[i].coeff * poly2[j].coeff;
      int exp = poly1[i].exp + poly2[j].exp;

      int found = 0;
      for (int k = 0; k < *res_size; k++) {
        if (result[k].exp == exp) {
          result[k].coeff += coeff;
          found = 1;
          break;
        }
      }

      if (!found) {
        result[*res_size].coeff = coeff;
        result[*res_size].exp = exp;
        (*res_size)++;
      }
    }
  }
}

void printPolynomial(struct Term poly[], int n) {
  for (int i = 0; i < n; i++) {
    printf("%dx^%d", poly[i].coeff, poly[i].exp);
    if (i < n - 1) {
      printf(" + ");
    }
  }
  printf("\n");
}

int main() {
  struct Term poly1[] = {{7, 7}, {2, 3}, {6, 1}}; // 7x^7 + 2x^3 +6x
  struct Term poly2[] = {{4, 12}, {2, 0}};        // 4x^12 + 2

  int n1 = sizeof(poly1) / sizeof(poly1[0]);
  int n2 = sizeof(poly2) / sizeof(poly2[0]);

  struct Term result[n1 * n2];
  int res_size;

  multiplyPolynomials(poly1, n1, poly2, n2, result, &res_size);

  printf("Polynomial 1: ");
  printPolynomial(poly1, n1);

  printf("Polynomial 2: ");
  printPolynomial(poly2, n2);

  printf("Resultant Polynomial after multiplication: ");
  printPolynomial(result, res_size);

  return 0;
}
