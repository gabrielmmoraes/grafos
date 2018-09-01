#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string>
#include "grafo.h"

int main(){
    
    FILE* pFile;

    pFile = fopen("grafo_teste.txt", "r");

    ListaAdjacencias lista(pFile);

    lista.DFS(0);

    for(int i=0; i<lista.getNVertices(); i++){
        printf("Pai do vertice %d é %d\n", i+1, lista.vertices[i]->getPai()+1);
    }

    // Apresentação dos resultados
    printf("Resultados:\n\tVértices: %u\n\tArestas: %u\n", lista.getNVertices(), lista.getNArestas());
}
