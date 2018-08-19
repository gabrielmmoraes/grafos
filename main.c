#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "dfs.h"

int main(){
    unsigned int i;
    unsigned int n_vertices;
    unsigned int arestas = 0;
    int aresta1, aresta2;
    unsigned short componentes_conexas = 1;

    fscanf(stdin, "%d", &n_vertices);

    uint8_t* visitados  = (uint8_t*)        calloc(n_vertices, 1);
    
    uint8_t (*grafo)[n_vertices];
    grafo = (uint8_t (*)[n_vertices])       calloc(n_vertices * n_vertices, 1);
    
    unsigned int* graus = (unsigned int*)   calloc(n_vertices, 4);

    while(fscanf(stdin, "%d %d", &aresta1, &aresta2) != EOF){
        grafo[aresta1-1][aresta2-1] = grafo[aresta2-1][aresta1-1] = 1;
        arestas++;
    }

    dfs(n_vertices, 0, grafo, visitados, graus);

    for(i = 0; i < n_vertices; i++){
        if(!visitados[i]){
            componentes_conexas++;
            dfs(n_vertices, i, grafo, visitados, graus);
        }
    }

    unsigned int max = 0;
    unsigned int min = n_vertices;
    double med = 0;

    for(i = 0; i < n_vertices; i++){
        //printf("Grau do vértice %d: %d\n", i+1, graus[i]);
        med += graus[i];
        if(graus[i] > max)  max = graus[i];
        if(graus[i] < min)  min = graus[i];
    }

    med /= n_vertices;

    printf("Resultados:\n\tVértices: %u\n\tArestas: %u\n\tComponentes Conexas: %d\n\tGrau mínimo: %u\n\tGrau máximo: %u\n\tGrau médio: %.2lf\n", n_vertices, arestas, componentes_conexas, min, max, med);
}