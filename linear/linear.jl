

function prefixSum(input, input_size)
    result = Array{Int64, 1}(input_size)
    for i = 1:input_size
        if i > 1
            result[i] = result[i-1] + input[i]  
        else
            result[i] = input[i]
        end
    end
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
    println("SUCESS")
else
    println("FAILED")
end
    

