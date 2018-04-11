/*
This is the code in C to calculate prefix sum using the linear algorithm
Authors: Sonika Garg and Madeline Stager
*/

#include <stdio.h>
#include "stdlib.h"
#include <string.h>
#include <time.h>

//method that takes an array of ints and 
//returns an array of equal size of the calculated prefix sums
//NOT SURE IF THIS WORKS YET
int * prefixSum (int *input, int input_size){
  clock_t start = clock();
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
  clock_t end = clock();
   double elapsed_time = (double)(end-start)/CLOCKS_PER_SEC;
  printf("elapsed time: %f\n", elapsed_time);
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

char* loadInputFile(char* filename){
    FILE* inputFile = fopen(filename, "r");
    if (!inputFile) {
        printf( "can't open file\n");
        return NULL;
    }

    fseek(inputFile, 0, SEEK_END);
    int length = ftell(inputFile);
    fseek(inputFile, 0, SEEK_SET);
    char * buffer = (char*)malloc(length);
    if (!buffer) {
        printf("can't allocate memory\n");
        return NULL;
    }
    fread(buffer, 1, length, inputFile);
    fclose(inputFile);
    return buffer;

}

int* readInput(char* filename, int* num_points){
    char* input = loadInputFile(filename);

    //Get number of values in input
    char* line = strtok(input, "\n");
//    int num_points = (int)(strtoll(line, NULL, 10));
    *num_points = atoi(line);
//    printf("num_points: %d\n", *num_points);

    // Parse values in input
    int* values =(int*) malloc(sizeof(int) * (*num_points));
    line = strtok(NULL, "\n");

    char* valueString = strtok(line, " ");
    int i=0;
    while(valueString){
//        printf("%s\n", valueString);
        int value = atoi(valueString);
        values[i] = value;
        valueString = strtok(NULL, " ");
        i++;
    }

    return values;


}

//doesn't do anything rn
int main(int argc, char** argv) {
    char* inputfile = argv[1];
    int num_points;
    int* values = readInput(inputfile, &num_points);
//    printArray(values, num_points);
    int * r = prefixSum(values, num_points);
    printArray(r, num_points);

//  int test1 [5] = {1, 2, 3, 4, 5};
//  int length1 = sizeof(test1)/sizeof(int);
//  int *result = prefixSum(test1, length1);
//
//  int test2[10] = {-2, 16, 4, 1, 7, -3, 8, 3, 0, -6};
//  int length2 = sizeof(test2)/sizeof(int);
//  int *result2 = prefixSum(test2, length2);
//
//  //answer should be [1, 3, 6, 10, 15]
//  printArray(result, length1);
//
//  //answer should be [-2, 14, 18, 19, 26, 23, 31, 34, 34, 28]
//  printArray(result2, length2);
//  free(result);
//  free(result2);
  return 0;
}
