#include <stdio.h>
#include <stdlib.h>

void pares (unsigned int* arr, unsigned int n, unsigned int inicio){
    
    if (inicio == n){
      return;
    }
  
    unsigned int i;
    
    for (i = inicio+1; i < n; i++){
      printf("Par encontrado: {%u, %u}\n", inicio+1, i+1);  
    }
    pares(arr, n, inicio+1);
}


int main(int argc, char* argv[]){
    unsigned int n;

    if (argc != 2){
      printf("Execute o programa com apenas um argumento, especificando o N (Exemplo: ./pares 2)\n");
      exit(0);
    }

    n = atoi(argv[1]);

    unsigned int i = 0;
    unsigned int arr[n];
    
    for (i = 0; i < n; i++){
        arr[i] = i+1;
    }
    
    pares(&arr, n, 0);

    return 0;
}
