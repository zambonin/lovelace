# Smith-Waterman

* **Para compilar**: make
* **Para testar**: ./run.sh

## Otimização

* Código traduzido para C
* Compilador escolhido: icc
* Troca de variáveis invariantes por valores absolutos
* Valor dependente do loop externo guardado em registrador
* Matriz linear (inicializada com memset)
* Remoção de chamadas de função dentro do loop
