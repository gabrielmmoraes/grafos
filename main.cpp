#include <stdio.h>
#include "grafo.h"
#include "tupla.h"

using namespace std;

int main(){

    FILE* pFileIn;
    FILE* pFileOut;

    Tupla<int*, float> t;

    int n;

    pFileIn = fopen("points-10000.txt","r");
    pFileOut = fopen("resultadosTSP.txt","a");

    n = 10000;

    MatrizAdjacencias G(pFileIn);

    t = G.TSP_vizinhosMaisProximos();

    fprintf(pFileOut, "Caminho %d pontos: %f\t\n",n,t.elem2);
    for(int i=0;i<n;i++){
        fprintf(pFileOut, "%d ",t.elem1[i]+1);
    }
    fprintf(pFileOut, "\n\n");

    free(t.elem1);
    return 0;
}
