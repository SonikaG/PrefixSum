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

func aggregate(thread_id int, br *barrier.Barrier, start []int64, end []int64, result []int64){
    var correct int64
    correct = 0
    for i:=0; i<thread_id; i++ {
        correct += result[end[i]]
    }
//    printf("thread id is: %d and the correction is: %d\n", thread_id, correction);
    br.After()
    start_index := start[thread_id]
    end_index := end[thread_id]
    for j:=start_index; j <=end_index; j++{
        result[j] += correct
     }
}

func fastHelper(thread_id int, wg *sync.WaitGroup, br *barrier.Barrier, result []int64, start []int64, end []int64){
    prefixSumLinear(result, start[thread_id], end[thread_id])
    br.Before()
    aggregate(thread_id, br, start, end, result)
    wg.Done()

}

func prefixSumFast(result []int64, input_size int){
    num_threads := 16;
    start_time := time.Now()
    var wg sync.WaitGroup
    br := barrier.New(num_threads)
    start := make([]int64, num_threads)
    end := make([]int64, num_threads)
    var correction int64
    correction = 0
    for j:= 0; j < num_threads; j++{
        if j>0 {
            start[j] = end[j-1]+1
        }else{
            start[j] = 0
        }
        if input_size % num_threads != 0 && j < input_size % num_threads {
            correction = 1
        }else {
            correction = 0
        }
         end[j] = start[j] + (int64)(input_size / num_threads) + correction - 1
    }
    for i:=0; i<num_threads; i++ {
        wg.Add(1)
        go fastHelper(i, &wg, br, result, start, end)
    }

    wg.Wait()
    elapsed := time.Since(start_time)
    fmt.Printf("fast elapsed time: %.9f\n", elapsed.Seconds())

}

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


func prefixSumStride(result []int64, input_size int){

    start := time.Now()
    var wg sync.WaitGroup
    br := barrier.New(input_size-1)
//    result := make([]int64, input_size)
//    copy(result, input)
    for i:=0; i<input_size-1; i++ {
        wg.Add(1)
        go strideHelper(i, &wg, br, result)
    }

    wg.Wait()
    elapsed := time.Since(start)
    fmt.Printf("stride elapsed time: %.9f\n", elapsed.Seconds())


}

//prefix sum method
func prefixSumLinear (result []int64, start_index int64, end_index int64) {
    start := time.Now()
//  result := make([]int64, input_size)
//    fmt.Printf("Start: %d and End: %d\n", start_index, end_index)
    for i:= start_index; i <= end_index; i++{
        if i > start_index{
            result[i] = result[i-1] + result[i]
        }
    }
    elapsed := time.Since(start)
    fmt.Printf("linear elapsed time: %.9f\n", elapsed.Seconds())
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
    result := make([]int64, len(numbers))
    copy(result, numbers)

    if *runType == "linear"{
        prefixSumLinear(result, 0, (int64)(len(result)-1))
        //fmt.Println(result)
    }else if *runType == "stride"{
        prefixSumStride(result, len(result))
        fmt.Println(result)
    }else if *runType == "fast" {
        prefixSumFast(result, len(result))
        //fmt.Println(result)
    }

}
