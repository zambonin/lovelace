# Implementação de k-Nearest Neighbors do Desafio 4
# O código não deve ser trocado de linguagem
import csv
import math
import operator

class kNN():
    ''' Init: lê input, define o valor de K '''
    def __init__(self,input_file_name,K):
        self.K = K
        self.data, self.n_params, self.header = self._readData(input_file_name)

    ''' Read Data: lê o input de um arquivo csv '''
    def _readData(self,file_name):
        with open(file_name, 'r') as csvfile:
            lines = csv.reader(csvfile)
            # Gera uma lista do arquivo com cada linha como uma lista
            # A primeira linha sempre contém os tipos/nomes da colunas
            data = list(lines)
            # Pega a quantidade de parâmetros por item
            # O primeiro parametro é sempre o tipo do item
            n_params = len(data[0])

            points = []
            for i in range(1,len(data)): # Para toda linha de dados
                for j in range(1,n_params): # Para todas as 'coordenadas' de um item
                    data[i][j] = float(data[i][j])
                points.append(data[i])
            return points, n_params, data[0]

    ''' Retorna os k vizinhos mais próximos de um item '''
    def _getNeighbors(self, item):
        distances = []
        # Calcula distância para todos os itens no dataset
        for dataline in self.data:
            distance = 0
            for i in range(1, self.n_params):
                distance += (dataline[i] - item[i]) ** 2
            distances.append((dataline, distance))
        # Ordena os itens por distâncias
        distances.sort(key=operator.itemgetter(1))
        return [distances[i][0] for i in range(self.K)]

    ''' Classifica um item baseado nos tipos dos K vizinhos mais próximos '''
    def classify(self, item):
        # Pega vizinhos
        neighbors = self._getNeighbors(item)
        # Organiza conjunto de votos por tipo possível
        types = {}
        for neighbor in neighbors:
            n_type = neighbor[0] # Tipo do vizinho
            if n_type in types:
                types[n_type] += 1
            else:
                types[n_type] = 1
        # Ordena conjunto de votos por tipo
        ranking = sorted(types, key=types.get, reverse=True)
        return ranking[0][0] # Retorna tipo mais comum entre vizinhos

    ''' Classifica um conjunto de dados de um arquivo csv '''
    def classifySet(self, input_file_name):
        input_data, input_n_params, input_header = self._readData(input_file_name)
        # Se a quantidade de parâmetros for diferente, não tenta classificar
        if input_n_params != self.n_params:
            return []

        # Classifica cada item e os retorna
        prediction = []
        for input_line in input_data:
            input_line[0] = self.classify(input_line)
            prediction.append(input_line)
        return prediction

    ''' Escreve um arquivo csv usando uma lista de itens classificados '''
    def writeSet(self, data, output_file_name):
        with open(output_file_name, 'w') as csvfile:
            writer = csv.writer(csvfile)
            # Escreve cabeçalho
            writer.writerow(self.header)
            # Escreve todas as linhas de dados
            for row in data:
                writer.writerow(row)
