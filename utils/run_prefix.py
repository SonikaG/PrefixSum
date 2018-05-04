import subprocess





cCmplCmd = "gcc ../implementations/prefix.c -o prefix -pthread"
cRunCmd = "./prefix "

juliaRunCmd = "julia ../implementations/prefix.jl "

goRunCmd = "go run ../implementations/prefix.go -input="

numRuns = 20

#inputFiles = ["prefix5.txt", "prefix20.txt", "prefix100.txt", "prefix1000.txt", "prefix100000.txt", "prefix1000000.txt", "prefix10000000.txt"]
# inputFiles = ["prefix100000.txt", "prefix1000000.txt", "prefix10000000.txt"]
# inputFiles = ["prefix10000000.txt"]
inputFiles = ["prefix100.txt", "prefix1000.txt", "prefix10000.txt"]

def main():
    run("C LINEAR", cRunCmd, True, "linear")
    run("GO LINEAR", goRunCmd, False, "-type=linear")
    # run("JULIA LINEAR", juliaRunCmd, False, "linear")
    # todo need to fix timing for fast
    # run("C FAST", cRunCmd, True, "fast")
    # run("GO FAST", goRunCmd, False, "-type=fast")
    run("C STRIDE", cRunCmd, True, "stride")
    run("GO STRIDE", goRunCmd, False, "-type=stride")



def get_time(p, lineNum, timePosition):
    output = str(p.stdout, 'utf-8')
    # print(output)
    line = output.split("\n")[lineNum]
    #print(output.split("\n")[:-2])
    print(line)
    timeString = line.split()[timePosition]
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
            if run_type == "JULIA LINEAR":
                time = get_time(p, 0, -2)
            else:
                time = get_time(p, 0, -1)
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
