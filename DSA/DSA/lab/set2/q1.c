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

void insertNode(struct Node **head, int data, int position) {
  struct Node *newNode = createNode(data);
  if (position == 0) {
    newNode->next = *head;
    *head = newNode;
    return;
  }

  struct Node *temp = *head;
  for (int i = 0; i < position - 1 && temp != NULL; i++) {
    temp = temp->next;
  }

  if (temp == NULL) {
    printf("Position out of bounds\n");
    free(newNode);
    return;
  }

  newNode->next = temp->next;
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
    free(temp);
    return;
  }

  struct Node *prev = NULL;
  for (int i = 0; i < position && temp != NULL; i++) {
    prev = temp;
    temp = temp->next;
  }

  if (temp == NULL) {
    printf("Position out of bounds\n");
    return;
  }

  prev->next = temp->next;
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

void reversePrintUtil(struct Node *head) {
  if (head == NULL)
    return;
  reversePrintUtil(head->next);
  printf("%d -> ", head->data);
}

void reversePrint(struct Node *head) {
  reversePrintUtil(head);
  printf("NULL\n");
}

void reverseList(struct Node **head) {
  struct Node *prev = NULL;
  struct Node *current = *head;
  struct Node *next = NULL;

  while (current != NULL) {
    next = current->next;
    current->next = prev;
    prev = current;
    current = next;
  }
  *head = prev;
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

  char ch = 'y';
  while (ch == 'y') {
    printf("press 1. to insert node \n");
    printf("press 2. to print node\n");
    printf("press 3. delete node \n");
    printf("press 4. print reverse list \n");
    printf("press 5. reverse list \n");
    printf("Enter the choice : ");
    char choice;
    scanf("%s", &choice);
    switch (choice) {
    case ('1'): {
      int val, pos;
      char ch;
      printf("Enter the position : ");
      scanf("%d %d", &val, &pos);
      insertNode(&head, val, pos);
      break;
    }
    case ('2'): {
      printList(head);
      break;
    }
    case ('3'): {
      printf("Enter the position : ");
      int pos;
      scanf("%d", &pos);
      deleteNode(&head, pos);
      break;
    }
    case ('4'): {
      reversePrint(head);
      break;
    }
    case ('5'): {
      reverseList(&head);
      break;
    }
    }
    printf("want to continue press y : ");
    scanf("%s", &ch);
  }
  return 0;
}
