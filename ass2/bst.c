#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>
#include"bst.h"

#include "unique_rng.c"

Node* addNode(Node *root, int value)
{
  Node *newNode = malloc(sizeof(Node));
  newNode->data = value;
  newNode->left = NULL;
  newNode->right = NULL;

  Node *temp;
  Node *prev = NULL;

  temp = root;
  while(temp) {
    prev = temp;
    if (temp->data > newNode->data)
      temp = temp->right;
    else if (temp->data < newNode->data)
      temp = temp->left;
    else {
      free(newNode);
      return NULL;
    }
  }
  if (prev==NULL)
    root = newNode;
  else {
    if (prev->data > newNode->data)
      prev->right = newNode;
    else
      prev->left = newNode;
  }

  return root;
}

Node* freeSubtree(Node *N) {
  if (N == NULL)
    return NULL;
  freeSubtree(N->left);
  freeSubtree(N->right);
  free(N);
}

void removeSubtreeWorker(Node *R, int value) {
  if (R == NULL)
    return;

  if (R->left && R->left->data == value) {
    freeSubtree(R->left);
    R->left = NULL;
    return;
  }

  if (R->right && R->right->data == value) {
    freeSubtree(R->right);
    R->right = NULL;
    return;
  }

  if (R->data < value)
    removeSubtreeWorker(R->left, value);
  else
    removeSubtreeWorker(R->right, value);
}

Node* removeSubtree(Node *R, int value) {
  if (R == NULL)
    return NULL;

  if (R->data == value) {
    freeSubtree(R);
    return NULL;
  }
  removeSubtreeWorker(R, value);
  return R;
}

void displaySubtree(Node *N)
{
  if (N==NULL)
    {
      return ;
    }
  displaySubtree(N->right);
  printf("%d\n", N->data);
  displaySubtree(N->left);
}

int countNodes(Node *N)
{
  int count=0;
  if(N==NULL)
    return 0;
  count = count + countNodes(N->right);
  count = count + countNodes(N->left);
  count = count + 1;
  return count;
}

// this is the most complicated task
Node* removeNode(Node* root, int value)
{
  // Ensure root isn't null.
  if (root == NULL) {
    return NULL;
  }
      
  if (value > root->data) {  // Value is in the left sub-tree.
    root->left = removeNode(root->left, value);
  } else if (value < root->data) { // Value is in the right sub-tree.
    root->right = removeNode(root->right, value);
  } else { // Found the correct node with value
    // Check the three cases - no child, 1 child, 2 child...
    // No Children
    if (root->left == NULL && root->right == NULL) {
      free(root);
      root = NULL;
    }
    // 1 child (on the right)
    else if (root->left == NULL) {
      Node *temp = root; // save current node
      root = root->right;
      free(temp);
    }
    // 1 child (on the left)
    else if (root->right == NULL) {
      Node *temp = root; // save current node
      root = root->left;
      free(temp);
    }
    // Two children
    else {
      // find minimal value of right sub tree
      Node *temp = root->left;
      while(temp->right != NULL) {
        temp = temp->right;
      }
      root->data = temp->data; // duplicate the node
      root->left = removeNode(root->left, root->data); // delete the duplicate node
    }
  }
  return root; // parent node can update reference
}

int numberLeaves(Node *N) {
  if (N == NULL)
    return 0;

  if (N->left == NULL && N->right == NULL)
    return 1;

  return numberLeaves(N->left) + numberLeaves(N->right);
}

int nodeDepth(Node *R, Node *N) {
  if (R == NULL || N == NULL)
    return -1;

  if (R == N)
    return 0;

  int subDepth = nodeDepth(R->data < N->data ? R->left : R->right, N);

  if (subDepth >= 0)
    return subDepth + 1;
  else
    return -1;
}



/*

Place for the BST functions from Exercise 1.

*/
static void traverse(Node* N, double* sum, int* num) {
    if(N == NULL) return ;
    *sum += N->data;
    *num += 1;
    traverse(N->left, sum, num);
    traverse(N->right, sum, num);
}

float avgSubtree(Node *N)
{
    double sum = 0;
    int num = 0;

    traverse(N, &sum, &num);

    if(num != 0) {
        return sum / num;
    } else {
        return -1;
    }
}
Node* createNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->left = node->right = NULL;
    node->data = data;
    return node;
}

Node* createBalanceTree(int* arr, int left, int right) {
    if(left > right) return NULL;
    if(left == right) return createNode(arr[left]);

    int mid = (left + right) / 2;
    Node* node = createNode(arr[mid]);
    node->left = createBalanceTree(arr, left, mid-1);
    node->right = createBalanceTree(arr, mid+1, right);

    return node;
}

void inOrder(Node* root, int* arr, int* index) {
    if(root == NULL) return ;

    inOrder(root->left, arr, index);
    arr[*index] = root->data;
    (*index)++;
    inOrder(root->right, arr, index);
}

// This functions converts an unbalanced BST to a balanced BST
Node* balanceTree(Node* root)
{
    int N = 0;
    double sum = 0;
    traverse(root, &sum, &N);
    int* arr = (int*)malloc(sizeof(int) * N);
    int index = 0;
    inOrder(root, arr, &index);

    Node* newRoot = createBalanceTree(arr, 0, N-1);
    free(arr);
    return newRoot;
}
Node *root=NULL;
int f_verbose = 0;
Node *root_balanced=NULL;

void clean(){
  /*****************************************************/
  /******   Free resources before program ends  ********/
  /*****************************************************/

  root=freeSubtree(root);
  root_balanced = freeSubtree(root_balanced);
  root= NULL;
  root_balanced = NULL;
  return;
}
int main(){
 unsigned int i,r;
  float avg, avg_balanced;
  const float epsilon = 0.001;
  float failed = 0;
  init_rand();
  // Create a random BST rooted at 'root'
  for(i=0; i<10000; i++){
    r = unique_random_number();     // This will give you the same set of random numbers every time
    root=addNode(root, r);
  }

  /*****************************************************/
  /******   Part 1 of Exercise 2 Starts here    ********/
  /*****************************************************/

  printf("/******** TEST OF PART 1 ********/\n\n");

  // Create a balanced BST from the unbalanced BST
  root_balanced = balanceTree(root);

  // Avg on unbalanced BST

  avg = avgSubtree(root);

  printf("Avg of unbalanced BST = %f\n", avg);

  // Sum on balanced BST
  avg_balanced = avgSubtree(root_balanced);

  printf("Avg of balanced BST = %f\n", avg_balanced);

  printf("Difference in avgs = %f\n", avg - avg_balanced);
  destroy_rand();

  failed = (avg - avg_balanced) + (avg - 28906.039062);
    printf("failed: %d ",failed);
  if(((failed > epsilon) || (failed < -epsilon)) && f_verbose)
    {
      printf("\n/******** START DEBUG MODE *********/\n");

      printf("\nUnbalanced tree:\n");
      printf("label1\n");
      displaySubtree(root);
      printf("label2\n");
      printf("\nBalanced tree:\n");
      printf("label3\n");
      displaySubtree(root_balanced);
      printf("label4\n");
      printf("\n/******** END DEBUG MODE ********/\n");
    }

  printf("\n /******** END OF PART 1 ********/\n\n");

  clean();
}