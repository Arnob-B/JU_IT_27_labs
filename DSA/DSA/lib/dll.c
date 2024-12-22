#include<stdlib.h>
#include<stdio.h>
/*
 * linked list 
 * 1. create header
 * 2. create list
 * 3. create new node(header + list)
 * 4. print content of list
 * 5. inserting a node after target (using index)
 * 6. delete a node (using signature)
 * 7. reverse a list
 * */

typedef struct dllNode {

  int val;
  struct dllNode *next;
  struct dllNode *prev;
}dllNode;


dllNode* createHeader( int val){
  dllNode * temp = (dllNode *)malloc(sizeof(dllNode));
  temp->val = val;
  temp->next = NULL;
  temp->prev = NULL;
  return temp;
}
void createList(dllNode * root, int val){
    dllNode *temp = root;
    while(temp->next!=NULL){
      temp = temp->next;
    }
    temp->next = (dllNode * )malloc(sizeof(dllNode));
    temp->next->prev = temp;
    temp->next->next = NULL;
    temp->next->val = val;
}

void printNodeLL(dllNode * root){
  dllNode * temp  = root;
  while(temp!=NULL){
    printf("%d, ",temp->val);
    temp= temp->next;
    if(temp == root) return; // avoid circ
  }
}
dllNode *  insertLL(dllNode * root,int i,dllNode * target){//create at ith index ,0 based
  if( i == 0){
    target->next = root;
    root = target;
  }
  else{
    dllNode * temp = root;
    int k;
    for( k=1;k<i&&(temp!=NULL);k++){ //addition in the end
      temp = temp->next;
    }
    if(temp == NULL && i>0) return root;
    target->next = temp->next;
    temp->next = target;
  }
  return root;
}
dllNode *  deleteLL(dllNode * root,int i){ //delete ith index ,0 based
  if( i == 0){
    dllNode *nextRoot=root->next;
    free(root);
    return nextRoot;
  }
  else{
    dllNode * temp = root;
    int k;
    dllNode * target = temp->next;
    for( k=1;k<i&&(target!=NULL);k++){ //addition in the end
      temp = target;target = target->next;
    }
    //printf("%d",k);
    if(target == NULL && i>0) return root;
    temp->next = target->next;
    target->next = NULL;
    free(target);
  }
  return root;
}
void printLLReverse(dllNode *root){
  dllNode * endP = root;
  while(endP->next != NULL)endP=endP->next; //setting up the ll
  printf("%d, ",endP->val);
  while(endP !=root){
    dllNode *startP = root;
    while(startP->next!=endP)
      startP = startP->next;
    printf("%d, ",startP->val);
    endP = startP;
  }
}
dllNode* reverseLL(dllNode *root){
  dllNode * endP = root;
  while(endP->next != NULL)endP=endP->next; //setting up the ll
  dllNode* newRoot = endP;
  while(endP !=root){
    dllNode *startP = root;
    while(startP->next!=endP)
      startP = startP->next;
    endP->next = startP;
    endP = startP;
  }
  endP->next = NULL;
  return newRoot;
}
void makeCircular(dllNode* root){
  dllNode* temp =root;
  while(temp->next !=NULL){
    temp=temp->next;
  }
  temp->next=root;
}

