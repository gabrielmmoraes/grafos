#include <stdio.h>
#include "grafo.h"
#include "tupla.h"
#include <ctime>
#include <chrono>

using namespace std;

int main(){

    FILE* pFileIn;
    FILE* pFileOut;

    Tupla<int*, float> t;

    chrono::high_resolution_clock::time_point inicio, fim;
    chrono::duration<double> duracao;

    int n;

    pFileIn = fopen("points-1000.txt","r");
    pFileOut = fopen("temposTSP.txt","a");

    n = 1000;

    fprintf(pFileOut, "Tempos para %d pontos:\t\n", n);

    inicio = chrono::high_resolution_clock::now();
    MatrizAdjacencias G(pFileIn);
    fim = chrono::high_resolution_clock::now();

    duracao = chrono::duration_cast<chrono::duration<double>>(fim-inicio);
    fprintf(pFileOut, "Tempo construtor: %lf ms\n", duracao);

    inicio = chrono::high_resolution_clock::now();
    t = G.TSP_lexicografico();
    fim = chrono::high_resolution_clock::now();
    
    duracao = chrono::duration_cast<chrono::duration<double>>(fim-inicio);
    fprintf(pFileOut, "Método lexicográfico: %lf ms\n", duracao);
    free(t.elem1);
    
    inicio = chrono::high_resolution_clock::now();
    t = G.TSP_vizinhosMaisProximos();
    fim = chrono::high_resolution_clock::now();
    
    duracao = chrono::duration_cast<chrono::duration<double>>(fim-inicio);
    fprintf(pFileOut, "Método vizinhos mais próximos: %lf ms\n\n", duracao);
    free(t.elem1);

    return 0;
}
