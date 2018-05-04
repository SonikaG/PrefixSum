#Some Notes on How to Run Our Code

To run prefix.jl (the little julia code that survived), you need to download Julia. After downloading it please add the following line to your bashrc:

export PATH =$PATH:~/julia-d386e40c17/bin/

We used a barrier implementation for go found here https://medium.com/golangspec/reusable-barriers-in-golang-156db1f75d0b

To be able to run your go code using that barrier you need to add the following line to your bashrc as well:

export GOPATH="~/your_path_to/PrefixSum/implementations"

#To Make Data Files to Run Our Code on 

We made a script to create data. It's called makefile. You will need to edit this file to get a new file with X amount of data. The way to do is to add the following line at the end of the file:

createFile(X, <\name of the file you want to create>)


