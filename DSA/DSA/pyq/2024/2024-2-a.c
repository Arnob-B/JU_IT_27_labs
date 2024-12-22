#include "./../../lib/arrayQueue.c"
#include <stdlib.h>
#include <stdio.h>
typedef struct myStack{
  arrQueue* q1;
  arrQueue* q2;
}myStack;


myStack * createStack(){
  myStack * newStack = (myStack*)malloc(sizeof(myStack));
  newStack->q1 = createArrQueue();
  newStack->q2 = createArrQueue();
  return newStack;
}
void myStackPush(myStack * stack,int val){
  arrQueue* target = empty(stack->q1) ? stack->q1 : stack->q2;
  arrQueue* source = target == stack->q2 ? stack->q1 : stack->q2;
  enqueue(target,val);
  int swap;
  while(dequeue(source,&swap)){
    enqueue(target,swap);
  }
}
int myStackPop(myStack * stack , int* val){
  if(empty(stack->q1) && empty(stack->q2)) return 0;
  else {
    arrQueue* source = !empty(stack->q1) ? stack->q1 : stack->q2;
    dequeue(source, val);
    return 1;
  }
}
int myStackSize(myStack * stack ){
  arrQueue* source = !empty(stack->q1) ? stack->q1 : stack->q2;
  return size(source);
}

int main(){
  myStack * ms = createStack();
  myStackPush(ms,1);
  myStackPush(ms,2);
  myStackPush(ms,3);
  myStackPush(ms,4);
  int val;
  while(myStackPop(ms, &val)){
    printf("%d , ",val);
  }

}
