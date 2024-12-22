#include<stdlib.h>
typedef struct bstNode {
  int val;
  struct bstNode * left , *right; 
}bstNode; 

bstNode *  createBSTNode(int val){
  bstNode * root = (bstNode*)malloc(sizeof(bstNode));
  root->val = val;
  root->left = root->right = NULL;
  return root;
}

bstNode* searching(bstNode * root,int key){
  bstNode * temp = root;
  while(temp!=NULL){
    if(key < temp->val){
      temp=temp->left;
    }
    else if(key > temp->val){
      temp=temp->right;
    }
    else break;
  }
  return temp;
}

void insert(bstNode * root , bstNode * target){
  if(target->val > root->val){
    if(root->right == NULL) {
      root->right =target;
      return;
    }
    insert(root->right,target);
  }
  else
  {
    if(root->left == NULL) {
      root->left =target;
      return;
    }
    insert(root->left,target);
  }
}


bstNode * successor(bstNode * root){ // no greater than the root able to take it's position
  bstNode * iosucressor;
  if(root -> right == NULL){
    return NULL; 
  }
  iosucressor = root->right;
  while(iosucressor->left!=NULL)iosucressor=iosucressor->left; //greatest number on the right
  return iosucressor;
}

bstNode * predecessor(bstNode * root){ // no smaller than the root able to take it's position
  bstNode * iopredecessor;
  if(root -> left == NULL){
    return NULL;
  }
  iopredecessor = root->left;
  while(iopredecessor->right!=NULL)iopredecessor=iopredecessor->right; //greatest number on the right
  return iopredecessor;
}


bstNode *delete(bstNode * root, bstNode * target , bstNode * parent){
  bstNode *iosucressor;
  if(target->right == NULL){
    // no right subtree
    if(parent->left == target) parent->left = target->left;
    else parent->right = target->right;
    return root;
  }
  bstNode * prev = target;
  iosucressor = prev->right;
  while(iosucressor->left!=NULL){
    prev = iosucressor;
    iosucressor = iosucressor->left;
  }
  prev->left = NULL;
  iosucressor ->right = target ->right;
  iosucressor->left = target->left;

  if(target == root) return iosucressor;
//setting up the parents
  if(parent->left == target) parent->left = iosucressor;
  else parent->right = iosucressor;
  return root;
}





