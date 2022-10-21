#include <stdio.h>
#include <assert.h>

#include "bst.c"
#include "bst.h"

#include <stdio.h>
#include <assert.h>

#include "bst.h"

int main() {
  Node *a, *b;
  a = addNode(NULL, 42);
  b = removeNode(a, 42);
  assert(b == NULL);

  a = addNode(NULL, 1);
  b = addNode(a, 2);

  displaySubtree(a);
  int c = numberLeaves(a);
  assert(c == 1);

  c = nodeDepth(a,b);
  printf("%d\n",c);
  assert(c == 1);

  a = removeSubtree(a, 2);
  printf("%d",a->value);
  
  return 0;
}