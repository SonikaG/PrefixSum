import subprocess

cCmplCmd = "gcc ../linear/linear.c -o clinear -pthread"
cRunCmd = "./clinear "

juliaRunCmd = "julia ../linear/linear.jl "

goRunCmd = "go run ../linear/linear.go -input="

numRuns = 20

inputFiles = ["prefix5.txt", "prefix20.txt", "prefix100.txt", "prefix1000.txt"]

def main():
    run("C LINEAR", cRunCmd, True, "linear")
    run("JULIA LINEAR", juliaRunCmd, False, "linear")
    run("GO LINEAR", goRunCmd, False, "linear")

    run("C STRIDE", cRunCmd, True, "stride")

def get_time(p, lineNum):
    output = str(p.stdout, 'utf-8')
    # print(output)
    line = output.split("\n")[lineNum]
    #print(output.split("\n")[:-2])
    #print(line)
    timeString = line.split()[2]
    time = float(timeString)
    # print(time)
    return time

def run(run_type, runCmd, shouldCompile, algo_type):
    print("RUNNING " + run_type + "\n")
    if shouldCompile:
        p = subprocess.run(cCmplCmd, shell=True, stdout=subprocess.PIPE)
        output = str(p.stdout, 'utf-8')
        print(output)

    for file_name in inputFiles:
        totalTime = 0
        for i in range(0, numRuns):
            p = subprocess.run(runCmd + file_name + " " + algo_type, shell=True, stdout=subprocess.PIPE)
            time = get_time(p, 0)
            totalTime += time
        averageTime = totalTime/numRuns
        print("averageTime: " + str(averageTime) + " for file " + file_name + "\n")
    print("DONE RUNNING " + run_type + "\n")


"""
def run_go_linear():
    print("RUNNING GO\n")
    for file_name in inputFiles:
        totalTime = 0
        for i in range(0, numRuns):
            p = subprocess.run(cRunCmd+file_name, shell=True, stdout=subprocess.PIPE)
            time = get_time(p, 0)
            totalTime += time
        averageTime = totalTime/numRuns
        print("averageTime: " + str(averageTime) + " for file " + file_name + "\n")
    print("DONE RUNNING GO\n")

def run_julia_linear():
    print("RUNNING JULIA\n")
    for file_name in inputFiles:
        totalTime = 0
        for i in range(0, numRuns):
            p = subprocess.run(juliaRunCmd+file_name, shell=True, stdout=subprocess.PIPE)
            time = get_time(p, 3)
            totalTime += time
            # print(time)
            # print(totalTime)
        averageTime = totalTime / numRuns
        print("averageTime: " + str(averageTime) + " for file " + file_name + "\n")
    print("DONE RUNNING JULIA\n")


def run_c_linear():
    print("RUNNING C\n")
    p = subprocess.run(cCmplCmd, shell=True, stdout=subprocess.PIPE)
    output = str(p.stdout, 'utf-8')
    print(output)
    for file_name in inputFiles:
        totalTime = 0
        for i in range(0, numRuns):
            p = subprocess.run(cRunCmd+file_name, shell=True, stdout=subprocess.PIPE)
            time =get_time(p, 0)
            totalTime += time
        averageTime = totalTime / numRuns
        print("averageTime: " + str(averageTime) + " for file " + file_name + "\n")
    print("DONE RUNNING C\n")
"""
if __name__ == '__main__':
    main()
