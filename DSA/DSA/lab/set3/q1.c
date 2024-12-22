#include <stdio.h>
#include <stdlib.h>

struct Node {
  int data;
  struct Node *left;
  struct Node *right;
};

struct Node *createNode(int data) {
  struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
  newNode->data = data;
  newNode->left = NULL;
  newNode->right = NULL;
  return newNode;
}

struct Node *insertNode(struct Node *root, int data) {
  if (root == NULL) {
    return createNode(data);
  }
  if (data < root->data) {
    root->left = insertNode(root->left, data);
  } else if (data > root->data) {
    root->right = insertNode(root->right, data);
  }
  return root;
}

void inOrder(struct Node *root) {
  if (root != NULL) {
    inOrder(root->left);
    printf("%d ", root->data);
    inOrder(root->right);
  }
}

void preOrder(struct Node *root) {
  if (root != NULL) {
    printf("%d ", root->data);
    preOrder(root->left);
    preOrder(root->right);
  }
}

void postOrder(struct Node *root) {
  if (root != NULL) {
    postOrder(root->left);
    postOrder(root->right);
    printf("%d ", root->data);
  }
}

int main() {
  struct Node *root = NULL;
  int choice, value;

  do {
    printf("\nMenu:\n");
    printf("1. Insert a node into the binary tree\n");
    printf("2. Perform in-order traversal\n");
    printf("3. Perform pre-order traversal\n");
    printf("4. Perform post-order traversal\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
      printf("Enter the value to insert: ");
      scanf("%d", &value);
      root = insertNode(root, value);
      break;
    case 2:
      printf("In-order traversal: ");
      inOrder(root);
      printf("\n");
      break;
    case 3:
      printf("Pre-order traversal: ");
      preOrder(root);
      printf("\n");
      break;
    case 4:
      printf("Post-order traversal: ");
      postOrder(root);
      printf("\n");
      break;
    case 5:
      printf("Exiting program.\n");
      break;
    default:
      printf("Invalid choice! Please try again.\n");
    }
  } while (choice != 5);

  return 0;
}
