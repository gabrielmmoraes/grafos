#include <stdio.h>
#include <cmath>
#include "grafo.h"
#include "tupla.h"

using namespace std;

int main(){

    FILE* pFileIn;
    FILE* pFileOut;

    int n;

    pFileIn = fopen("points-20.txt","r");
    pFileOut = fopen("resultadosTSP.txt","a");

    n = 20;

    MatrizAdjacencias G(pFileIn);

    Tupla<int*, float> t = G.TSP_dinamica();

    fprintf(pFileOut, "Caminho dinâmico %d pontos: %f\t\n",n,t.elem2);
    for(int i=0;i<n;i++){
        fprintf(pFileOut, "%d ",t.elem1[i]+1);
    }
    fprintf(pFileOut, "\n\n");

    free(t.elem1);
    return 0;
}
