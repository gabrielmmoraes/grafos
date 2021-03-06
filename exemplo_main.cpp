
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string>
#include "src/grafo.h"
#include "src/tupla.h"
#include <ctime>
#include <chrono>

using namespace std;

int main(){

    FILE* pFileIn;
    FILE* pFileOut;
    FILE* MST;

    chrono::high_resolution_clock::time_point inicio, fim;
    chrono::duration<double> duracao;

    pFileIn = fopen("grafo_2.txt", "r");
    pFileOut = fopen("resultados_grafo_2_matriz.txt", "w");
    MST = fopen("MST_grafo_2.txt", "w");

    inicio = chrono::high_resolution_clock::now();
    ListaAdjacencias G(pFileIn, true);
    fim = chrono::high_resolution_clock::now();
    duracao = chrono::duration_cast<chrono::duration<double>>(fim-inicio);
    fprintf(pFileOut, "Tempo construtor: %lf ms\n\n", duracao);

    for (int j = 9; j <= 49; j+=10){

        Tupla<int*,float> tupla = G.CaminhoMinimo(0,j);

        fprintf(pFileOut, "Distância até %d: %.3f\n",j+1, tupla.elem2);

        fprintf(pFileOut, "Caminho: ");
        for(int i = 1; i<=tupla.elem1[0];i++){
            fprintf(pFileOut, "(%d) ",tupla.elem1[i]+1);
        }
        fprintf(pFileOut, "\n");

        fprintf(pFileOut, "Excentricidade de %d: %.3f\n\n", j+1, G.excentricidade(j));

    }

    inicio = chrono::high_resolution_clock::now();

    for(int i=0;i<100;i++){
        G.excentricidade(i);
    }

    fim = chrono::high_resolution_clock::now();

    duracao = chrono::duration_cast<chrono::duration<double>>(fim-inicio)/100;
    fprintf(pFileOut, "Tempo médio excentricidade: %lf ms\n", duracao);

    inicio = chrono::high_resolution_clock::now();
    G.Prim(0);
    fim = chrono::high_resolution_clock::now();
    duracao = chrono::duration_cast<chrono::duration<double>>(fim-inicio);
    G.ArvoreGeradoraMinima(MST);

    fprintf(pFileOut, "Tempo MST: %lf ms\n\n", duracao);

    /* inicio = chrono::high_resolution_clock::now();
    float distmed = G.DistanciaMedia();
    fim = chrono::high_resolution_clock::now();
    duracao = chrono::duration_cast<chrono::duration<double>>(fim-inicio);
    fprintf(pFileOut, "Distância média: %.3f\n", distmed);
    fprintf(pFileOut, "Tempo distância média: %lf ms\n", duracao); */
}