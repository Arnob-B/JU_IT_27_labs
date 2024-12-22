#include"./../../lib/dll.c"

void joinCircLL(dllNode *l1 , dllNode * l2){
  dllNode * t1 = l1->prev;
  dllNode * t2 = l2->prev;
  t1->next = l2;
  l2->prev = t1;
  l1->prev = t2;
  t2->next = l1;
}

int main(){
  dllNode * root = createHeader(1);
  createList(root,2);
  createList(root,3);
  createList(root,4);
  createList(root,5);
  dllNode * root2 = createHeader(1);
  createList(root2,2);
  createList(root2,3);
  createList(root2,4);
  createList(root2,5);
  makeCircular(root2);
  joinCircLL(root,root2);
  printNodeLL(root);


}
