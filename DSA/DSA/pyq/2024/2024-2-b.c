#include"./../../lib/arrStack.c"
#include<stdio.h>


arrStack* sort(arrStack* stack);
int main(){
  arrStack* stack = createStack();
  push(stack,10);
  push(stack,1);
  push(stack,3);
  push(stack,9);
  push(stack,7);
  stack = sort(stack);
  int val;
  while(pop(stack,&val)){
   printf("%d ",val);
  }
}

arrStack* sort(arrStack* stack){
  if(empty(stack)) return stack;
  int key ;
  pop(stack,&key);
  arrStack * s1 = createStack();
  arrStack * s2 = createStack();
  int val;
  while(pop(stack,&val)){
    if(val > key) // "<" will sort it ascending
      push(s2,val);
    else
      push(s1,val);
  }
  //sorting the two stacks;
  s1 = sort(s1);
  s2 = sort(s2);
  arrStack * s2new = createStack();
  while(pop(s2,&val)){
    push(s2new,val);
  }
  push(s1,key);
  while(pop(s2new,&val)){
    push(s1, val);
  }
  return s1;
}

