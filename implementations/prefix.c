/*
This is the code in C to calculate prefix sum using the linear algorithm
Authors: Sonika Garg and Madeline Stager
*/

#include <stdio.h>
#include "stdlib.h"
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <math.h>

//global variables
int * result;
int size;
//int ** tree_new;
//int ** tree_old;

//global barrier
pthread_barrier_t bar;

int* start;
int* end;

struct fastPrefixArgs {
    int thread_id;
//    int start;
//    int range;
};


//method to print an array
void printArray (int *input, int input_size){
 int i;
 printf("[");
 for (i = 0; i < input_size-1; i++){
   printf("%d, ", input[i]);
 }
 printf("%d]\n", input[input_size-1]);
}

//the linear algorithm implementation of prefix sum
//takes the input array and its size as parameters
//NOT SURE IF THIS WORKS YET
//__attribute__ ((optimize(1)))
void prefixSumLinear (int start, int end, int print) {
//  printArray(result, input_size);
//  int *result = malloc(input_size *sizeof(int));
  clock_t start_time = clock();
  int i;
  for (i = start; i <= end; i++) {
    if (i > start){
      result[i] = result[i-1] + result[i];
    }
  }
  clock_t end_time = clock();
  double elapsed_time = (double)(end_time-start_time)/CLOCKS_PER_SEC;
  if (print){
    printf("linear elapsed time: %f\n", elapsed_time);
  }
  return;
}

void aggregate(int thread_id){
    int correction = 0;
    int i;
    for (i=0; i<thread_id; i++){
        correction += result[end[i]];
    }
//    printf("thread id is: %d and the correction is: %d\n", thread_id, correction);
    pthread_barrier_wait(&bar);
    int start_index = start[thread_id];
    int end_index = end[thread_id];
    int j;
    for (j=start_index; j <=end_index; j++){
        result[j] += correction;
     }

}

void * fastHelper(void *arguments){
    int thread_id = *((int*)arguments);
//    printf("thread %d, start is %d, end is %d, range is %d\n", thread_id, start[thread_id], end[thread_id], end[thread_id] - start[thread_id]+1);
    prefixSumLinear(start[thread_id], end[thread_id], 0);
    pthread_barrier_wait(&bar);
    //read values from previous chunks to know what correction should be added
    //add the correction to each number
    aggregate(thread_id);

    return NULL;
}

void prefixSumFast(int *input, int input_size){
    int num_threads = 8;
    pthread_t threads[num_threads];

//    result = malloc(sizeof(int)*input_size);
//    memcpy(result, input, sizeof(int)*input_size);

    struct fastPrefixArgs* arguments = malloc(sizeof(struct fastPrefixArgs)*num_threads);


    int correction = 0;
    int i;
    for (i=0; i<num_threads; i++){
        if (i>0){
            start[i] = end[i-1]+1;
        }else{
            start[i] = 0;
        }
        if (input_size % num_threads != 0 && i < input_size % num_threads) {
            correction = 1;
        }else {
            correction = 0;
        }
         end[i] = start[i] + (input_size / num_threads) + correction - 1;
//        printf("thead %d starts at %d and ends at %d\n", i, start[i], end[i]);
//        printf("points per thread %d, correction %d\n", input_size / num_threads, correction);
    }

    if(pthread_barrier_init(&bar, NULL, num_threads)){
        printf("error, barrier did not work");
        return;
    }


    clock_t start = clock();
//    int i;
    for (i = 0; i < num_threads; i++){
        int* thread_id = malloc(sizeof(int));
        *thread_id = i;
        pthread_create(&threads[i], NULL, fastHelper, (void*)(thread_id));
    }
//    printf("all threads started\n");

    //join all the threads
      int j;
      for (j = 0; j < num_threads; j++){
            if(pthread_join(threads[j], NULL)){
                printf("error\n");
                fprintf(stderr, "Error joining thread\n");
                return;
            }
      }
      clock_t end = clock();
      double elapsed_time = (double)(end-start)/CLOCKS_PER_SEC;
      printf("fast elapsed time: %f\n", elapsed_time);
//      printArray(result, input_size)

}



//the tree (up-down) algorithm implementation of prefix sum
//takes the input array and its size as parameters
//void * prefixSumTree(int *input, int input_size){
//  int i;
//  double depth = log(input_size)/log(2);
//  int **ar = (int **)malloc(sizeof(int *) * (int)(ceil(depth)));
//  for (i = 0; i < ceil(depth); i++){
//    int size = input_size*1.0/(pow(2.0,i));
//    ar[i] = (int *)malloc(sizeof(int) * size);
//  }
//}

//helper function that each thread executes
void * strideHelper(void *arg){
  int stride;
  int *my_id = (int *)arg;
  //printf("my id: %d\n", *my_id);
  for (stride = 1; stride <= (size-1); stride = stride * 2){
    int my_value = result[*my_id];
    //printf("my value and my id: %d, %d\n", my_value, *my_id);
    pthread_barrier_wait(&bar);
    if(*my_id + stride < size){
      result[*my_id + stride] += my_value;
    }  
    pthread_barrier_wait(&bar);
  } 
}

//the stride algorithm implementation of prefix sum
//takes the input array and its size as parameters
int * prefixSumStride (int *input, int input_size){
  pthread_t threads[input_size-1];
//  int k;
  size = input_size;
  result = malloc(sizeof(int)*input_size);
  memcpy(result, input, sizeof(int)*input_size);
  if(pthread_barrier_init(&bar, NULL, input_size-1)){
    printf("error, barrier did not work");
    return NULL;
  }
  clock_t start = clock();
  int i;
  for (i = 0; i < input_size-1; i++){
    int *thread_id = (int *)malloc(sizeof(int));
    *thread_id = i;
    //printf("value of i %d\n", i);
    pthread_create(&threads[i], NULL, strideHelper, (void*)(thread_id));
  }

  //join all the threads
  int j;
  for (j = 0; j < input_size-1; j++){
        if(pthread_join(threads[j], NULL)){
            printf("error\n");
            fprintf(stderr, "Error joining thread\n");
            return NULL;
        }
  }
  clock_t end = clock();
  double elapsed_time = (double)(end-start)/CLOCKS_PER_SEC;
  printf("stride elapsed time: %f\n", elapsed_time);
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
    result = malloc(sizeof(int)*num_points);
    memcpy(result, values, sizeof(int)*num_points);

    start = malloc(sizeof(int)*1);
    end = malloc(sizeof(int)*1);


    if(strcmp(argv[2],"linear") == 0){
      prefixSumLinear(0, num_points-1, 1);
//      printArray(result, num_points);
    }
    else if(strcmp(argv[2],"stride") == 0){
      prefixSumStride(values, num_points);
//      printArray(result, num_points);
    }else if(strcmp(argv[2], "fast") == 0){
        prefixSumFast(values, num_points);
//        printArray(result, num_points);
    }
//  int test1 [5] = {1, 2, 3, 4, 5};
//  int length1 = sizeof(test1)/sizeof(int);
//  int *result = prefixSumStride(test1, length1);
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
