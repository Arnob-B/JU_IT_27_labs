#include<stdlib.h>
#include"./ll.c"
typedef struct llStack{
  llNode * top;
}llStack;

llStack *createStack();
void push(llStack *,int );
int pop(llStack*,int *);
int empty(llStack*);
int top(llStack*);

//definations
llStack* createStack(){
  llStack* stack = (llStack*)malloc(sizeof(llStack));
  stack->top = NULL;
  return stack;
}
void push(llStack * stack,int val){
  llNode* node = (llNode*)malloc(sizeof(llNode));
  node->next = NULL;
  node->val = val;
  if(stack->top!=NULL) node->next = stack->top;
  stack->top = node;
}
int top(llStack* stack){
  if(stack->top != NULL) return stack->top->val;
  else return -1;
}
int pop(llStack * stack, int* x){
  if(stack->top ==NULL)return 0;
  else{
    *x = stack->top->val;
    llNode *todel  = stack->top;
    stack->top = stack->top->next;
    todel->next = NULL;free(todel);
    return 1;
  }
}
int empty(llStack*stack) {return stack->top==NULL;}
