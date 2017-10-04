#!/usr/bin/python3
# Executor do algoritmo k-Nearest Neighbors

import sys
import kNN

''' Parâmetros da execução: [arquivo com dados originais] [arquivo com dados para classificar] [arquivo de saída] [valor de k]'''
def main(argv):
    try: # parsing dos inputs
        dataset_file = argv[0]
        test_file = argv[1]
        output_file = argv[2]
        k = int(argv[3])
    except ValueError as err:
        print('error:',err)
        return

    knn = kNN.kNN(dataset_file, k) # Lê dados originais
    output = knn.classifySet(test_file) # Lê e classifica dados de teste
    knn.writeSet(output, output_file) # Escreve a saída

if __name__ == "__main__":
    main(sys.argv[1:])
