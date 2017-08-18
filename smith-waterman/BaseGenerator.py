#!/usr/bin/python3

import sys # for args
import random

def main(argv):
    '''
        Generates a string composed of A, C, T, and G
        parameters: 'size of the string' 'seed for pseudo-random generation'
    '''
    bases = ['A', 'C', 'G', 'T']
    try:
        size = int(argv[0])
        seed = argv[1]

        random.seed(seed,2)
        base = ""
        for i in range(size):
            base+= bases[random.randint(0,3)]
        print(base)

    except ValueError as err:
        print('error:',err)
        return

if __name__ == "__main__":
    main(sys.argv[1:])
