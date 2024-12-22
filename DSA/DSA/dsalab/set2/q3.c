#include <stdio.h>
#include <stdlib.h>

struct Node {
  int data;
  struct Node *next;
  struct Node *prev;
};

struct Node *createNode(int data) {
  struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
  newNode->data = data;
  newNode->next = NULL;
  newNode->prev = NULL;
  return newNode;
}

void insertNode(struct Node **head, int data, int position) {
  struct Node *newNode = createNode(data);
  if (*head == NULL) {
    *head = newNode;
    return;
  }

  if (position == 0) {
    newNode->next = *head;
    (*head)->prev = newNode;
    *head = newNode;
    return;
  }

  struct Node *temp = *head;
  for (int i = 0; i < position - 1 && temp->next != NULL; i++) {
    temp = temp->next;
  }

  newNode->next = temp->next;
  newNode->prev = temp;

  if (temp->next != NULL) {
    temp->next->prev = newNode;
  }
  temp->next = newNode;
}

void deleteNode(struct Node **head, int position) {
  if (*head == NULL) {
    printf("List is empty\n");
    return;
  }

  struct Node *temp = *head;

  if (position == 0) {
    *head = temp->next;
    if (*head != NULL) {
      (*head)->prev = NULL;
    }
    free(temp);
    return;
  }

  for (int i = 0; i < position && temp != NULL; i++) {
    temp = temp->next;
  }

  if (temp == NULL) {
    printf("Position out of bounds\n");
    return;
  }

  if (temp->next != NULL) {
    temp->next->prev = temp->prev;
  }

  if (temp->prev != NULL) {
    temp->prev->next = temp->next;
  }

  free(temp);
}

int countNodes(struct Node *head) {
  int count = 0;
  while (head != NULL) {
    count++;
    head = head->next;
  }
  return count;
}

void reversePrint(struct Node *head) {
  if (head == NULL) {
    printf("List is empty\n");
    return;
  }

  struct Node *tail = head;
  while (tail->next != NULL) {
    tail = tail->next;
  }

  while (tail != NULL) {
    printf("%d -> ", tail->data);
    tail = tail->prev;
  }
  printf("NULL\n");
}

void reverseList(struct Node **head) {
  struct Node *temp = NULL;
  struct Node *current = *head;

  while (current != NULL) {
    temp = current->prev;
    current->prev = current->next;
    current->next = temp;
    current = current->prev;
  }

  if (temp != NULL) {
    *head = temp->prev;
  }
}

void printList(struct Node *head) {
  while (head != NULL) {
    printf("%d -> ", head->data);
    head = head->next;
  }
  printf("NULL\n");
}

int main() {
  struct Node *head = NULL;

  insertNode(&head, 1, 0);
  insertNode(&head, 2, 1);
  insertNode(&head, 3, 2);
  insertNode(&head, 4, 3);
  printf("Original List: ");
  printList(head);

  deleteNode(&head, 1);
  printf("After Deleting at position 1: ");
  printList(head);

  printf("Number of nodes: %d\n", countNodes(head));

  printf("Reverse Print: ");
  reversePrint(head);

  reverseList(&head);
  printf("Reversed List: ");
  printList(head);

  return 0;
}
