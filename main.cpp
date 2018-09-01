#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string>
#include "grafo.h"

int main(){
    
    FILE* pFile;

    pFile = fopen("grafo_teste.txt", "r");

    ListaAdjacencias lista(pFile);

    lista.componentesConexos();

    for(int i=0; i<lista.getNVertices(); i++){
        printf("CC do vertice %d é %d\n", i+1, lista.vertices[i]->getMarcacao());
    }

    // Apresentação dos resultados
    printf("Resultados:\n\tVértices: %u\n\tArestas: %u\n", lista.getNVertices(), lista.getNArestas());
}
