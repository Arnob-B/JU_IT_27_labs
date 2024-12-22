#include"./../../lib/ll.c"

llNode* rotateClock(llNode* root){
   llNode* temp = root;
   while(temp->next !=root)temp=temp->next;
   return temp;
}

int main(){
  llNode* root = createHeader(1);
  createList(root,2);
  createList(root,3);
  createList(root,4);
  createList(root,5);
  createList(root,6);
  makeCircular(root);
  printNodeLL(root);printf("\n");
  root = rotateClock(root);
  printNodeLL(root);
}
