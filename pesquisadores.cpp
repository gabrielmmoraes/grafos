#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string>
#include "grafo.h"
#include <algorithm>

using namespace std;

int main(){
    //Custo total: 1155826.75

    FILE* pFileIn;
    FILE* consulta;

    pFileIn = fopen("rede_colaboracao.txt", "r");
    //consulta = fopen("rede_colaboracao_vertices.txt", "r");

    ListaAdjacencias G(pFileIn, true);
    /*Tupla<int, int> vertice;
    vector<Tupla<int, int> > vetor_graus;
    for(int i=0;i<G.getNVertices();i++){
        vertice.elem1 = i;
        vertice.elem2 = G.getVertices()[i]->getGrau();
        vetor_graus.push_back(vertice);
    }

    sort(vetor_graus.begin(), vetor_graus.end());

    Tupla<int, int> maior1 = vetor_graus[G.getNVertices()-1];
    Tupla<int, int> maior2 = vetor_graus[G.getNVertices()-2];
    Tupla<int, int> maior3 = vetor_graus[G.getNVertices()-3];

    int v;
    char nome[2048];
    while(fscanf(consulta, "%d,%s", &v, nome)!=EOF){
        if(v==maior1.elem1){
            printf("Maior: %s\nGrau: %d\n\n", nome, maior1.elem2);
            break;
        }
    }

    while(fscanf(consulta, "%d,%s", &v, nome)!=EOF){
        if(v==maior2.elem1){
            printf("Segundo maior: %s\nGrau: %d\n\n", nome, maior2.elem2);
            break;
        }
    }

    while(fscanf(consulta, "%d,%s", &v, nome)!=EOF){
        if(v==maior3.elem1){
            printf("Terceiro maior: %s\nGrau: %d\n\n", nome, maior3.elem2);
            break;
        }
    }

    while(fscanf(consulta, "%d,%s", &v, nome)!=EOF){
        if(nome=="Edsger W. Dijkstra"){
            break;
        }
    }

    for(int i=0;i<G.getVertices()[v]->getGrau();i++){} */

    /* Tupla<int*,float> gosto = G.CaminhoMinimo(2722,11365);

    fprintf(pFileOut, "Distância até Turing: %.3f\n", gosto.elem2);

    fprintf(pFileOut, "Caminho: ");
    for(int i = 1; i<=gosto.elem1[0];i++){
        fprintf(pFileOut, "(%d) ",gosto.elem1[i]);
    }
    fprintf(pFileOut, "\n");



    gosto = G.CaminhoMinimo(2722,471365);

    fprintf(pFileOut, "Distância até Kruskal: %.3f\n", gosto.elem2);

    fprintf(pFileOut, "Caminho: ");
    for(int i = 1; i<=gosto.elem1[0];i++){
        fprintf(pFileOut, "(%d) ",gosto.elem1[i]);
    }
    fprintf(pFileOut, "\n");



    gosto = G.CaminhoMinimo(2722,5709);

    fprintf(pFileOut, "Distância até Kleinberg: %.3f\n", gosto.elem2);

    fprintf(pFileOut, "Caminho: ");
    for(int i = 1; i<=gosto.elem1[0];i++){
        fprintf(pFileOut, "(%d) ",gosto.elem1[i]);
    }
    fprintf(pFileOut, "\n");



    gosto = G.CaminhoMinimo(2722,11386);

    fprintf(pFileOut, "Distância até Tardos: %.3f\n", gosto.elem2);

    fprintf(pFileOut, "Caminho: ");
    for(int i = 1; i<=gosto.elem1[0];i++){
        fprintf(pFileOut, "(%d) ",gosto.elem1[i]);
    }
    fprintf(pFileOut, "\n");*/



    Tupla<int*, float> gosto = G.CaminhoMinimo(2722,343930);

    printf("Distância até Ratton: %.3f\n", gosto.elem2);

    printf("Caminho: ");
    for(int i = 1; i<=gosto.elem1[0];i++){
        printf("(%d) ",gosto.elem1[i]);
    }
    printf("\n");
    return 0;
}