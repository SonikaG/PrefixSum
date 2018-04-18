package main
import "fmt"
import "io/ioutil"
import "strings"
import "strconv"
import "time"
import "flag"

//prefix sum method
func prefixSum (input []int64, input_size int) ([]int64) {
    start := time.Now()
    result := make([]int64, input_size)
    for i:= 0; i < input_size; i++{
        if i == 0{
            result[i] = input [i]
        }else{
            result[i] = result[i-1] + input [i]
        }
    }
    elapsed := time.Since(start)
    fmt.Printf("elapsed time: %.9f\n", elapsed.Seconds())
    return result;
}

//function to read the contents of the file
func readFile(input string) ([]int64){
  whole, err := ioutil.ReadFile(input)
  if err != nil {
    fmt.Printf("OH NO, couldn't read file")
    panic(err)
  }
  lines := strings.Split(string(whole), "\n")

  num_points, err := strconv.Atoi(lines[0])
  //fmt.Println(num_points)
  values := strings.Split(lines[1], " ")
  numbers := make([]int64, num_points)
  for i := 0; i < len(values)-1; i++{
    val, err := strconv.ParseInt(values[i], 10, 64)
    if(err != nil){
      panic(err)
    }
    numbers[i] = val
  }
  //fmt.Println(numbers)
  return numbers

}

//main method 
func main (){


    inputFile := flag.String("input", "test", "name of input file")
    flag.Parse()
//    fmt.Println(*inputFile)

    /*testOne := []int64{1, 2, 3, 4, 5}
    result := prefixSum(testOne, len(testOne))
    fmt.Println(result)

    testTwo := []int64{-2, 16, 4, 1, 7, -3, 8, 3, 0, -6}
    resultTwo := prefixSum(testTwo, len(testTwo))
    fmt.Println(resultTwo)*/


    numbers := readFile(*inputFile)
//    start := time.Now()
    result := prefixSum(numbers, len(numbers))
//    elapsed := time.Since(start)
//    fmt.Printf("elapsed time: %.9f\n", elapsed.Seconds())
    fmt.Println(result)
}
