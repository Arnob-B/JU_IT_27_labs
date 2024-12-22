#include "./../../lib/ll.c"


llNode * reversal(llNode * root, int k){
  llNode * startP =  root;
  llNode * endP =  root;
  llNode * nextStartP =  root;
  llNode * prevNode;
  while(nextStartP!=NULL){
    prevNode = nextStartP;
    startP = nextStartP;

    endP = nextStartP;
    int win = k;
    while(win-- && endP->next!=NULL){ // setting up the endP
      endP= endP->next;
    }
    nextStartP = endP->next;

    while(endP!=startP){
      //reversing
      while(endP!=prevNode){
        startP = prevNode;
        while(startP->next !=endP){
          startP = startP->next;
        }
        endP->next = startP;
      }
    }
    startP->next = prevNode;
    prevNode = startP;
  }
}

int main(){
  llNode * root = createHeader(1);
  createList(root,2);
  createList(root,3);
  createList(root,4);
  createList(root,5);
  int k = 3;
}
