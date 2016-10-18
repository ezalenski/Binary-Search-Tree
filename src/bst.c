#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

struct bst_node {
  int val;
  int nSize;
  struct bst_node *left;
  struct bst_node *right;
};
typedef struct bst_node NODE;


struct bst {
    NODE *root;
};

static void set_size(NODE *r);
static NODE * rebalance(NODE *r);
static int size(NODE*r);

BST_PTR bst_create(){
  BST_PTR t = malloc(sizeof(struct bst));
  t->root = NULL;
  return t;
}


static void free_r(NODE *r){
    if(r==NULL) return;
    free_r(r->left);
    free_r(r->right);
    free(r);
}
void bst_free(BST_PTR t){
    free_r(t->root);
    free(t);
}

static NODE * insert(NODE *r, int x, int *success){
    NODE *leaf;
    if(r == NULL){
      leaf = malloc(sizeof(NODE));
      leaf->left = NULL;
      leaf->right = NULL;
      leaf->val = x;
      leaf->nSize = 1;
      *success = 1;
      return leaf;
    }

    if(r->val == x) {
      *success = 0;
      return r;
    }
    
    if(((size(r->left) + 1)/3 > size(r->right)/2) || ((size(r->right) + 1)/3 > size(r->left)/2)) {
      r = rebalance(r);
    }

    if(x < r->val){
      r->left = insert(r->left, x, success);
    } else {
      r->right = insert(r->right, x, success);
    }
    if(*success) {
      r->nSize += 1;
    }
    return r;
}

// how about an iterative version?
static NODE *insert_i(NODE *r, int x){
  NODE *parent;
  NODE *curr;
  curr = parent = r;
  if(r == NULL) {
    r = malloc(sizeof(NODE));
    r->left = NULL;
    r->right = NULL;
    r->nSize = 1;
    r->val = x;
    return r;
  }
  while(curr != NULL) {
    //parent = curr;
    if(curr->val == x)
      break;
    if(x < curr->val)
      curr = curr->left;
    else
      curr = curr->right;
  }
  if(curr == NULL) {
    while(parent != NULL) {
      parent->nSize += 1;
      if(x < parent->val) {
	if(parent->left == NULL)
	  break;
	parent = parent->left;
      }
      else {
	if(parent->right == NULL)
	  break;
	parent = parent->right;
      }
    }
    curr = malloc(sizeof(NODE));
    curr->left = NULL;
    curr->right = NULL;
    curr->nSize = 1;
    curr->val = x;
    if(parent->val > x)
      parent->left = curr;
    else
      parent->right = curr;
  }
  return r;
}


void bst_insert(BST_PTR t, int x){
  int success;
  t->root = insert(t->root, x, &success);
  //  t->root = insert_i(t->root, x);
  //set_size(t->root);
}

int bst_contains(BST_PTR t, int x){
    NODE *p = t->root;

    while(p != NULL){

        if(p->val == x)
            return 1;
        if(x < p->val){
            p = p->left;
        }
        else
            p = p->right;
    }
    return 0;  
}

static int min_h(NODE *r){
  if(r==NULL)
    return -1; // should never happen!
  while(r->left != NULL)
      r = r->left;
  return r->val;
}

static int max_h(NODE *r){
  if(r==NULL)
    return -1; // should never happen!
  while(r->right != NULL)
      r = r->right;
  return r->val;
}

static NODE *remove_r(NODE *r, int x, int *success){
NODE   *tmp;
int sanity;

  if(r==NULL){
    *success = 0;
    return NULL;
  }
  if(r->val == x){
    *success = 1;
    if(r->left == NULL){
        tmp = r->right;
        free(r);
        return tmp;
    }
    if(r->right == NULL){
        tmp = r->left;
        free(r);
        return tmp;
    }
    // if we get here, r has two children
    r->val = min_h(r->right);
    r->right = remove_r(r->right, r->val, &sanity);
    if(!sanity)
        printf("ERROR:  remove() failed to delete promoted value?\n");
    r->nSize -= 1;
    return r;
  }

  if(((size(r->left) - 1)/2 < size(r->right)/3) || ((size(r->right) - 1)/2 < size(r->left)/3)) {
      r = rebalance(r);
  }
  
  if(x < r->val){  
    r->left = remove_r(r->left, x, success);
  } else {  
    r->right = remove_r(r->right, x, success);
  }

  if(*success)
    r->nSize -= 1;
  return r;

}

int bst_remove(BST_PTR t, int x){
    int success;
    t->root = remove_r(t->root, x, &success);
    return success;
}

static void set_size(NODE *r) {
  if (r==NULL)
    return;
  set_size(r->left);
  set_size(r->right);
  if(r->left == NULL && r->right == NULL)
    r->nSize = 1;
  else if(r->left == NULL)
    r->nSize = r->right->nSize + 1;
  else if(r->right == NULL)
    r->nSize = r->left->nSize + 1;
  else
    r->nSize = r->left->nSize + r->right->nSize + 1;
}

static int size(NODE *r){
    if(r==NULL) return 0;
    return r->nSize;
}
int bst_size(BST_PTR t){

    return size(t->root);
}

static int height(NODE *r){
    int l_h, r_h;

    if(r==NULL) return -1;
    l_h = height(r->left);
    r_h = height(r->right);
    return 1 + (l_h > r_h ? l_h : r_h);

}
int bst_height(BST_PTR t){
    return height(t->root);

}

