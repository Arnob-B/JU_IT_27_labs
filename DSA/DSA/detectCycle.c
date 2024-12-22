#include"./lib/ll.c"


int rain(){
  llNode * root = createHeader(1);
  createList(root,2);
  createList(root,3);
  createList(root,4);
  createList(root,5);
  createList(root,6);
  createList(root,7);
  //creating the loop from 7 to 3
  llNode * temp = root;
  while(temp->next!=NULL){
    temp = temp->next;
  }
  temp->next = root->next->next;

  //detection algo
  llNode *f = root , *s = root;
  int flag = 1;
  while(f!= s){
    if(f->next == NULL || f->next->next == NULL|| s->next == NULL) {flag = 0;break;}
    f = f->next->next;
    s = s->next;
  }
  if(flag ) printf("there is a loop");
}
