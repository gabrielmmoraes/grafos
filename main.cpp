#include <stdio.h>
#include "grafo.h"
#include "tupla.h"

using namespace std;

int main(){

    FILE* pFileIn;

    pFileIn = fopen("points-5.txt","r");

    ListaAdjacencias G(pFileIn);

    /* Tupla<int*, float> t = G.TSP_lexicografico();

    printf("Caminho léxico: %f\t\n",t.elem2);
    for(int i=0;i<5;i++){
        printf("%d; ",t.elem1[i]+1);
    }
    printf("\n\n"); */

    Tupla<int*, float> t = G.TSP_vizinhosMaisProximos();

    printf("Caminho vizinhos: %f\t\n",t.elem2);
    for(int i=0;i<5;i++){
        printf("%d; ",t.elem1[i]+1);
    }
    printf("\n\n");

    return 0;
}
