#include<stdlib.h>
#define maxSize 1000
typedef struct arrStack{
  int data[maxSize];
  int top;
}arrStack;

arrStack *createStack();
void push(arrStack *,int );
int pop(arrStack*,int *);
int empty(arrStack*);
int top(arrStack*);

//definations
arrStack* createStack(){
  arrStack* stack = (arrStack*)malloc(sizeof(arrStack));
  stack->top=-1;
  return stack;
}
void push(arrStack * stack,int val){
  if(stack->top < maxSize -1){
    stack->top++;
    stack->data[stack->top] = val;
  }
}
int top(arrStack* stack){
  if(stack->top !=-1) return stack->data[stack->top];
  else return -1;
}
int pop(arrStack * stack, int* x){
  if(stack->top ==-1)return 0;
  else{
    *x = stack->data[stack->top];
    stack->top = stack->top-1;
    return 1;
  }
}
int empty(arrStack *stack){
  return stack->top == -1 ? 1:0;
}
