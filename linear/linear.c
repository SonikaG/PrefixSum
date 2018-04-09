/*
This is the code in C to calculate prefix sum using the linear algorithm
Authors: Sonika Garg and Madeline Stager
*/

int num;

//method that takes an array of ints and 
//returns an array of equal size of the calculated prefix sums
//NOT SURE IF THIS WORKS YET
int * prefixSum (int *input){
  int i;
  int result [num];
  for (i = 0; i < num; i++) {
    int j;
    result[i] = input [i];
    for (j = 0; j < i; j++){
      result[i] += input[j];
    } 
  }
}

//doesn't do anything rn
int main() {
 return 0;
}
