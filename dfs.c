#include <stdint.h>
#include "dfs.h"

//unsigned int n_visitados = 0;

void dfs(unsigned int size, unsigned int raiz, uint8_t grafo[size][size], uint8_t visitados[], unsigned int graus[]){
    // Marcando vértice como visitado
    visitados[raiz] = 1;
    for (unsigned int i = 0; i < size; i++){
        // Checando vizinhos do vértice
        if(grafo[raiz][i]){
            // Ao achar um vizinho, aumenta o grau do vértice raiz
            graus[raiz]++;
            // Caso o vértice encontrado não foi visitado, executamos dfs nele
            if(!visitados[i]) dfs(size, i, grafo, visitados, graus);
        }
    }
    return;
}
