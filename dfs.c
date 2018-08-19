#include <stdint.h>
#include "dfs.h"

//unsigned int n_visitados = 0;

void dfs(unsigned int size, unsigned int raiz, uint8_t grafo[size][size], uint8_t visitados[], unsigned int graus[]){
    //printf("Entrando em %d:\n", raiz+1);
    //n_visitados++;
    visitados[raiz] = 1;
    for (unsigned int i = 0; i < size; i++){
        //printf("Checando %d\t%d, visitados %d\n", raiz+1, i+1, n_visitados);
        if(grafo[raiz][i]){
            graus[raiz]++;
            //printf("Aresta entre %d e %d, grau de %d agora é %d\n", raiz+1, i+1, raiz+1, graus[raiz]);
            if(!visitados[i]) dfs(size, i, grafo, visitados, graus);
        }
    }
    return;
}