int bst_min(BST_PTR t){
    return min_h(t->root);
}

int bst_max(BST_PTR t){
    return max_h(t->root);
}

static void indent(int m){
    int i;
    for(i=0; i<m; i++)
        printf("-");
}

static void inorder(NODE *r){
  if(r==NULL) return;
  inorder(r->left);
  printf("[%d]\n", r->val);
  inorder(r->right);

}
void bst_inorder(BST_PTR t){

  printf("========BEGIN INORDER============\n");
  inorder(t->root);
  printf("=========END INORDER============\n");

}

static void preorder(NODE *r, int margin){
  if(r==NULL) {
    indent(margin);
    printf("NULL \n");
  } else {
    indent(margin);
    printf("%d\n", r->val);
    preorder(r->left, margin+3);
    preorder(r->right, margin+3);
  }
}

void bst_preorder(BST_PTR t){

  printf("========BEGIN PREORDER============\n");
  preorder(t->root, 0);
  printf("=========END PREORDER============\n");

}

/* 
 * Not a graded exercise, but good practice!
 *
 * Complete the (recursive) helper function for the post-order traversal.
 * Remember: the indentation needs to be proportional to the height of the node!
 */
static void postorder(NODE *r, int margin){
  if(r==NULL) {
    indent(margin);
    printf("NULL \n");
  } else {
    postorder(r->left, margin+3);
    postorder(r->right, margin+3);   
    indent(margin);
    printf("%d\n", r->val);
  }
}

// indentation is proportional to depth of node being printed
//   depth is #hops from root.
void bst_postorder(BST_PTR t){

  printf("========BEGIN POSTORDER============\n");
  postorder(t->root, 0);
  printf("=========END POSTORDER============\n");

}

/* 
 * Recursive helper function from_arr, used by
 * bst_from_sorted_arr(...). The function must return a sub-tree that is
 * perfectly balanced, given a sorted array of elements a.
 */
static NODE * from_arr(int *a, int n){
int m;
NODE *root;

    if(n <= 0) return NULL;
    m = n/2;
    root = malloc(sizeof(NODE));
    root->val = a[m];
    root->left = from_arr(a, m);
    root->right = from_arr(&(a[m+1]), n-(m+1));
    return root;

}

BST_PTR bst_from_sorted_arr(int *a, int n){

  BST_PTR t = bst_create();

  t->root = from_arr(a, n);
  set_size(t->root);
  return t;
}


/******    TODO      *********/
static void to_arr(NODE *r, int *a) {
  int m;
  
  if(r == NULL)
    return;
  to_arr(r->left, a);
  m = (size(r->left));
  a[m] = r->val;
  to_arr(r->right, &(a[m+1]));
}

int * bst_to_array(BST_PTR t) {
  int n = bst_size(t);
  int *ret = malloc(sizeof(int) * n);
  to_arr(t->root, ret);
  return ret;
}

static int get_ith(NODE *r, int k) {
  if(k < 1 || r == NULL || k > size(r)) {
    fprintf(stderr, "ERROR: bst_get_ith(): invalid arguments\n");
    return 0;
  }
  int n = size(r);
  if(n == 1 || k == (size(r->left) + 1))
    return r->val;
  if(k <= size(r->left))
    return get_ith(r->left, k);
  else
    return get_ith(r->right, k-(size(r->left)+1));
}

int bst_get_ith(BST_PTR t, int i) {
  return get_ith(t->root, i);
}

static int get_nearest(NODE *r, int x) {
  int small, big; /* smallest and biggest number closest to x */
  if(r == NULL)
    return -1;
  if(r->val == x || (r->val > x && r->left == NULL) || (r->val < x && r->right == NULL))
    return r->val;
  if(r->val > x) {
    small = get_nearest(r->left, x);
    if(small >= 0 && ((x - small) < (r->val - x)))
      return small;
    else
      return r->val;
  }
  else {
    big = get_nearest(r->right, x);
    if(big >= 0 && ((big - x) < (x - r->val)))
      return big;
    else
      return r->val;
  }
}

int bst_get_nearest(BST_PTR t, int x) {
  
  return get_nearest(t->root, x);

}

static int num_geq(NODE *r, int x) { 
  if(r == NULL)
    return 0;
  if(r->val == x)
    return size(r->right) + 1;
  if(r->val > x)
    return num_geq(r->left, x) + size(r->right) + 1;
  return num_geq(r->right, x);
  
}

int bst_num_geq(BST_PTR t, int x) {
  return num_geq(t->root,x);
}

static int num_leq(NODE *r, int x) {
  if(r == NULL)
    return 0;
  if(r->val == x)
    return size(r->left) + 1;
  if(r->val < x)
    return num_leq(r->right, x) + size(r->left) + 1;
  return num_leq(r->left, x);
}

int bst_num_leq(BST_PTR t, int x) {
  return num_leq(t->root,x);
}

static NODE * rebalance(NODE *r) {
  int i;
  int n = size(r);
  int *a = malloc(sizeof(int)*n);
  to_arr(r,a);
  
  /* printf("REBALANCE ARR: ["); */
  /* for(i = 0; i < n; i++) */
  /*   printf(" %i ", a[i]); */
  /* printf("]\n"); */
  
  free_r(r);

  NODE *ret = from_arr(a, n);
  free(a);
  set_size(ret); 
  
  /* inorder(ret); */
  
  return ret;
}
