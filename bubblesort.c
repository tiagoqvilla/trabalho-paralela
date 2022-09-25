// bubble_sort.c (Roland Teodorowitsch; 15 set. 2022)

#include <stdio.h>
#include <omp.h>

#define MAX_ARRAY_SIZE 25000
#define INI_ARRAY_SIZE 2500
#define INC_ARRAY_SIZE 2500
#define NUM_ARRAYS 25

// ESTRUTURA DE DADOS COMPARTILHADA
int arrays[NUM_ARRAYS][MAX_ARRAY_SIZE];

// BUBBLE SORT
void BubbleSort(int n, int * vetor) {
  int c =0, d, troca, trocou =1;

  while (c < (n-1) && trocou ) {
        trocou = 0;
        for (d = 0 ; d < n - c - 1; d++)
            if (vetor[d] > vetor[d+1]) {
                troca      = vetor[d];
                vetor[d]   = vetor[d+1];
                vetor[d+1] = troca;
                trocou = 1;
            }
        c++;
  }
}

int main() {
  int i, j, array_size;
  double tempo;

  for (array_size = INI_ARRAY_SIZE; array_size <= MAX_ARRAY_SIZE; array_size += INC_ARRAY_SIZE) {

      // INICIALIZA OS ARRAYS A SEREM ORDENADOS
      for (i=0 ; i<NUM_ARRAYS; i++) {
          for (j=0 ; j<array_size; j++) {
              if (i%5 == 0)
                 arrays[i][j] = array_size-j;
              else
                 arrays[i][j] = j+1;
          }
      }

      // REALIZA A ORDENACAO
      tempo = -omp_get_wtime();
      omp_set_num_threads(4);
      #pragma omp parallel for
      for (i=0 ; i<NUM_ARRAYS; i++) {
          BubbleSort(array_size, &arrays[i][0]);
      }
      tempo += omp_get_wtime();

      // VERIFICA SE OS ARRAYS ESTAO ORDENADOS
      for (i=0 ; i<NUM_ARRAYS; i++)
          for (j=0 ; j<array_size-1; j++)
              if (arrays[i][j] > arrays[i][j+1])
                 return 1;

      // MOSTRA O TEMPO DE EXECUCAO
      printf("%d %lf\n",array_size, tempo);
  }
  return 0;
}
