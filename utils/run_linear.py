import subprocess

cCmplCmd = "gcc ../linear/linear.c -o clinear"
cRunCmd = "./clinear prefixTest1.txt"

juliaRunCmd = "julia ../linear/linear.jl"

goRunCmd = "go run ../linear/linear.go"

def main():
    run_c_linear()
    run_julia_linear()
    run_julia_linear()
    run_go_linear()

def get_time(p):
    output = str(p.stdout, 'utf-8')
    print(output)
    line = output.split("\n")[0]
    timeString = line.split()[2]
    time = float(timeString)
    print(time)

def run_go_linear():
    print("RUNNING GO\n")
    p = subprocess.run(cRunCmd, shell=True, stdout=subprocess.PIPE)
    get_time(p)
    print("DONE RUNNING GO\n")

def run_julia_linear():
    print("RUNNING JULIA\n")
    p = subprocess.run(juliaRunCmd, shell=True, stdout=subprocess.PIPE)
    get_time(p)
    print("DONE RUNNING JULIA\n")


def run_c_linear():
    print("RUNNING C\n")
    p = subprocess.run(cCmplCmd, shell=True, stdout=subprocess.PIPE)
    output = str(p.stdout, 'utf-8')
    print(output)
    p = subprocess.run(cRunCmd, shell=True, stdout=subprocess.PIPE)
    get_time(p)
    print("DONE RUNNING C\n")

if __name__ == '__main__':
    main()