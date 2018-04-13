import subprocess

cCmplCmd = "gcc ../linear/linear.c -o clinear"
cRunCmd = "./clinear "

juliaRunCmd = "julia ../linear/linear.jl "

goRunCmd = "go run ../linear/linear.go -input="

numRuns = 20

inputFiles = ["prefix5.txt", "prefix20.txt", "prefix100.txt", "prefix1000.txt"]

def main():
    run_c_linear()
    # run_julia_linear()
    run_julia_linear()
    run_go_linear()

def get_time(p, lineNum):
    output = str(p.stdout, 'utf-8')
    # print(output)
    line = output.split("\n")[lineNum]
    timeString = line.split()[2]
    time = float(timeString)
    # print(time)
    return time

def run_go_linear():
    print("RUNNING GO\n")
    totalTime = 0
    for file_name in inputFiles:
        for i in range(0, numRuns):
            p = subprocess.run(cRunCmd+file_name, shell=True, stdout=subprocess.PIPE)
            time = get_time(p, 0)
            totalTime += time
        averageTime = totalTime/numRuns
        print("averageTime: " + str(averageTime) + "for file " + file_name + "\n")
    print("DONE RUNNING GO\n")

def run_julia_linear():
    print("RUNNING JULIA\n")
    totalTime = 0
    for file_name in inputFiles:
        for i in range(0, numRuns):
            p = subprocess.run(juliaRunCmd+file_name, shell=True, stdout=subprocess.PIPE)
            time = get_time(p, 1)
            totalTime += time
        averageTime = totalTime / numRuns
        print("averageTime: " + str(averageTime) + "for file " + file_name + "\n")
    print("DONE RUNNING JULIA\n")


def run_c_linear():
    print("RUNNING C\n")
    p = subprocess.run(cCmplCmd, shell=True, stdout=subprocess.PIPE)
    output = str(p.stdout, 'utf-8')
    print(output)
    totalTime = 0
    for file_name in inputFiles:
        for i in range(0, numRuns):
            p = subprocess.run(cRunCmd+file_name, shell=True, stdout=subprocess.PIPE)
            time =get_time(p, 0)
            totalTime += time
        averageTime = totalTime / numRuns
        print("averageTime: " + str(averageTime) + "for file " + file_name + "\n")
    print("DONE RUNNING C\n")

if __name__ == '__main__':
    main()