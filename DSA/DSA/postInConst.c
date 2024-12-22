#include "./lib/binTree.c"
/*
typedef struct btNode {
  int val;
  struct btNode * left , *right;
}btNode;
*/

btNode *buildTree(int *lrR, int l1, int r1, int *lRr, int l2, int r2) {
  if (l1 > r1)
    return NULL;
  if (l2 > r2)
    return NULL;

  // searching the headValue
  int headValue = lrR[r1];
  int ind = 0;
  int temp = r1;
  while (temp >= l1) {
    int searchTerm = lrR[temp];
    int flag = 0;
    for (int i = r2; i >= l2; i--) {
      if (lRr[i] == searchTerm) {
        headValue = searchTerm;
        ind = i;
        flag = 1;
        // printf("serach term %d ind ->%d\n", headValue,ind);
        break;
      }
    }
    if (flag)
      break;
    temp--;
  }

  btNode *root = createBTNode(headValue);
  // printf("left %d %d\n",l2, ind-1);
  root->left = buildTree(lrR, l1, r1, lRr, l2, ind - 1);
  // printf("right %d %d\n",ind+1, r2);
  root->right = buildTree(lrR, l1, r1, lRr, ind + 1, r2);
  return root;
}
int main() {
  int size = 10;
  int lrR[10] = {9, 1, 2, 12, 7, 5, 3, 11, 4, 8};
  int lRr[10] = {9, 5, 1, 7, 2, 12, 8, 4, 3, 11};
  btNode *root = buildTree(lrR, 0, size - 1, lRr, 0, size - 1);
  postOdrTrav(root);
  printf("\n");
  inOdrTrav(root);
  printf("\n");
  preOdrTrav(root);
  printf("\n");
}
