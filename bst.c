#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>
#include "bst.h"


/*

Place for the BST functions from Exercise 1.

*/

struct Node {
  int data;
  struct Node* left;
  struct Node* right;
};

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

  return newNode;
}
//how to use this funtionc ?????
Node* freeSubtree(Node *N) {
  if (N == NULL)
    return;
  freeSubtree(N->left);
  freeSubtree(N->right);
  free(N);
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


float avgSubtree(Node *N)

{

  int divNum=countNodes(N);
  return (float)sumNode(N) / (float) divNum;
}
int sumNode(Node*N){
  if(N==NULL) return 0;
  return (N->data)+sumNode (N->left)+sumNode(N->right);
}


// This functions converts an unbalanced BST to a balanced BST
Node* balanceTree(Node* root){
if(root ==NULL)
return NULL;

int array_size=countNodes(root);
int tree [array_size];
bstToSortedlist(root,tree,0);
sortedArrayToBST(tree,tree[0],tree[array_size]);



}


int 
bstToSortedlist(Node * root,int arr[] ,int countNum){
  if (root== NULL) 
      return countNum;
  if(root->left !=NULL)
      countNum = bstToSortedlist(root->left,arr,countNum);

  arr[countNum]=root->data;
  countNum++;
  if (root->right!=NULL)
     countNum  = bstToSortedlist( root->right,arr,countNum);
     return countNum;

 }
 Node* sortedArrayToBST(int arr [],int start,int end){


  int mid =(start+end)/2;
  Node * root;
  root->data = arr[mid];
  root->left =sortedArrayToBST (arr,start,mid-1);
  root->right =sortedArrayToBST(arr, mid+1,end);
  return root;
 }


 

