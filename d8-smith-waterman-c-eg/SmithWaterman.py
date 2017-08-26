#!/usr/bin/python3
# Smith-Waterman algorithm
# Adapted for INE5540 2017/2

import sys # for args

def main(argv):
    try:
        '''
        Parses the two input files, each with a nucleotide sequence.
        Only the bases A, C, G, and T are valid, but we do not check the input.
        Only the first 5000 bases will be considered.
        '''
        max_base = 5000
        first_file = open(argv[0], "r")
        first = first_file.read(max_base)
        first_file.close()
        second_file = open(argv[1], "r")
        second = second_file.read(max_base)
        second_file.close()

    except ValueError as err:
        print('error:', err)
        return

    score = computeSW(first,second)
    print('Max Score is '+str(score))

'''-----------------------------------------'''
def computeSW(first_seq, second_seq):
    '''
        Creates a score matrix with the local alignment scores.
        Returns the best alignment score found.
    '''
    rows = len(first_seq)
    columns = len(second_seq)

    score_matrix = [[0 for col in range(columns)] for row in range(rows)]

    max_score = 0

    # Computes the alignment scores
    for i in range(1, rows):
        first_base = first_seq[i-1]
        for j in range(1, columns):
            similarity = 2 if first_base == second_seq[j-1] else -1
            diagonal = score_matrix[i - 1][j - 1] + similarity
            up   = score_matrix[i - 1][j] - 1
            left = score_matrix[i][j - 1] - 1
            score = 0

            if up > score:
                score = up
            if left > score:
                score = left
            if diagonal > score:
                score = diagonal
            
            score_matrix[i][j] = score
            
            if score > max_score:
                max_score = score
    return max_score

'''-----------------------------------------'''
if __name__ == "__main__":
    main(sys.argv[1:]) # Executes the code ignoring the name of the file

