#include <stdio.h>
#include <stdlib.h>

long fat(int n)
{
    long res;
    int i;
    res = 1;

    for(i = 2; i <= n; i++){
       res *= i; 
    }
    return res;
}

int main(int argc, char **argv)
{
  int n;
  long resultado;
  if(argc<2){
    printf("uso ./fatorial <numero natural>\n");
    exit(1);
  }
  n = atoi(argv[1]);
  if(n < 0){
    printf("Erro! Numero de entrada nao e' natural\n");
    exit(1);
  }

  printf("Calculando fatorial de %d sem OpenMP\n",n);

  resultado = fat(n);
  printf("finonacci(%d) = %ld\n", n, resultado);

  return 0;
}
