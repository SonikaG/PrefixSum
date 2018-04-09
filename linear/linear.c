/*
This is the code in C to calculate prefix sum using the linear algorithm
Authors: Sonika Garg and Madeline Stager
*/

#include <stdio.h>
#include "stdlib.h"

//method that takes an array of ints and 
//returns an array of equal size of the calculated prefix sums
//NOT SURE IF THIS WORKS YET
int * prefixSum (int *input, int input_size){
  int i;
  int *result = malloc(input_size *sizeof(int));
  for (i = 0; i < input_size; i++) {
    if (i > 0){
      result[i] = result [i-1] + input[i];
    }
    else{
    result[i] = input [i];
    } 
  }
  return result;
}

//method to print an array
void printArray (int *input, int input_size){
 int i;
 printf("[");
 for (i = 0; i < input_size-1; i++){
   printf("%d, ", input[i]);
 }
 printf("%d]\n", input[input_size-1]);
}

//doesn't do anything rn
int main() {
  int test1 [5] = {1, 2, 3, 4, 5};
  int length1 = sizeof(test1)/sizeof(int);
  int *result = prefixSum(test1, length1);

  int test2[10] = {-2, 16, 4, 1, 7, -3, 8, 3, 0, -6};
  int length2 = sizeof(test2)/sizeof(int);
  int *result2 = prefixSum(test2, length2);
  
  //answer should be [1, 3, 6, 10, 15]
  printArray(result, length1);

  //answer should be [-2, 14, 18, 19, 26, 23, 31, 34, 34, 28]
  printArray(result2, length2);
  free(result);
  free(result2);
  return 0;
}
