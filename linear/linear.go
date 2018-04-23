package main
import "fmt"
import "io/ioutil"
import "strings"
import "strconv"
import "time"
import "flag"
import "barrier"
import "sync"


//var result []int64

func strideHelper(thread_id int, wg *sync.WaitGroup, br *barrier.Barrier, result []int64){
    size := len(result)
    for stride:=1; stride < size; stride *= 2 {
        my_value := result[thread_id]
        br.Before()
        if thread_id+stride < size {
            result[thread_id+stride] += my_value
        }
        br.After()
    }
    wg.Done()
}


func prefixSumStride(input []int64, input_size int){

    start := time.Now()
    var wg sync.WaitGroup
    br := barrier.New(input_size-1)
    result := make([]int64, input_size)
    copy(result, input)
    for i:=0; i<input_size-1; i++ {
        wg.Add(1)
        go strideHelper(i, &wg, br, result)
    }

    wg.Wait()
    elapsed := time.Since(start)
    fmt.Printf("stride elapsed time: %.9f\n", elapsed.Seconds())
    fmt.Println(result)


}

//prefix sum method
func prefixSumLinear (input []int64, input_size int) ([]int64) {
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
    fmt.Printf("linear elapsed time: %.9f\n", elapsed.Seconds())
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
    runType := flag.String("type", "test", "name of run type")
    flag.Parse()
    //fmt.Println(*inputFile)

    /*testOne := []int64{1, 2, 3, 4, 5}
    result := prefixSum(testOne, len(testOne))
    fmt.Println(result)

    testTwo := []int64{-2, 16, 4, 1, 7, -3, 8, 3, 0, -6}
    resultTwo := prefixSum(testTwo, len(testTwo))
    fmt.Println(resultTwo)*/

    numbers := readFile(*inputFile)


    if *runType == "linear"{
        result := prefixSumLinear(numbers, len(numbers))
        fmt.Println(result)
    }else if *runType == "stride"{
        prefixSumStride(numbers, len(numbers))
    }

}
