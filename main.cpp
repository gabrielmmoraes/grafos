#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string>
#include <ctime>
#include <sys/time.h>
#include "grafo.h"

using namespace std;

long getMicrotime(){
	struct timeval currentTime;
	gettimeofday(&currentTime, NULL);
	return currentTime.tv_sec * (int)1e6 + currentTime.tv_usec;
}

int main(){

	const int LEITURAS = 1000;

	int i;

    FILE* pFile;

    pFile = fopen("as_graph.txt", "r");

	long inicio, fim, acum_bfs = 0, acum_dfs = 0;

	double duracao;

	printf("Análise do grafo com Lista de Adjacência:\n\n");
	
	inicio = getMicrotime();

    ListaAdjacencias grafo(pFile);

	fim = getMicrotime();

	duracao = (fim-inicio) / 1000;

	printf("Construindo Lista de Adjacência (%.0lf ms)\n\n", duracao);
    
	for(i = 0; i<LEITURAS; i++){
		inicio = getMicrotime();
		grafo.BFS(i);
		fim = getMicrotime();
		duracao = (fim - inicio) / 1000;
		acum_bfs += duracao;

		inicio = getMicrotime();
		grafo.DFS(i);
		fim = getMicrotime();
		duracao = (fim - inicio) / 1000;
		acum_dfs += duracao;
	}

	printf("Tempo Médio (1000 observações):\n\tBFS: %ld ms\n\tDFS: %ld ms\n\n", acum_bfs/LEITURAS, acum_dfs/LEITURAS);

	for(int i=0;i<5;i++){
		grafo.BFS(i);
		printf("BFS a partir de %d:\n",i+1);
		for(int j = 9;j<50;j+=10){
			printf("O pai de %d é %d\n",j+1,grafo.getVertices()[j]->getPai()+1);
		}
		grafo.DFS(i);
		printf("\nDFS a partir de %d:\n",i+1);
		for(int j = 9;j<50;j+=10){
			printf("O pai de %d é %d\n",j+1,grafo.getVertices()[j]->getPai()+1);
		}
		printf("\n");
	}

	Lista** componentes = grafo.analiseComponentesConexos();
	int quantidade = grafo.componentesConexos().size();
	int maior = componentes[0]->getTamanho();
	int menor = componentes[quantidade-1]->getTamanho();
	printf("O grafo possui %d componentes conexas.\n A maior tem tamanho %d.\n A menor tem tamanho %d\n\n",quantidade,maior,menor);

	printf("Grau mínimo: %d\nGrau máximo: %d\nGrau médio: %f\nMediana do grau: %f\n\n",grafo.getGrauMin(),grafo.getGrauMax(),grafo.getGrauMedio(),grafo.getGrauMediano(	));
    
	//printf("Diâmetro do grafo(se -1, grafo não é conexo): %d\n",grafo.diametro());
	// Apresentação dos resultados
    //printf("Resultados:\n\tVértices: %u\n\tArestas: %u\n\tMediana: %.2f\n", lista.getNVertices(), lista.getNArestas(), lista.getGrauMediano());
}
