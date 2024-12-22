#include"./../../lib/ll.c"

llNode * findJoin(llNode * l1,llNode * l2){
  llNode * endP = l1;
  while(endP->next!=NULL) endP = endP->next;
  while(endP != l1 || endP!=l2){
    llNode *startP1 = l1;
    llNode *startP2 = l2;
    if(l1 == endP || l2 == endP) break; // if it attaches to the front
    while(startP1->next!=endP){
      startP1 =startP1->next;
    }
    while(startP2->next!=endP){
      startP2 =startP2->next;
    }
    if(startP1 != startP2 )break;
    endP = startP1;
  }
  return endP;
}

int main(){
  llNode * r1 = createHeader(1);
  createList(r1,2);
  createList(r1,3);
  llNode * r2 = createHeader(10);
  createList(r2,11);
  createList(r2,12);
  createList(r2,13);
  createList(r2,14);
  r1->next->next = r2;
  printf("%d ",findJoin(r1,r2)->val);
}
