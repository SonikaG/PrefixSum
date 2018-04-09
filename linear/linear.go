package main
import "fmt"

func prefixSum (input []int64, input_size int) ([]int64) {
    result := make([]int64, input_size)
    for i:= 0; i < input_size; i++{
        if i == 0{
            result[i] = input [i]
        }else{
            result[i] = result[i-1] + input [i]
        }
    }
    return result;
}

func main (){
    testOne := []int64{1, 2, 3, 4, 5}
    result := prefixSum(testOne, len(testOne))
    fmt.Println(result)

    testTwo := []int64{-2, 16, 4, 1, 7, -3, 8, 3, 0, -6}
    resultTwo := prefixSum(testTwo, len(testTwo))
    fmt.Println(resultTwo)
}
