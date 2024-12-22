#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char *str) {
  int n = strlen(str);
  for (int i = 0; i < n / 2; i++) {
    char temp = str[i];
    str[i] = str[n - i - 1];
    str[n - i - 1] = temp;
  }
}

char *addLargeNumbers(char *num1, char *num2) {
  int len1 = strlen(num1);
  int len2 = strlen(num2);
  int maxLen = len1 > len2 ? len1 : len2;

  char *result = (char *)malloc(maxLen + 2);
  result[maxLen + 1] = '\0';
  reverse(num1);
  reverse(num2);
  int carry = 0, i;
  for (i = 0; i < maxLen; i++) {
    int digit1 = i < len1 ? num1[i] - '0' : 0;
    int digit2 = i < len2 ? num2[i] - '0' : 0;
    int sum = digit1 + digit2 + carry;
    result[i] = (sum % 10) + '0';
    carry = sum / 10;
  }

  if (carry) {
    result[i] = carry + '0';
    i++;
  }

  result[i] = '\0';

  reverse(result);
  return result;
}

int main() {
  char num1[1000], num2[1000];

  printf("Enter the first large number: ");
  scanf("%s", num1);
  printf("Enter the second large number: ");
  scanf("%s", num2);
  char *result = addLargeNumbers(num1, num2);
  printf("Sum: %s\n", result);
  free(result);
  return 0;
}
