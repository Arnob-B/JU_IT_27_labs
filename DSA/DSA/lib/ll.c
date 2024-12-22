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

typedef struct llNode {
  int val;
  struct llNode *next;
}llNode;


llNode* createHeader( int val){
  llNode * temp = (llNode *)malloc(sizeof(llNode));
  temp->val = val;
  return temp;
}
void createList(llNode * root, int val){
    llNode *temp = root;
    while(temp->next!=NULL){
      temp = temp->next;
    }
    temp->next = (llNode * )malloc(sizeof(llNode));
    temp->next->val = val;
}

void makeCircular(llNode* root){
  llNode* temp =root;
  while(temp->next !=NULL){
    temp=temp->next;
  }
  temp->next=root;
}

void printNodeLL(llNode * root){
  llNode * temp  = root;
  while(temp!=NULL){
    printf("%d, ",temp->val);
    temp= temp->next;
    if(temp == root) return; // avoid circ
  }
}
llNode *  insertLL(llNode * root,int i,llNode * target){//create at ith index ,0 based
  if( i == 0){
    target->next = root;
    root = target;
  }
  else{
    llNode * temp = root;
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
llNode *  deleteLL(llNode * root,int i){ //delete ith index ,0 based
  if( i == 0){
    llNode *nextRoot=root->next;
    free(root);
    return nextRoot;
  }
  else{
    llNode * temp = root;
    int k;
    llNode * target = temp->next;
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
void printLLReverse(llNode *root){
  llNode * endP = root;
  while(endP->next != NULL)endP=endP->next; //setting up the ll
  printf("%d, ",endP->val);
  while(endP !=root){
    llNode *startP = root;
    while(startP->next!=endP)
      startP = startP->next;
    printf("%d, ",startP->val);
    endP = startP;
  }
}
llNode* reverseLL(llNode *root){
  llNode * endP = root;
  while(endP->next != NULL)endP=endP->next; //setting up the ll
  llNode* newRoot = endP;
  while(endP !=root){
    llNode *startP = root;
    while(startP->next!=endP)
      startP = startP->next;
    endP->next = startP;
    endP = startP;
  }
  endP->next = NULL;
  return newRoot;
}
/*
int main(){
  llNode * root = createHeader(1);
  createList(root,2);
  createList(root,3);
  createList(root,4);
  createList(root,5);
  printNodeLL(root);
  printf("\n");
  printLLReverse(root);
  printf("\n");
  printNodeLL(root);
  printf("\n");
  root = reverseLL(root);
  printNodeLL(root);
}
*/
