#!/usr/bin/python3
# Smith-Waterman algorithm
# Adapted for INE5540 2017/2

import sys # for args

def main(argv):
    try:
        first, second = parseArguments(argv)
    except ValueError as err:
        print('error:', err)
        return

#    print(first)
#    print(second)

    score = computeSW(first,second)
    print('Max Score is '+str(score))

'''-----------------------------------------'''
def parseArguments(argv):
    '''
        Parses the two input files, each with a nucleotide sequence.
        Only the bases A, C, G, and T are valid, but we do not check the input.
        Only the first 5000 bases will be considered.
    '''
    max_base = 5000
    first_file = open(argv[0], "r")
    first_string = first_file.read(max_base)
    first_file.close()
    second_file = open(argv[1], "r")
    second_string = second_file.read(max_base)
    second_file.close()
    return first_string, second_string

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
        for j in range(1, columns):
            score = computeScore(score_matrix, first_seq[i-1], second_seq[j-1], i, j)
            if score > max_score:
                max_score = score
            score_matrix[i][j] = score
#            print (i, j, score)

    return max_score

'''-----------------------------------------'''
def computeScore(matrix, first_base, second_base, i, j):
    '''
        Computes the score for a given matrix cell.
        Takes as input the matrix, the two bases to compare,
        and the indexes from where they came.
    '''
    # Sample scores to use for matching, mismatching, and gaps
    match    = 2
    mismatch = -1
    gap      = -1

    similarity = match if first_base == second_base else mismatch
    diagonal = matrix[i - 1][j - 1] + similarity
    up   = matrix[i - 1][j] + gap
    left = matrix[i][j - 1] + gap

    return max(0, up, left, diagonal)

'''-----------------------------------------'''
if __name__ == "__main__":
    main(sys.argv[1:]) # Executes the code ignoring the name of the file

