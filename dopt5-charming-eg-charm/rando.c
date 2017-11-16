#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    if (argc < 2) return 1;
    int size = atoi(argv[1]);
    int* randos = (int*) malloc(size*sizeof(int));
    int* sums = (int*) malloc(size*sizeof(int));

    for (int i = 0; i < size; ++i) randos[i] = rand()%100;
    for (int j = 0; j < size; ++j) sums[j] = randos[j] + randos[(j+1)%size] + randos[(size+j-1)%size];
    for (int k = 0; k < size; ++k) printf("[%d] rand = %d\t sum with neighbors = %d\n",k,randos[k],sums[k]);

    free(randos);
    free(sums);
}
