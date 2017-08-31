#!/usr/bin/python3
# Auto-tuner prototype
# Built for INE5540 robot overlords

import subprocess # to run stuff
import sys # for args, in case you want them
import time # for time

def tuner(argv):
    exec_file = 'matmult'
    compilation_line = ['gcc','-o',exec_file,'mm.c']
    timeList = []
    steps = ['-DSTEP=2', '-DSTEP=4','-DSTEP=8','-DSTEP=16','-DSTEP=32']
    bestTime=float("inf");
    bestFlag=''
    bestStep=''
    flags=["-O0", "-O1", "-O2", "-O3", "-Og", "-Os", "-Ofast", "-march=native", "-mtune=native", "-g"]
    flags_n=['-march=native', '-mtune=native','-g']
    for f in flags:
        for s in steps:
            timeList = []
            print(bestFlag)
            print(bestTime)
            print(f)
            # Compile code
            compilation_try = subprocess.run(compilation_line+steps+[f])
            if (compilation_try.returncode == 0):
                print("Happy compilation")
            else:
                print("Sad compilation")

            # Run code
            for num_it in range(10):
                input_size = str(8)
                t_begin = time.time() # timed run
                run_trial = subprocess.run(['./'+exec_file, input_size])
                t_end = time.time()
                if (run_trial.returncode == 0):
                    print("Happy execution in "+str(t_end-t_begin))
                else:
                    print("Sad execution")
                timeList.append(t_end-t_begin);

            sum = 0;
            for elem in timeList:
                sum += elem
            avg = sum/len(timeList)
            print(compilation_line);
            if (avg < bestTime):
                if (f[1] != "O"):
                    bestFlag=bestFlag+f
                else:
                    bestFlag=[f]
                bestStep=[s]
                bestTime=avg
            print(bestFlag)
            print(bestTime)
            print(bestStep)
    compilation_line = compilation_line+bestStep+bestFlag
if __name__ == "__main__":
    tuner(sys.argv[1:]) # go auto-tuner
