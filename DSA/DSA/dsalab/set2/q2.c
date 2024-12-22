#include <stdio.h>
#include <stdlib.h>

struct Node {
  int data;
  struct Node *next;
};

struct Node *createNode(int data) {
  struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
  newNode->data = data;
  newNode->next = NULL;
  return newNode;
}

struct Node *createCircularLinkedList(int n) {
  struct Node *head = NULL;
  struct Node *temp = NULL;
  struct Node *current = NULL;

  for (int i = 1; i <= n; i++) {
    temp = createNode(i);
    if (head == NULL) {
      head = temp;
      current = head;
    } else {
      current->next = temp;
      current = current->next;
    }
    current->next = head;
  }
  return head;
}

int josephus(int n, int k) {

  struct Node *head = createCircularLinkedList(n);
  struct Node *prev = NULL;
  struct Node *current = head;

  while (current->next != current) {

    for (int i = 1; i < k; i++) {
      prev = current;
      current = current->next;
    }

    printf("Person at position %d is eliminated.\n", current->data);
    prev->next = current->next;
    free(current);
    current = prev->next;
  }

  int result = current->data;
  free(current);
  return result;
}

int main() {
  int n, k;

  printf("Enter the number of people (n): ");
  scanf("%d", &n);
  printf("Enter the step count (k): ");
  scanf("%d", &k);

  int survivor = josephus(n, k);
  printf("The last remaining person is at position %d\n", survivor);

  return 0;
}
