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
    int j;
    result[i] = input [i];
    for (j = 0; j < i; j++){
      result[i] += input[j];
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
  int *result = prefixSum(test1, 5);
  printArray(result, 5);
  return 0;
}
