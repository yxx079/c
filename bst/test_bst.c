#include <stdio.h>
#include <assert.h>

#include "bst.h"

int main() {
//   Node *a, *b,*d;
//   a = addNode(NULL, 42);
//   b = removeNode(a, 42);
//   assert(b == NULL);

//   a = addNode(NULL, 1);
//   b = addNode(a, 2);

//   displaySubtree(a);
//   int c = numberLeaves(a);
//   assert(c == 1);

//   c = nodeDepth(a,b);
//   assert(c == 1);

//   a=removeNode(a, 1);
//  displaySubtree(a);
Node *a,*b;
a=addNode(NULL,6);
 addNode(a,7);
addNode(a,5);
addNode(a,8);
b=addNode(a,9);
addNode(a,3);
printf("%d",nodeDepth(a,b));
  
  return 0;
}