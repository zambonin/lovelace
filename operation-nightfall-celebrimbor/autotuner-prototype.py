#!/usr/bin/python3
# Auto-tuner prototype
# Built for INE5540 robot overlords

import subprocess # to run stuff
import sys # for args, in case you want them
import time # for time

def tuner(argv):
    exec_file = 'matmult'
    compilation_line = ['gcc','-o',exec_file,'mm.c']
    steps = ['-DSTEP=2']

    # Compile code
    compilation_try = subprocess.run(compilation_line+steps)
    if (compilation_try.returncode == 0):
        print("Happy compilation")
    else:
        print("Sad compilation")

    # Run code
    input_size = str(4)
    t_begin = time.time() # timed run
    run_trial = subprocess.run(['./'+exec_file, input_size])
    t_end = time.time()
    if (run_trial.returncode == 0):
        print("Happy execution in "+str(t_end-t_begin))
    else:
        print("Sad execution")


if __name__ == "__main__":
    tuner(sys.argv[1:]) # go auto-tuner
