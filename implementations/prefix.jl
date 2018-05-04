#= An implementation of the linear algorithm of prefix sum in Julia
Authors: Madeline Stager and Sonika Garg =#


#=

function barrierInit(threads)
    global arrival = Base.Semaphore(1)
    global departure = Base.Semaphore(1)
    global counter = 0
    global numThreads = threads
    Base.acquire(departure)
end

@everywhere function barrierWait(arrival, departure, counter, numThreads)
    println(counter)
    Base.acquire(arrival)
    counter = counter + 1
    if counter < numThreads
        Base.release(arrival)
    else
        Base.release(departure)
    end
    Base.acquire(departure)
    counter = counter - 1
    if counter > 0
        Base.release(departure)
    else
        Base.release(arrival)
    end
end



@everywhere function strideHelper(id, arrival, departure, counter, numThreads)
    stride = 1
    while stride<10
        println("hello 1 ", stride, " ", id)
        barrierWait(arrival, departure, counter, numThreads)
        println("hello 2 ", stride, " ", id)
        barrierWait(arrival, departure, counter, numThreads)
        println("hello 3 ", stride, " ", id)
        stride *= 2
    end
end


function prefixSumStride()
    println(Threads.nthreads())
    barrierInit(5)
    threads = Array{Future, 1}(5)
    for i = 2:6
        println("starting ", i)
        threads[i-1] = remotecall(strideHelper, i, i-1, arrival, departure, counter, 5)
        println("done starting ", i)
    end

    println(counter)
    for i = 1:5
        wait(threads[i])
    end
end

=#

#prefixSum linear implementation, takes an input array and and input size (int)
function prefixSumLinear(input, input_size)
    tic()
    result = Array{Int64, 1}(input_size)
    for i = 1:input_size
        if i > 1
            result[i] = result[i-1] + input[i]  
        else
            result[i] = input[i]
        end
    end
    toc()
    result
end



function arrayEqual(a, b)
    if length(a) != length(b)
        return false
    else
        for i = 1:length(a)
            if a[i] != b[i]
                return false
            end
        end
        return true
    end
end

#main function 
function main()
    inputFile = ARGS[1]


    numbers = readInput(inputFile)
#=  tic()
    toc()

    tic()
    toc()

    tic() =#
    #the line that is actually running
    result = prefixSumLinear(numbers, length(numbers))
#=  toc()

    tic()
    result = prefixSumLinear(numbers, length(numbers))
    toc() =#

    #println(result)

   # prefixSumStride()

end 

#function to read in the values from a file 
function readInput(fileName)
    f = open(fileName)
    num_points = parse(Int, readline(f))
    #println(num_points)
    array = readline(f)
    #println(array)
    values = split(array, " ")
    #println(values)
    numbers = Array{Int64, 1}(num_points)
    for i = 1:length(values)-1
        numbers[i] = parse(Int, values[i])
    end
    #println(numbers)
    close(f)
    return numbers
end

#=
# test 1
# answer should be [1, 3, 6, 10, 15]
x = [1 2 3 4 5]
r = prefixSum(x, length(x))
println(r)
if arrayEqual(r, [1 3 6 10 15])
    println("SUCESS")
else
    println("FAILED")
end

# test 2
# answer should be [-2, 14, 18, 19, 26, 23, 31, 34, 34, 28]
x = [-2 16 4 1 7 -3 8 3 0 -6]
r = prefixSum(x, length(x))
println(r)
if arrayEqual(r,  [-2, 14, 18, 19, 26, 23, 31, 34, 34, 28])
    println("SUCCESS")
else
    println("FAILED")
end =#

main()
