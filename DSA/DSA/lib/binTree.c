#include<stdlib.h>
#include<stdio.h>
typedef struct btNode {
  int val;
  struct btNode * left , *right; 
}btNode; 


btNode *  createBTNode(int val){
  btNode * root = (btNode*)malloc(sizeof(btNode));
  root->val = val;
  root->left = root->right = NULL;
  return root;
}


void inOdrTrav(btNode * root){
  if(root == NULL) return;
  inOdrTrav(root->left);
  printf("%d ,",root->val);
  inOdrTrav(root->right);
}
void preOdrTrav(btNode * root){
  if(root == NULL) return;
  printf("%d ,",root->val);
  preOdrTrav(root->left);
  preOdrTrav(root->right);
}
void postOdrTrav(btNode * root){
  if(root == NULL) return;
  postOdrTrav(root->left);
  postOdrTrav(root->right);
  printf("%d ,",root->val);
}

/*
 * testing
int main(){
  btNode * root = createBTNode(1);
  root->right = createBTNode(3);
  root->right->left = createBTNode(6);
  root->right->right = createBTNode(7);
  root->left = createBTNode(2);
  root->left->right = createBTNode(5);
  root->left->left = createBTNode(4);
  root->left->left->left = createBTNode(8);
  root->left->left->right = createBTNode(9);
  inOdrTrav(root);printf("\n");
  preOdrTrav(root);printf("\n");
  postOdrTrav(root);printf("\n");
}
*/
