#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bst.h"

void print_arr(int *a, int n) {
  int i;
  printf(" [");
  for(i = 0; i < n; i++)
    printf(" %i ", a[i]);
  printf("]\n");
}

void swap(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

void permute_tests(int *array, int *testnum, int i,int length) { 
  if (length == i){
    printf("\n\nTEST E%i: bst_to_array of size %i\nThe input order was: ", *testnum, length);
    print_arr(array, length);
    printf("Expected output:\n");
    int c;
    printf(" [");
    for(c = 0; c < length; c++)
      printf(" %i ", c);
    printf("]\n");
    printf("Program's output:\n");
    BST_PTR t = bst_create();
    for(c = 0; c < length; c++) {
      bst_insert(t, array[c]);
    }
    int *arr = bst_to_array(t);
    print_arr(arr, length);
    assert(bst_size(t) == length);
    bst_free(t);
    free(arr);
    (*testnum)++;
    return;
  }
  int j = i;
  for (j = i; j < length; j++) { 
    swap(&(array[i]),&(array[j]));
    permute_tests(array, testnum, i+1,length);
    swap(&(array[i]),&(array[j]));
  }
  return;
}

void testE() {
  printf("Test E:\n\n");
  printf("TEST E1: bst_to_array of size 0\nExpected output: []\n");
  printf("Program's output: ");
  BST_PTR t = bst_create();
  int *arr = bst_to_array(t);
  print_arr(arr, bst_size(t));
  bst_free(t);
  free(arr);
  
  printf("\n\nTEST E2: bst_to_array of size 1\nExpected output: [ 1 ]\n");
  printf("Program's output:");
  t = bst_create();
  bst_insert(t, 1);
  arr = bst_to_array(t);
  print_arr(arr, bst_size(t));
  bst_free(t);
  free(arr);
  
  int inputlength = 4;
  arr = malloc(sizeof(int)*inputlength);
  int i;
  for(i = 0; i < inputlength; i++)
    arr[i] = i;
  int testnum = 3;
  permute_tests(arr, &testnum, 0, inputlength);
  free(arr);
}

void testF() {
  printf("\n\nTest F:");
  int i;
  int testarr[] = { 2,3,5,7,11,13,17,19,23,29,31,37,41,43,47 };
  BST_PTR t = bst_from_sorted_arr(testarr, 15);

  printf("\n\nTEST F1: bst_get_ith for 0-th smallest element\nExpected output: ERROR MESSAGE\n");
  printf("Program's output: ");
  printf("%i\n", bst_get_ith(t, i));

  for(i = 1; i < 16; i++) {
    printf("\n\nTEST F%i: bst_get_ith for %i-th smallest element\nExpected output: %i\n", i+1, i, testarr[i-1]);
    printf("Program's output: ");
    printf("%i\n", bst_get_ith(t, i));
  }

  printf("\n\nTEST F%i: bst_get_ith for %i-th smallest element\nExpected output: ERROR MESSAGE\n", i, i);
  printf("Program's output: ");
  printf("%i\n", bst_get_ith(t, i));  
  
  bst_free(t);
}

int nearesttothird(int a, int b, int c) { 
  if(abs(c-a) == abs(c-b)) {
    printf("%i OR ", b);
  }
  if(abs(c-a) <= abs(c-b))
    return a;
  else
    return b;
}

void testG() {
  int i;
  printf("\n\nTest G:");
  int testarr[] = { 2,3,5,7,11,13,17,19,23,29,31,37,41,43,47 };
  BST_PTR t = bst_from_sorted_arr(testarr, 15);

  printf("\n\nTEST G1: bst_get_nearest(t, 0)\n Expected output: 2\n");
  printf("Program's output: ");
  printf("%i\n", bst_get_nearest(t, 0));

  for(i = 1; i < 15; i++) {
    int testnum = (testarr[i-1]+testarr[i])/2;
    printf("\n\nTEST G%i: bst_get_nearest(t, %i)\nExpected output: ", i+1, testnum);
    printf("%i\n", nearesttothird(testarr[i-1], testarr[i], testnum));
    printf("Program's output: ");
    printf("%i\n", bst_get_nearest(t, testnum));
  }

  printf("\n\nTEST G%i: bst_get_nearest(t, 50)\nExpected output: 47\n", i+1);
  printf("Program's output: ");
  printf("%i\n", bst_get_nearest(t, 50));  
  
  bst_free(t);
  
}

int main(){
    int i;

    /* PART 1 */
    BST_PTR t = bst_create();

    printf("Test A:\n\n");
    printf("TEST A1: bst_insert(t, 5)\nExpected output:\n========BEGIN INORDER============\n[5]\n==========END INORDER===========\n");
    bst_insert(t, 5);
    printf("Program's output:\n");
    bst_inorder(t);


    printf("\n\nTEST A2: bst_insert(t, 3)\nExpected output:\n========BEGIN INORDER============\n[3]\n[5]\n==========END INORDER===========\n");
    bst_insert(t, 3);
    printf("Program's output:\n");
    bst_inorder(t);
    
    printf("\n\nTEST A3: bst_insert(t, 4)\nExpected output:\n========BEGIN INORDER============\n[3]\n[4]\n[5]\n==========END INORDER===========\n");
    bst_insert(t, 4);
    printf("Program's output:\n");
    bst_inorder(t);

    printf("\n\nTEST A4: bst_insert(t, 7)\nExpected output:\n========BEGIN INORDER============\n[3]\n[4]\n[5]\n[7]\n==========END INORDER===========\n");
    bst_insert(t, 7);
    printf("Program's output:\n");
    bst_inorder(t);

    printf("\n\nTEST A5: bst_insert(t, 6)\nExpected output:\n========BEGIN INORDER============\n[3]\n[4]\n[5]\n[6]\n[7]\n==========END INORDER===========\n");
    bst_insert(t, 6);
    printf("Program's output:\n");
    bst_inorder(t);

    printf("\n\nTEST A6: bst_insert(t, 8)\nExpected output:\n========BEGIN INORDER============\n[3]\n[4]\n[5]\n[6]\n[7]\n[8]\n==========END INORDER===========\n");
    bst_insert(t, 8);
    printf("Program's output:\n");
    bst_inorder(t);
    
    printf("\n\nTEST A7: bst_insert(t, 2)\nExpected output:\n========BEGIN INORDER============\n[2]\n[3]\n[4]\n[5]\n[6]\n[7]\n[8]\n==========END INORDER===========\n");
    bst_insert(t, 2);
    printf("Program's output:\n");
    bst_inorder(t);

    printf("\n\nTEST A8: bst_insert(t, 1)\nExpected output:\n========BEGIN INORDER============\n[1]\n[2]\n[3]\n[4]\n[5]\n[6]\n[7]\n[8]\n==========END INORDER===========\n");
    bst_insert(t, 1);
    printf("Program's output:\n");
    bst_inorder(t);

    printf("\n\nTEST A9: bst_insert(t, 9)\nExpected output:\n========BEGIN INORDER============\n[1]\n[2]\n[3]\n[4]\n[5]\n[6]\n[7]\n[8]\n[9]\n==========END INORDER===========\n");
    bst_insert(t, 9);
    printf("Program's output:\n");
    bst_inorder(t);

    assert(bst_size(t) == 9);

    printf("\nTest B:\n\n");

    printf("TEST B1: bst_contains(t, 5)\nExpected output: 1\n");
    printf("Program's output: %i\n", bst_contains(t, 5));

    printf("\n\nTEST B2: bst_contains(t, 1)\nExpected output: 1\n");
    printf("Program's output: %i\n", bst_contains(t, 1));

    printf("\n\nTEST B3: bst_contains(t, 2)\nExpected output: 1\n");
    printf("Program's output: %i\n", bst_contains(t, 2));

    printf("\n\nTEST B4: bst_contains(t, 8)\nExpected output: 1\n");
    printf("Program's output: %i\n", bst_contains(t, 8));

    printf("\n\nTEST B5: bst_contains(t, 9)\nExpected output: 1\n");
    printf("Program's output: %i\n", bst_contains(t, 9));

    printf("\n\nTEST B6: bst_contains(t, 0)\nExpected output: 0\n");
    printf("Program's output: %i\n", bst_contains(t, 0));

    printf("\n\nTEST B7: bst_contains(t, 10)\nExpected output: 0\n");
    printf("Program's output: %i\n", bst_contains(t, 10));    

    printf("\nTest C:\n\n");

    printf("TEST C1: bst_remove(t, 1)\nExpected output:\n========BEGIN INORDER============\n[2]\n[3]\n[4]\n[5]\n[6]\n[7]\n[8]\n[9]\n==========END INORDER===========\n");
    bst_remove(t, 1);
    printf("Program's output:\n");
    bst_inorder(t);


    printf("\n\nTEST C2: bst_remove(t, 5)\nExpected output:\n========BEGIN INORDER============\n[2]\n[3]\n[4]\n[6]\n[7]\n[8]\n[9]\n==========END INORDER===========\n");
    bst_remove(t, 5);
    printf("Program's output:\n");
    bst_inorder(t);
    
    printf("\n\nTEST C3: bst_remove(t, 3)\nExpected output:\n========BEGIN INORDER============\n[2]\n[4]\n[6]\n[7]\n[8]\n[9]\n==========END INORDER===========\n");
    bst_remove(t, 3);
    printf("Program's output:\n");
    bst_inorder(t);

    printf("\n\nTEST C4: bst_remove(t, 8)\nExpected output:\n========BEGIN INORDER============\n[2]\n[4]\n[6]\n[7]\n[9]\n==========END INORDER===========\n");
    bst_remove(t, 8);
    printf("Program's output:\n");
    bst_inorder(t);

    assert(bst_size(t) == 5);
   
    bst_free(t);

    printf("\nTest D:\n\n");
    
    int arr0[] = {};
    printf("TEST D1: bst_from_sorted_arr of size 0\nExpected output:\n========BEGIN INORDER============\n==========END INORDER===========\n");
    t = bst_from_sorted_arr(arr0, 0);
    printf("Program's output:\n");
    bst_inorder(t);
    assert(bst_size(t) == 0);
    bst_free(t);
    
    int arr1[] = { 1 };
    printf("\n\nTEST D2: bst_from_sorted_arr of size 1\nExpected output:\n========BEGIN INORDER============\n[1]\n==========END INORDER===========\n");
    t = bst_from_sorted_arr(arr1, 1);
    printf("Program's output:\n");
    bst_inorder(t);
    assert(bst_size(t) == 1);
    bst_free(t);
    
    int arr2[] = { 1, 3, 5, 7, 9, 11, 13 };
    printf("\n\nTEST D3: bst_from_sorted_arr of odd size\nExpected output:\n========BEGIN INORDER============\n[1]\n[3]\n[5]\n[7]\n[9]\n[11]\n[13]\n==========END INORDER===========\n");
    t = bst_from_sorted_arr(arr2, 7);
    printf("Program's output:\n");
    bst_inorder(t);
    assert(bst_size(t) == 7);
    bst_free(t);
    
    int arr3[] = { 0, 2, 4, 6, 8, 10, 12, 14 };
    printf("\n\nTEST D4: bst_from_sorted_arr of odd size\nExpected output:\n========BEGIN INORDER============\n[0]\n[2]\n[4]\n[6]\n[8]\n[10]\n[12]\n[14]\n==========END INORDER===========\n");
    t = bst_from_sorted_arr(arr3, 8);
    printf("Program's output:\n");
    bst_inorder(t);
    assert(bst_size(t) == 8);
    bst_free(t);

    testE();

    testF();

    testG();
 
    printf("\nTest H:\n\n");

    t = bst_from_sorted_arr(arr3, 8);
    printf("TEST H1: bst_num_geq(t, -1)\nExpected output: %i\n", bst_size(t));
    printf("Program's output: %i\n", bst_num_geq(t, -1));

    printf("\n\nTEST H2: bst_num_geq(t, 3)\nExpected output: 6\n");
    printf("Program's output: %i\n", bst_num_geq(t, 3));

    printf("\n\nTEST H3: bst_num_geq(t, 10)\nExpected output: 3\n");
    printf("Program's output: %i\n", bst_num_geq(t, 10));

    printf("\n\nTEST H4: bst_num_geq(t, 15)\nExpected output: 0\n");
    printf("Program's output: %i\n", bst_num_geq(t, 15));

    printf("\nTest I:\n\n");

    printf("TEST I1: bst_num_leq(t, -1)\nExpected output: 0\n");
    printf("Program's output: %i\n", bst_num_leq(t, -1));

    printf("\n\nTEST I2: bst_num_leq(t, 3)\nExpected output: 2\n");
    printf("Program's output: %i\n", bst_num_leq(t, 3));

    printf("\n\nTEST I3: bst_num_leq(t, 10)\nExpected output: 6\n");
    printf("Program's output: %i\n", bst_num_leq(t, 10));

    printf("\n\nTEST I4: bst_num_leq(t, 15)\nExpected output: %i\n", bst_size(t));
    printf("Program's output: %i\n", bst_num_leq(t, 15));

    bst_free(t);
}
