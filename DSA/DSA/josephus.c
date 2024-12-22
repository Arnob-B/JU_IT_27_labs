#include"./ll.c"


int josephus(llNode * root, int key){
  llNode * temp = root;
  while(temp->next !=temp){
    int k = key;
    while(--k){
      temp=temp->next;
    }
    llNode * todel = temp->next;
    printf("deleted %d\n",todel->val);
    temp->next = temp->next->next;
    temp = todel->next;
    todel->next= NULL;
  }
  return temp->val;
}
int main(){
  llNode * root = createHeader(1);
  createList(root,2);
  createList(root,3);
  createList(root,4);
  createList(root,5);
  llNode * temp = root;
  makeCircular(root);
  printf("%d ",josephus(root,2));
}
