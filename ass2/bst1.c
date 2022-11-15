#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>
#include "bst.h"


/*

Place for the BST functions from Exercise 1.

*/
Node *malloc_node(int value){
    Node * node = (Node *) malloc(sizeof(Node));
  node->data = value;
  node->left = node->right = NULL;
  return node;
}

Node* addNode(Node *root, int value)
{
  
    
 Node *current;
 Node **link;
 link=&root;
 while((current=*link)!=NULL ){
if(value>current->data){
link=&current->left;
}
else if(value<current->data){

  link =&current->right;
}
else{
return root;}
}
current = malloc_node(value);
*link=current;
return root;
}
//how to use this funtionc ?????
Node* freeSubtree(Node *N) {
  if (N == NULL)
    return NULL;
  freeSubtree(N->left);
  freeSubtree(N->right);
  free(N);
  return NULL;
  
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


 
 int sumNode(Node* N){
     if(N == NULL) return 0;
     return N->data+sumNode(N->right)+sumNode(N->left); 
 }


float avgSubtree(Node *N)

{
  if(N==NULL){
    return 0;
  }
  int divNum=countNodes(N);
  int sum =sumNode(N);
  return  (float)sum / (float) divNum;
}





void
bstToSortedlist(Node * root,int *arr ,int *countNum){
  if (root== NULL) 
      return ;

	bstToSortedlist(root->left, arr, countNum);
	arr[(*countNum)++] = root->data;
	bstToSortedlist(root->right, arr, countNum);

 }
 Node* sortedArrayToBST(int arr [],int start,int end){

     if (start > end)
      return NULL;
  int mid =(start+end)/2;
  Node *root=malloc_node(arr[mid]);
  root->left =sortedArrayToBST (arr,start,mid-1);
  root->right =sortedArrayToBST(arr, mid+1,end);
  return root;
 }
 

// This functions converts an unbalanced BST to a balanced BST
Node* balanceTree(Node* root){
	int *array = (int *)malloc(sizeof(int) * countNodes(root));
	int index = 0;
	bstToSortedlist(root, array, &index);
	// create a balanced BST from a sorted array.
	Node *root_balanced = sortedArrayToBST(array, 0, index - 1);
	free(array);
	return root_balanced;
}



